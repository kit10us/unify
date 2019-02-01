// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved
#pragma once

/// <summary>
/// Allows streaming (serializing) of data
/// </summary>

#include <unify/Unify.h>

namespace unify 
{
	enum StreamAccessType
	{
		STREAMACCESS_NONE,
		STREAMACCESS_READ,
		STREAMACCESS_WRITE,
		STREAMACCESS_APPEND,
		STREAMACCESS_READTEXT,
		STREAMACCESS_WRITETEXT,
		STREAMACCESS_APPENDTEXT,
		STREAMACCESS_READBINARY,
		STREAMACCESS_WRITEBINARY,
		STREAMACCESS_APPENDBINARY
	};

	enum StreamSeekType
	{
		STREAMSEEK_START,	// Seek from the start of the stream
		STREAMSEEK_END,		// Seek from the end of the stream
		STREAMSEEK_CURRENT	// Seek from our current position
	};

	class Stream
	{
	public:
		Stream();
		virtual ~Stream();

		virtual bool Open( StreamAccessType access, void * pData );
		virtual void Close();		
		virtual unsigned int Read( void* pDest, unsigned int uLength );
		virtual unsigned int ReadPack( void* pDest, unsigned int uLength );
		virtual void Write( const void* pSrc, unsigned int uLength );
		virtual void WritePack( const void* pSrc );
		virtual bool Seek( StreamSeekType seek, int iOffset = 0 );
		void SetFlags( unsigned int uFlags );
		unsigned int GetFlags();
		bool EndOfStream();
		unsigned int BytesWaiting();
		bool IsOpen() const;

	protected:
		FILE * m_pStream;
		StreamAccessType m_Access;
		unsigned int m_uFlags;
		bool m_bEndOfStream;
		unsigned int m_uBytesWaiting;
		bool m_isOpen;
	};
}

