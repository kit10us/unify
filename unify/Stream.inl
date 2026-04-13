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


#pragma warning(push)
#pragma warning(disable: 4100) // Microsoft Visual C++ (MSVC) indicating that a function parameter is declared but not used in the function body

namespace unify
{
	inline
	Stream::Stream()
		: m_uFlags{ FLAG00 }
		, m_pStream{ 0 }
		, m_bEndOfStream{ false }
		, m_uBytesWaiting{ 0 }
		, m_isOpen{ false }
	{
	}

	inline
	Stream::~Stream()
	{
	}

	// Open a stream.
	inline
	bool Stream::Open(StreamAccessType access, void* pData)
	{
		return true;
	}

	// Close a stream.
	inline
	void Stream::Close()
	{
		if (m_pStream)
		{
			fclose((FILE*)m_pStream);
			m_pStream = 0;
			m_bEndOfStream = false;
		}
	}

	// Read a length of data.
	inline
	unsigned int Stream::Read(void* pDest, unsigned int uLength)
	{
		// Fail by default.
		return 0;
	}

	// Read a pack of data (the size of a pack is dependent on the stream).
	inline
	unsigned int Stream::ReadPack(void* pDest, unsigned int uLength)
	{
		// Fail by default.
		return 0;
	}

	// Write a length of data.
	inline
	void Stream::Write(const void* pSrc, unsigned int uLength)
	{
		// Fail by default.
		throw unify::Exception("Access base write!");
	}

	// Write a pack of data (the size of a pack is dependent on the stream).
	inline
	void Stream::WritePack(const void* pSrc)
	{
		// Fail by default.
		throw unify::Exception("Access base write!");
	}

	// Set the stream flags.
	inline
	void Stream::SetFlags(unsigned int uFlags)
	{
		m_uFlags = uFlags;
	}

	// Returns the currently set stream flags.
	inline
	unsigned int Stream::GetFlags()
	{
		return m_uFlags;
	}

	// Seek to a position in a stream
	inline
	bool Stream::Seek(StreamSeekType seek, int iOffset)
	{
		return false; // DEFAULT NO SEEK
	}

	// Returns if we've reached the end of the stream
	inline
	bool Stream::EndOfStream()
	{
		return m_bEndOfStream;
	}

	// Returns the number of bytes waiting (or until EOF)
	inline
	unsigned int Stream::BytesWaiting()
	{
		return m_uBytesWaiting;
	}

	inline
	bool Stream::IsOpen() const
	{
		return m_pStream != nullptr;
	}
}

#pragma warning(pop)
