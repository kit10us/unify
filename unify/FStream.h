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
	/// Perform stream operation on a file source.
	/// </summary>
	class FileStream : public Stream
	{
	public:
		FileStream();
		~FileStream();

		void Open( StreamAccessType access, unify::Path path );
		void Close();
		
		unsigned int Read( void * pDest, unsigned int uLength );
		unsigned int ReadPack( void * pDest, unsigned int uLength );
		
		void Write( const void * pSrc, unsigned int uLength ) override;
		void WritePack( const void * pSrc ) override;
		void Write( std::string out );

		bool Seek( StreamSeekType seek, int iOffset = 0 );

		__int64 Pos();
		bool SetPosition( __int64 );
	};

	__int64 FileLength( const char * pszFilename );
}
