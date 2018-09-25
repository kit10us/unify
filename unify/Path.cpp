// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/Path.h>
#include <unify/String.h>
#include <fstream>
#include <stdio.h>

using namespace unify;


Path::Path()
{
}

Path::Path( std::string path )
: m_path( path )
{
}

Path::Path( const char * const path )
: m_path( path )
{
}

Path::Path( const Path & left, const Path & right )
{
	Combine( left, right );
}

Path::Path( const std::vector< std::string > & pathParts )
{
	Join( pathParts );
}


Path & Path::operator=( const Path & path )
{
	m_path = path.m_path;
	return *this;
}

bool Path::operator==( const Path & path ) const
{
	if ( m_path.length() != path.m_path.length() )
	{
		return false;
	}

	unsigned int i = 0;
	while( i < m_path.length()  )
	{
		char l = m_path[ i ];
		char r = path.m_path[ i ];
		if ( l == '\\' )
		{
			l = '/';
		}
		if ( r == '\\' )
		{
			r = '/';
		}

		if ( l != r )
		{
			return false;
		}
		++i;
	}

	return true;
}

bool Path::operator!=( const Path & path ) const
{
	return !( *this == path );
}

Path Path::operator+( const Path & path )
{
	Path newPath( *this, path );
	return newPath;
}

Path & Path::operator+=( const Path & path )
{
	Combine( *this, path );
	return *this;
}

bool Path::Empty() const
{
	return m_path.empty();
}

std::vector< std::string > Path::Split() const
{
	std::vector< std::string > parts;
	size_t start = 0;
	size_t p;
	for ( p = 0; p != m_path.size(); ++p )
	{
		if ( m_path.at( p ) == '\\' || m_path.at( p ) == '/' )
		{
			if ( p == 0 )
			{
				parts.push_back( "/" );
			}
			else
			{
				parts.push_back( m_path.substr( start, p - start + 1 ) );
				start = p + 1;
			}
		}
	}
	if ( p != 0 && p != start )
	{
		parts.push_back( m_path.substr( start, p - start ) );
		start = p + 1;
	}
	return parts;
}

Path & Path::Join( const std::vector< std::string > & pathParts )
{
	m_path = std::string();
	for ( std::vector< std::string >::const_iterator itr = pathParts.begin(), end = pathParts.end(); itr != end; ++itr )
	{
		Combine( *this, unify::Path( *itr ) );
	}
	return *this;
}

Path & Path::Normalize()
{
	std::vector< std::string > parts = Split();
	for ( std::vector< std::string >::const_iterator itr = parts.begin(); itr != parts.end(); ++itr )
	{
		if ( itr != parts.begin() && unify::BeginsWith( *itr, ".." ) ) 
		{
			itr = parts.erase( itr - 1 ); // Erase what ever leads.
			itr = parts.erase( itr ); // Erase the "..".
		}
		else if ( itr != parts.begin() && unify::BeginsWith( *itr, "." ) ) 
		{
			itr = parts.erase( itr ); // Erase the ".".
		}
	}
	return Join( parts );
}

bool Path::Exists() const
{
	std::ifstream ifile( m_path.c_str() );
	return ifile ? true : false;
}

std::string Path::ExtensionOnly() const
{
	size_t i = m_path.find_last_of( "./\\" );
	if ( i == std::string::npos )
	{
		return std::string();
	}
	else if ( m_path[ i ] == '.' )
	{
		return m_path.substr( i );
	}

	return std::string();
}

Path Path::DirectoryOnly() const
{
	size_t i = m_path.find_last_of( ":/\\" );
	if ( i == std::string::npos )
	{
		return Path();
	}
	else
	{
		std::string s = m_path.substr( 0, i + 1 );
		return Path( m_path.substr( 0, i + 1 ) );
	}
}

std::string Path::Filename() const
{
	size_t l = m_path.find_last_of( ":/\\" );
	if ( l == std::string::npos )
	{
		l = 0;
	}
	else
	{
		l += 1;
	}

	return m_path.substr( l );
}

std::string Path::FilenameNoExtension() const
{
	size_t l = m_path.find_last_of( ":/\\" );
	if ( l == std::string::npos )
	{
		l = 0;
	}
	else
	{
		l += 1;
	}

	size_t r = m_path.find_last_of( "." );
	if ( r != std::string::npos )
	{
		r = r - l;
	}

	return m_path.substr( l, r );
}

Path & Path::Combine( const Path & left, const Path & right )
{
	// If one or the other is empty, return the other.
	if ( left.m_path.empty() )
	{
		m_path = right.m_path;
		return *this;
	}
	else if ( right.m_path.empty() )
	{
		m_path = left.m_path;
		return *this;
	}

	std::string pathOut( left.m_path ); // Create a new path instead of working directly with ours incase L or R is us.

	// Prefix if needed.
	char lastChar = left.m_path[ left.m_path.length() - 1 ];
	char firstChar = right.m_path[ 0 ];
	if ( lastChar != '\\' && lastChar != '/' && firstChar != '\\' && firstChar != '/' )
	{
		pathOut += '/' + right.m_path;
	}
	else if ( ( lastChar == '\\' || lastChar == '/' ) && ( firstChar == '\\' || firstChar == '/' ) )
	{
		// Remove prefix if it exists with both
		pathOut += right.m_path.substr( 1 );
	}
	else
	{
		pathOut += right.m_path;
	}

	m_path = pathOut;
	return *this;
}

bool Path::IsDirectory() const
{
	char lastChar = m_path[ m_path.length() - 1 ];
	if ( lastChar == '\\' || lastChar == '/' )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Path::IsExtension( std::string extension ) const
{
	std::string leftExtension = ExtensionOnly();
	if ( leftExtension.empty() )
	{
		if ( extension.empty() )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if ( extension.empty() )
	{
		return false;
	}

	if ( extension[ 0 ] != '.' )
	{
		return _stricmp( leftExtension.c_str() + 1, extension.c_str() ) == 0;
	}
	else
	{
		return _stricmp( leftExtension.c_str(), extension.c_str() ) == 0;
	}
}

Path Path::ChangeExtension( std::string extension ) const
{
	std::string pathOut;
	size_t i = m_path.find_last_of( "./\\" );

	// Check if we found an extension
	if ( i == std::string::npos || m_path[ i ] == '/' || m_path[ i ] == '\\' )
	{
		pathOut = m_path;
	}
	else
	{
		pathOut = m_path.substr( 0, i );
	}

	// Allow an extension to be removed
	if ( ! extension.empty() )
	{
		pathOut += ( extension.at( 0 ) == '.' ? "" : "." ) + extension;
	}
	return Path( pathOut );
}

Path & Path::ChangeFilename( const Path & newFilename )
{
	return Combine( DirectoryOnly(), unify::Path( newFilename.Filename() ) );
}

std::string Path::ToString() const
{
	return m_path;
}

std::wstring Path::ToWString() const
{
	return std::wstring( m_path.begin(), m_path.end() );
}

std::string Path::ToString( Slash direction ) const
{
	std::string temp;

	switch( direction )
	{
	case Slash::Foward:
		temp = StringReplace( ToString(),  "/", "\\" );
		break;
	case Slash::Backward:
		temp = StringReplace( ToString(), "\\", "/" );
		break;
	}
	return temp;
}

bool Path::Delete()
{
	return remove( (char*)m_path.c_str() ) ? false : true;
}

bool Path::Rename( unify::Path to )
{
	return rename( m_path.c_str(), to.m_path.c_str() ) ? false : true;
}

std::wstring Path::ToWString( Slash direction ) const
{
	std::string temp( ToString( direction ) );
	return std::wstring( temp.begin(), temp.end() );
}

std::ostream & operator<<( std::ostream & os, const Path & path )
{
	os << path.ToString();
	return os;
}
