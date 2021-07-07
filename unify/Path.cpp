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


#include <unify/Path.h>
#include <unify/String.h>
#include <fstream>
#include <stdio.h>

using namespace unify;
using namespace string;

const std::string Path::XPathPrefix( "file:///" );

bool Path::IsXPath( std::string path )
{
	return BeginsWith( path, XPathPrefix );
}

Path::Path()
{
}

Path::Path( std::string path )
	: m_path{ BeginsWith( path, XPathPrefix ) ? path : XPathPrefix + path }
{
}

Path::Path( char * path )
	: m_path{ BeginsWith( path, XPathPrefix ) ? path : XPathPrefix + path }
{
}

Path::Path( Path left, Path right )
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
	std::string asString = ToString(); 
	for ( p = 0; p != asString.size(); ++p )
	{
		if (asString.at( p ) == '\\' || asString.at( p ) == '/' )
		{
			std::string part;
			if ( p != 0 )
			{
				part = asString.substr( start, p - start );
			}

			part += "/";
			parts.push_back( part );
			start = p + 1;
		}
	}
	if ( p != 0 && p != start )
	{
		parts.push_back( asString.substr( start, p - start ) );
		start = p + 1;
	}
	return parts;
}

Path & Path::Join( const std::vector< std::string > & pathParts )
{
	m_path = std::string();
	for ( std::vector< std::string >::const_iterator itr = pathParts.begin(), end = pathParts.end(); itr != end; ++itr )
	{
		Combine( *this, Path( *itr ) );
	}
	return *this;
}

Path & Path::Normalize()
{
	std::vector< std::string > parts = Split();
	for ( std::vector< std::string >::const_iterator itr = parts.begin(); itr != parts.end(); ++itr )
	{
		if ( itr != parts.begin() && BeginsWith( *itr, ".." ) ) 
		{
			itr = parts.erase( itr - 1 ); // Erase what ever leads.
			itr = parts.erase( itr ); // Erase the "..".
		}
		else if ( itr != parts.begin() && BeginsWith( *itr, "." ) ) 
		{
			itr = parts.erase( itr ); // Erase the ".".
		}
	}
	return Join( parts );
}

bool Path::Exists() const
{
	std::ifstream ifile( ToString() );
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

bool Path::HasExtension() const
{
	return !this->ExtensionOnly().empty();
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
	if ( left.m_path.empty() || left.m_path == XPathPrefix )
	{
		m_path = right.ToXPath();
		return *this;
	}
	else if ( right.m_path.empty() || right.m_path == XPathPrefix )
	{
		m_path = left.ToXPath();
		return *this;
	}

	std::string pathOut( left.m_path ); // Create a new path instead of working directly with ours incase L or R is us.

	// Prefix if needed.
	char lastChar = RightString( left.ToString(), 1 )[ 0 ];
	char firstChar = right.ToString()[ 0 ];
	if ( lastChar != '\\' && lastChar != '/' && firstChar != '\\' && firstChar != '/' )
	{
		pathOut += '/' + right.ToString();
	}
	else if ( ( lastChar == '\\' || lastChar == '/' ) && ( firstChar == '\\' || firstChar == '/' ) )
	{
		// Remove prefix if it exists with both
		pathOut += right.ToString().substr( 1 );
	}
	else
	{
		pathOut += right.ToString();
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
	return string::StringIs( ExtensionOnly(), extension, "." + extension );
}

void Path::ChangeExtension( std::string extension )
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

	m_path = pathOut;
}

Path & Path::ChangeFilename( const Path & newFilename )
{
	return Combine( DirectoryOnly(), Path( newFilename.Filename() ) );
}

std::string Path::ToString() const
{
	return BeginsWith( m_path, XPathPrefix) ? StringMinusLeft( m_path, (unsigned int)XPathPrefix.length() ) : m_path;
}

std::string Path::ToString( Slash direction ) const
{
	std::string temp;

	switch (direction)
	{
	case Slash::Foward:
		temp = StringReplace( ToString(), "/", "\\" );
		break;
	case Slash::Backward:
		temp = StringReplace( ToString(), "\\", "/" );
		break;
	}
	return temp;
}

std::wstring Path::ToWString() const
{
	return std::wstring( m_path.begin(), m_path.end() );
}

std::wstring Path::ToWString( Slash direction ) const
{
	std::string temp( ToString( direction ) );
	return std::wstring( temp.begin(), temp.end() );
}

std::string Path::ToXPath() const
{
	return m_path;
}

std::wstring Path::ToWXPath() const
{
	return std::wstring( m_path.begin(), m_path.end() );
}

std::wstring Path::ToWXPath( Slash direction ) const
{
	std::string temp( ToString( direction ) );
	return std::wstring( temp.begin(), temp.end() );
}

bool Path::Delete()
{
	return remove( ToString().c_str() ) ? false : true;
}

bool Path::Rename( Path to )
{
	return rename( ToString().c_str(), to.ToString().c_str() ) ? false : true;
}

Path unify::ChangeExtension( Path path, std::string extension )
{
	Path outPath( path );
	outPath.ChangeExtension( extension );
	return outPath;
}

std::ostream & operator<<( std::ostream & os, const Path & path )
{
	os << path.ToString();
	return os;
}