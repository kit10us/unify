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


#include <unify/Stream.h>
#include <unify/Exception.h>
#include <unify/Flags.h>

using namespace unify;

Stream::Stream()
: m_uFlags{ FLAG00 }
, m_pStream{ 0 }
, m_bEndOfStream{ false }
, m_uBytesWaiting{ 0 }
, m_isOpen{ false }
{
}

Stream::~Stream()
{
}

// Open a stream.
bool Stream::Open( StreamAccessType access, void * pData )
{
	access;
	pData;
	return true;
}

// Close a stream.
void Stream::Close()
{
	if( m_pStream )
	{
		fclose( (FILE*)m_pStream );
		m_pStream = 0;
		m_bEndOfStream = false;
	}
}

// Read a length of data.
unsigned int Stream::Read( void * pDest, unsigned int uLength )
{
	pDest;
	uLength;
	// Fail by default.
	return 0;
}

// Read a pack of data (the size of a pack is dependent on the stream).
unsigned int Stream::ReadPack( void * pDest, unsigned int uLength )
{
	pDest;
	uLength;
	// Fail by default.
	return 0;
}

// Write a length of data.
void Stream::Write( const void * pSrc, unsigned int uLength )
{
	pSrc;
	uLength;
	// Fail by default.
	throw unify::Exception( "Access base write!" );
}

// Write a pack of data (the size of a pack is dependent on the stream).
void Stream::WritePack( const void * pSrc )
{
	pSrc;
	// Fail by default.
	throw unify::Exception( "Access base write!" );
}

// Set the stream flags.
void Stream::SetFlags( unsigned int uFlags )
{
	m_uFlags = uFlags;
}

// Returns the currently set stream flags.
unsigned int Stream::GetFlags()
{
	return m_uFlags;
}

// Seek to a position in a stream
bool Stream::Seek( StreamSeekType seek, int iOffset )
{
	seek;
	iOffset;
	return false; // DEFAULT NO SEEK
}

// Returns if we've reached the end of the stream
bool Stream::EndOfStream()
{
	return m_bEndOfStream;
}

// Returns the number of bytes waiting (or until EOF)
unsigned int Stream::BytesWaiting()
{
	return m_uBytesWaiting;
}

bool Stream::IsOpen() const
{
	return m_pStream != nullptr;
}
