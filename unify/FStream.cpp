/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


#include <unify/FStream.h>
#include <unify/Exception.h>
#include <stdio.h>
#include <string>

#pragma warning(push)
#pragma warning(disable: 4996) // This function or variable may be unsafe. (fopen)

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

	char mode[3]{};
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

	case STREAMACCESS_NONE:
		throw Exception("Attempted to access an FStream with access modifier \'none\'!");
	};

	m_pStream = fopen(path.ToString().c_str(), mode );

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
	Write( out.c_str(), (unsigned int)out.length() );
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

bool FileStream::Pos(fpos_t & pos)
{
	return fgetpos( (FILE*)m_pStream, &pos) == 0;
}

bool FileStream::SetPosition( fpos_t & pos )
{
	return fsetpos( (FILE*)m_pStream, &pos) == 0;
}

int64_t unify::FileLength( const char * pszFilename )
{
	int64_t iLength = 0;
	
	FILE* fp{};

	fp = fopen(pszFilename, "rt" );
	if (fp == 0)
	{
		return {};
	}

	while( fgetc( fp ) != EOF ) iLength++;

	return iLength;
}

#pragma warning(pop)