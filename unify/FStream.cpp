// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/FStream.h>
#include <unify/Exception.h>
#include <string>

using namespace unify;

FileStream::FileStream()
{
}

FileStream::~FileStream()
{
	Close();
}

void FileStream::Open( StreamAccessType access, unify::Path path )
{
	Close();

	char mode[3];
	switch( access )
	{
	case STREAMACCESS_READBINARY:
		mode[0] = 'r';
		mode[1] = 'b';
		mode[2] = 0;
		break;
	case STREAMACCESS_WRITEBINARY:
		mode[0] = 'w';
		mode[1] = 'b';
		mode[2] = 0;
		break;
	case STREAMACCESS_APPENDBINARY:
		mode[0] = 'a';
		mode[1] = 'b';
		mode[2] = 0;
		break;
	case STREAMACCESS_READ:
	case STREAMACCESS_READTEXT:
		mode[0] = 'r';
		mode[1] = 't';
		mode[2] = 0;
		break;
	case STREAMACCESS_WRITE:
	case STREAMACCESS_WRITETEXT:
		mode[0] = 'w';
		mode[1] = 't';
		mode[2] = 0;
		break;	
	case STREAMACCESS_APPEND:
	case STREAMACCESS_APPENDTEXT:
		mode[0] = 'a';
		mode[1] = 't';
		mode[2] = 0;
		break;
	};

	fopen_s( &m_pStream, path.ToString().c_str(), mode );

	if( ! m_pStream )
	{
		throw unify::Exception( "Failed to open file \"" + path.ToString() + "\"!" );
	}

	m_Access = access;
	m_bEndOfStream = false;
	m_uBytesWaiting = /*BYTES_UNKNOWN*/0;
}

void FileStream::Close()
{
	Stream::Close();
}

// Read uLength bytes from stream, return actual bytes read
unsigned int FileStream::Read( void * pDest, unsigned int uLength )
{
	if( m_Access != STREAMACCESS_READ && m_Access != STREAMACCESS_READBINARY )
	{
		return 0;
	}

	unsigned int u;
	int c = EOF;
	for( u = 0; u < uLength; u++ )
	{
		c = fgetc( (FILE*)m_pStream );
		if( c == EOF ) break;

		((unsigned char*)pDest)[u] = (unsigned char)c;
	}
	if( feof( (FILE*)m_pStream) || c == EOF )
	{
		m_bEndOfStream = true;
	}
	return u;
}

// Read a string of characters to and including the first NULL (or until the MaxLength-1 is reached)
// Note that this may include a '\r' cariage return.
unsigned int FileStream::ReadPack( void * pDest, unsigned int uMaxLength )
{
	if( m_Access != STREAMACCESS_READ && m_Access != STREAMACCESS_READTEXT )
	{
		return 0;
	}
	
	unsigned int u;
	int c = 0;
	c = fgetc( (FILE*)m_pStream );
	for( u = 0; (u < uMaxLength) && c != EOF && c != '\n' ; u++ )
	{
		((char*)pDest)[u] = (char)c;
		c = fgetc( (FILE*)m_pStream );
	}
	((char*)pDest)[u] = 0;
	if( feof( (FILE*)m_pStream ) || c == EOF )
	{
		m_bEndOfStream = true;
	}
	return u;
}

// Write uLength bytes to stream
void FileStream::Write( const void * pSrc, unsigned int uLength )
{
	if( m_Access != STREAMACCESS_WRITE && m_Access != STREAMACCESS_WRITETEXT && m_Access != STREAMACCESS_APPEND )
	{
		throw unify::Exception( "Attempted write, when access mode is not a write supported mode!" );
	}
	
	unsigned int u;
	for( u = 0; u < uLength; u++ )
	{
		fputc( ((unsigned char*)pSrc)[u], (FILE*)m_pStream );
	}
}

// Write a null terminated string to the stream...
void FileStream::WritePack( const void* pSrc )
{
	if( m_Access != STREAMACCESS_WRITE && m_Access != STREAMACCESS_WRITETEXT && m_Access != STREAMACCESS_APPEND )
	{
		throw unify::Exception( "Attempted write, when access mode is not a write supported mode!" );
	}
	
	unsigned int u;
	for( u = 0; ((unsigned char*)pSrc)[u]; u++ )
	{
		fputc( ((unsigned char*)pSrc)[u], (FILE*)m_pStream );
	}
}

void FileStream::Write( std::string out )
{
	Write( out.c_str(), out.length() );
}

bool FileStream::Seek( StreamSeekType seek, int iOffset )
{
	// Reset the end of file...
	m_bEndOfStream = false;

	switch( seek )
	{
	default:
		return false;

	case STREAMSEEK_START:
		return( fseek( (FILE*)m_pStream, iOffset, SEEK_SET )==0 ? true : false );

	case STREAMSEEK_END:
		return( fseek( (FILE*)m_pStream, iOffset, SEEK_END )==0 ? true : false );

	case STREAMSEEK_CURRENT:
		return( fseek( (FILE*)m_pStream, iOffset, SEEK_CUR )==0 ? true : false );
	}
}

__int64 FileStream::Pos()
{
	//return fseek( (FILE*)m_pStream, 0L, SEEK_CUR );
	
	fpos_t pos;

	if( fgetpos( (FILE*)m_pStream, &pos) == 0 /*Success*/ ) return pos;
	
	return -1;
}

bool FileStream::SetPosition( __int64 iPos )
{
	fpos_t pos = iPos;

	if( fsetpos( (FILE*)m_pStream, &pos) == 0 /*Success*/ ) return true;
	
	return false;
}

__int64 FileLength( const char * pszFilename )
{
	__int64 iLength = 0;
	
	FILE * fp = 0;

	fopen_s( &fp, pszFilename, "rt" );
	if( fp == 0 ) return 0;

	while( fgetc( fp ) != EOF ) iLength++;

	return iLength;
}
