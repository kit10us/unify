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
#include <unify/Stream.h>
#include <unify/Path.h>

namespace unify 
{
	/// <summary>
	/// Perform stream operation on a file.
	/// </summary>
	class FileStream : public Stream
	{
	public:
		FileStream();
		~FileStream();

		/// <summary>
		/// Open a stream at a specified path.
		/// </summary>
		void Open( StreamAccessType access, unify::Path path );

		/// <summary>
		/// Close the stream.
		/// </summary>
		virtual void Close() override;
		
		/// <summary>
		/// Read from the stream.
		/// </summary>
		virtual unsigned int Read( void * pDest, unsigned int length ) override;

		/// <summary>
		/// Read a string of characters to and including the first NULL (or until the MaxLength-1 is reached)
		/// Note that this may include a '\r' cariage return.
		/// </summary>
		virtual unsigned int ReadPack( void * dest, unsigned int length ) override;
		
		/// <summary>
		/// Write to the stream.
		/// </summary>
		virtual void Write( const void * source, unsigned int length ) override;

		/// <summary>
		/// Write a null terminated string to the stream...
		/// </summary>
		virtual void WritePack( const void * pSrc ) override;

		/// <summary>
		/// Write a string to the stream.
		/// </summary>
		void Write( std::string out );

		/// <summary>
		/// Seek to a position in the stream.
		/// </summary>
		virtual bool Seek( StreamSeekType seek, int offset = 0 ) override;

		/// <summary>
		/// Returns our position within the stream.
		/// </summary>
		bool Pos(fpos_t & pos);

		/// <summary>
		/// Set our position within a stream.
		/// </summary>
		bool SetPosition( fpos_t & pos );
	};

	/// <summary>
	/// Returns a fike's length.
	/// </summary>
	int64_t FileLength( const char * filename );
}
