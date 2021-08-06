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


template< typename foo, typename ... bar >
bool unify::string::StringIs( std::string a, std::string b, std::string rest... )
{
	if (StringIs(a, b ))
	{
		return true;
	}
	return string::StringIs( a, rest );
}

template< typename T >
std::vector< T > unify::string::Split( std::string sourceString, const char delimitor )
{
	std::vector< T > destination;
	std::stringstream ss( sourceString );
	std::string item;
	while( std::getline( ss, item, delimitor ) ) 
	{
		destination.push_back( Cast< T >( item ) );
	}
	return destination;
}

template< typename T >
std::vector< T > unify::string::Split( std::string sourceString, const std::vector< char > & delimitors, bool includeEmpties )
{
	std::vector< T > destination;

	size_t start = 0;
	size_t end = 0;
	for( end = 0; end < sourceString.size(); ++end )
	{
		if ( std::find( delimitors.begin(), delimitors.end(), sourceString.at( end ) ) != delimitors.end() )
		{
			if ( start == end )
			{
				if ( includeEmpties )
				{
					destination.push_back( T() );
				}
			}
			else
			{
				destination.push_back( Cast< T >( sourceString.substr( start, end - start ) ) );
			}
			start = end + 1;
		}
	}

	if ( start == end )
	{
		if ( includeEmpties )
		{
			destination.push_back( T() );
		}
	}
	else
	{
		destination.push_back( Cast< T >( sourceString.substr( start, end - start ) ) );
	}

	return destination;
}

template< typename T >
std::vector< T > unify::string::SplitOnWhitespace( std::string sourceString )
{
	std::vector< char > delimitors;
	delimitors.push_back( ' ' );
	delimitors.push_back( '\t' );
	delimitors.push_back( '\n' );
	return Split< T >( sourceString, delimitors );
}
