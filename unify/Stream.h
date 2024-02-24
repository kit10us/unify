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


#pragma once

#include <unify/Unify.h>

namespace unify 
{
	/// <summary>
	/// Type of stream access.
	/// </summary>
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

	/// <summary>
	/// Position to seek from.
	/// </summary>
	enum StreamSeekType
	{
		STREAMSEEK_START,	// Seek from the start of the stream
		STREAMSEEK_END,		// Seek from the end of the stream
		STREAMSEEK_CURRENT	// Seek from our current position
	};

	/// <summary>
	/// Allows streaming (serializing) of data.
	/// </summary>
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

