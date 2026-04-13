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

namespace unify
{
	inline
	bool Path::IsXPath( std::string path )
	{
		return unify::String::BeginsWith( path, XPathPrefix );
	}

	inline
	Path::Path()
	{
	}

	inline
	Path::Path( std::string path )
		: m_path{ String::BeginsWith( path, XPathPrefix ) ? path : XPathPrefix + path }
	{
	}

	inline
	Path::Path( char * path )
		: m_path{ String::BeginsWith( path, XPathPrefix ) ? path : XPathPrefix + path }
	{
	}

	inline
	Path::Path( Path left, Path right )
	{
		Combine( left, right );
	}

	inline
	Path::Path( const std::vector< std::string > & pathParts )
	{
		Join( pathParts );
	}

	inline
	Path & Path::operator=( const Path & path )
	{
		m_path = path.m_path;
		return *this;
	}

	inline
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

	inline
	bool Path::operator!=( const Path & path ) const
	{
		return !( *this == path );
	}

	inline
	Path Path::operator+( const Path & path )
	{
		Path newPath( *this, path );
		return newPath;
	}

	inline
	Path & Path::operator+=( const Path & path )
	{
		Combine( *this, path );
		return *this;
	}

	inline
	bool Path::Empty() const
	{
		return m_path.empty();
	}

	inline
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

	inline
	Path & Path::Join( const std::vector< std::string > & pathParts )
	{
		m_path = std::string();
		for ( std::vector< std::string >::const_iterator itr = pathParts.begin(), end = pathParts.end(); itr != end; ++itr )
		{
			Combine( *this, Path( *itr ) );
		}
		return *this;
	}

	inline
	Path & Path::Normalize()
	{
		std::vector< std::string > parts = Split();
		for ( std::vector< std::string >::const_iterator itr = parts.begin(); itr != parts.end(); ++itr )
		{
			if ( itr != parts.begin() && String::BeginsWith( *itr, ".." ) )
			{
				itr = parts.erase( itr - 1 ); // Erase what ever leads.
				itr = parts.erase( itr ); // Erase the "..".
			}
			else if ( itr != parts.begin() && String::BeginsWith( *itr, "." ) )
			{
				itr = parts.erase( itr ); // Erase the ".".
			}
		}
		return Join( parts );
	}

	inline
	bool Path::Exists() const
	{
		if (IsDirectory())
		{
			return std::filesystem::is_directory(ToPath());
		}
		else
		{
			std::ifstream ifile(ToString());
			return ifile ? true : false;
		}
	}

	inline
	std::string Path::ExtensionOnly() const
	{
		size_t i = m_path.find_last_of( "./\\" );
		if ( i == std::string::npos )
		{
			return {};
		}
		else if ( m_path[ i ] == '.' )
		{
			return m_path.substr( i );
		}

		return {};
	}

	inline
	Path Path::DirectoryOnly() const
	{
		size_t i = m_path.find_last_of( ":/\\" );
		if ( i == std::string::npos )
		{
			return {};
		}
		else
		{
			std::string s = m_path.substr( 0, i + 1 );
			return Path( m_path.substr( 0, i + 1 ) );
		}
	}

	inline
	bool Path::HasExtension() const
	{
		return !this->ExtensionOnly().empty();
	}

	inline
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

	inline
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

	inline
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
		char lastChar = String::RightString( left.ToString(), 1 )[ 0 ];
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

	inline
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

	inline
	bool Path::IsExtension( std::string extension ) const
	{
		return String::StringIs( ExtensionOnly(), extension, "." + extension );
	}

	inline
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

	inline
	Path & Path::ChangeFilename( const Path & newFilename )
	{
		return Combine( DirectoryOnly(), Path( newFilename.Filename() ) );
	}

	inline
	std::string Path::ToString() const
	{
		return String::BeginsWith( m_path, XPathPrefix) ? String::StringMinusLeft( m_path, (unsigned int)XPathPrefix.length() ) : m_path;
	}

	inline
	std::string Path::ToString( Slash direction ) const
	{
		std::string temp;

		switch (direction)
		{
		case Slash::Foward:
			temp = String::StringReplace( ToString(), "/", "\\" );
			break;
		case Slash::Backward:
			temp = String::StringReplace( ToString(), "\\", "/" );
			break;
		}
		return temp;
	}

	inline
	std::wstring Path::ToWString() const
	{
		return std::wstring( m_path.begin(), m_path.end() );
	}

	inline
	std::wstring Path::ToWString( Slash direction ) const
	{
		std::string temp( ToString( direction ) );
		return std::wstring( temp.begin(), temp.end() );
	}

	inline
	std::string Path::ToXPath() const
	{
		return m_path;
	}

	inline
	std::wstring Path::ToWXPath() const
	{
		return std::wstring( m_path.begin(), m_path.end() );
	}

	inline
	std::wstring Path::ToWXPath( Slash direction ) const
	{
		std::string temp( ToString( direction ) );
		return std::wstring( temp.begin(), temp.end() );
	}

	inline
	std::filesystem::path Path::ToPath() const
	{
		return std::filesystem::path(ToString());
	}

	inline
	bool Path::Delete()
	{
		return remove( ToString().c_str() ) ? false : true;
	}

	inline
	bool Path::Rename( Path to )
	{
		return rename( ToString().c_str(), to.ToString().c_str() ) ? false : true;
	}

	inline
	std::list<Path> Path::Files() const
	{
		if (!IsDirectory())
		{
			return { *this };
		}

		std::list<Path> files{};
		for (auto const& entry : std::filesystem::directory_iterator{DirectoryOnly().ToString()})
		{
			auto path = Path{ entry.path().string() };
			files.push_back(path);
		}

		return files;
	}

	inline
	Path unify::ChangeExtension( Path path, std::string extension )
	{
		Path outPath( path );
		outPath.ChangeExtension( extension );
		return outPath;
	}

	inline
	std::ostream & operator<<( std::ostream & os, const Path & path )
	{
		os << path.ToString();
		return os;
	}
}