// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

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
