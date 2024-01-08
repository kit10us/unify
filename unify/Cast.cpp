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

#include <unify/Cast.h>
#include <unify/String.h>

#pragma warning(push)
#pragma warning(disable : 4244) // 'argument' : conversion from ... to ..., possible loss of data

template<>
std::string unify::Cast( const std::string in )
{
	return in;
}

template<>
std::string unify::Cast( const std::wstring in )
{
	return std::string( in.begin(), in.end() );
}

template<>
std::string unify::Cast( const bool in )
{
	return in ? "true" : "false";
}

template<>
std::string unify::Cast( const unsigned char in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const char in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const unsigned int in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast(const unsigned __int64 in)
{
	return std::to_string(in);
}


template<>
std::string unify::Cast( const int in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const float in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const double in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const unsigned short in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const short in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const unsigned long in )
{
	return std::to_string(in);
}

template<>
std::string unify::Cast( const long in )
{
	return std::to_string(in);
}

template<> 
bool unify::Cast( const std::string text )
{
	std::string temp = string::Trim( text );
	if ( string::StringIs( temp, "false" ) || string::StringIs( temp, "f" ) || string::StringIs( temp, "0" ) || string::StringIs( temp, "no" ) )
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<>
char unify::Cast( const std::string text )
{
	return (char)( ! text.empty() ? atoi( text.c_str() ) : 0 );
}

template<>
unsigned char unify::Cast( const std::string text )
{
	return (unsigned char )Cast< unsigned int >( text );
}

template<>
int unify::Cast( const std::string text )
{
	return( ! text.empty() ? atoi( text.c_str() ) : 0 );
}

template<>
unsigned int unify::Cast( const std::string text )
{
	return( ! text.empty() ? strtoul( text.c_str(), 0, 0 ) : 0 );
}

template<>
unsigned __int64 unify::Cast(const std::string text)
{
	return(!text.empty() ? strtoull(text.c_str(), 0, 0) : 0);
}

template<>
float unify::Cast( const std::string text )
{
	return (float)Cast< double >( text );
}

template<>
double unify::Cast( const std::string text )
{
	return( ! text.empty() ? atof( text.c_str() ) : 0 );
}

template<>
wchar_t * unify::Cast( const std::string text )
{
	if( text.empty() ) return NULL;

	const char * lpszIn = text.c_str();
	unsigned int uLength = 0;
	while( lpszIn[ uLength++ ] != 0 );
	wchar_t * lpszOut = new wchar_t[ uLength ];
	uLength = 0;
	while( lpszIn[ uLength ] != 0 )
	{
		wchar_t c = (wchar_t)lpszIn[ uLength ];
		lpszOut[ uLength ] = c;
		uLength++;
	}
	lpszOut[ uLength ] = 0;
	return lpszOut;
}

template<>
short unify::Cast( const std::string text )
{
	return (short)( ! text.empty() ? atoi( text.c_str() ) : 0 );
}

template<>
unsigned short unify::Cast( const std::string text )
{
	return(unsigned short)( ! text.empty() ? strtoul( text.c_str(), 0, 0 ) : 0 );
}

template<>
std::wstring unify::Cast( const std::string text )
{
	return std::wstring( text.begin(), text.end() );
}

template<> unify::Path unify::Cast( const std::string text )
{
	return unify::Path( text );
}

template<>
bool unify::Cast( const char * text )
{
	return Cast< bool, std::string >( text );
}

template<>
char unify::Cast( const char * text )
{
	return Cast< char, std::string >( text );
}

template<>
unsigned char unify::Cast( const char * text )
{
	return Cast< unsigned char, std::string >( text );
}

template<>
int unify::Cast( const char * text )
{
	return Cast< int, std::string >( text );
}

template<>
unsigned int unify::Cast( const char * text )
{
	return Cast< unsigned int, std::string >( text );
}

template<>
unsigned __int64 unify::Cast(const char* text)
{
	return Cast< unsigned __int64, std::string >(text);
}

template<>
float unify::Cast( const char * text )
{
	return Cast< float, std::string >( text );
}

template<>
double unify::Cast( const char * text )
{
	return Cast< double, std::string >( text );
}

template<>
wchar_t * unify::Cast( const char * text )
{
	return Cast< wchar_t *, std::string >( text );
}

template<>
std::string unify::Cast( const char * text )
{
	return std::string( text );
}

template<> 
std::string unify::Cast( const wchar_t * text )
{
	return Cast< std::string >( std::wstring( text ) );
}


#pragma warning(pop)
