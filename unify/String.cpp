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


#include <unify/String.h>

// IsAlpha (is a letter)
bool unify::string::IsAlpha( const char ch )
{
	if( ch >= 'a' && ch <= 'z' ) return true;
	if( ch >= 'A' && ch <= 'Z' ) return true;
	return false;
}

// IsNumeric (is a number)
bool unify::string::IsNumeric( const char ch )
{
	if( ch >= '0' && ch <= '9' ) return true;
	return false;
}

bool unify::string::StringIs( std::string a, std::string is )
{
	return _stricmp( a.c_str(), is.c_str()) == 0;
}

bool unify::string::StringIsAny( std::string a, const std::list< std::string > & list )
{
	for( const auto & b : list )
	{
		if( _stricmp( a.c_str(), b.c_str() ) == 0 ) return true;
	}
	return false;
}

bool unify::string::BeginsWith( std::string source, std::string beginsWith )
{
	if ( source.length() < beginsWith.length() ) return false;
	return StringIs( source.substr( 0, beginsWith.length() ), beginsWith );
}

bool unify::string::EndsWith( std::string source, std::string endsWith )
{
	if ( source.length() < endsWith.length() ) return false;
	return StringIs( source.substr( source.length() - endsWith.length() ), endsWith );
}

bool unify::string::StringIsInt( std::string sOne )
{
	const char * pChar = sOne.c_str();
	if( *pChar == '-' ) pChar++;
	while( *pChar ) 
	{
		if( *pChar < '0' || *pChar > '9' ) return 0;
		pChar++;
	}
	return 1;
}

bool unify::string::StringIsFloat( std::string sOne )
{
	const char * pChar = sOne.c_str();
	if( *pChar == '-' ) pChar++;
	while( *pChar ) 
	{
		if( (*pChar < '0' || *pChar > '9') && *pChar != '.' ) 
		{
			if( (*pChar == 'f' || *pChar == 'F') && pChar[1] == 0 ) return 1;
			return 0;
		}
		pChar++;
	}
	return 1;
}

/// <summary>
/// Removes all instances of character 'chr' from the left of 'stringIn'.
/// </summary>
std::string unify::string::TrimLeft( std::string stringIn, char chr )
{
	if ( stringIn.empty() ) return stringIn;
	unsigned int uCount = 0;
	for( uCount = 0; uCount < stringIn.length() && stringIn[ uCount ] == chr; uCount++ );
	return stringIn.erase( 0, uCount );
}

/// <summary>
/// Removes all instances of character 'chr' from the right of 'stringIn'.
/// </summary>
std::string unify::string::TrimRight( std::string stringIn, char chr )
{
	if ( stringIn.empty() ) return stringIn;
	unsigned int uCount = 0;
	for( uCount = 0; uCount >= 0  && stringIn[ stringIn.length() - (uCount + 1) ] == chr; uCount++ );
	return stringIn.erase( stringIn.length() - uCount, stringIn.length() - 1 );
}

/// <summary>
/// Performs both TrimLeft and TrimRight...
/// </summary>
std::string unify::string::Trim( std::string stringIn, char chr )
{
	return TrimRight( TrimLeft(  stringIn, chr ), chr );
}

/// <summary>
/// Retruns the trimmed string from a specific string, exclusive.
/// </summary>
std::string unify::string::TrimFrom( std::string stringIn, std::string from )
{
	size_t i = stringIn.find( from );
	if ( i == std::string::npos )
	{
		return stringIn;
	}
	else
	{
		return stringIn.substr( 0, stringIn.length() - i );
	}
}

/// <summary>
/// Returns the trimmed string to a specific string, exclusive.
/// </summary>
std::string unify::string::TrimTo( std::string stringIn, const char to )
{
	size_t begins = 0;
	size_t i = 0;
	while( ( i = stringIn.find( to ) ) != std::string::npos )
	{
		begins = i;
	}
	return stringIn.substr( begins );
}

// Returns a portion of a string (uLength)...
std::string unify::string::RightString( std::string stringIn, std::string::size_type uLength )
{
	if( stringIn.length() == 0 ) return std::string();
	if( uLength > stringIn.length() ) uLength = (unsigned int)stringIn.length();
	return stringIn.substr( stringIn.length() - uLength, uLength );
}

// Returns a portion of a string (uLength) from it's beginning...
std::string unify::string::LeftString( std::string stringIn, unsigned int uLength )
{
	return stringIn.substr( 0, uLength );
}

// Returns a string minus a portion from the front/left side of the string...
// new size = size - uLessLength
std::string unify::string::StringMinusLeft( std::string sStringIn, unsigned int uLessLength )
{
	if( uLessLength >= sStringIn.length() ) return std::string();
	return sStringIn.substr( uLessLength, (unsigned int)sStringIn.length() - uLessLength );
}

// Returns a string minus a portion from the end/right side of the string...
std::string unify::string::StringMinusRight( std::string sStringIn, unsigned int uLessLength )
{
	if( uLessLength >= sStringIn.length() ) return std::string();
	return sStringIn.substr( 0, (unsigned int)sStringIn.length() - uLessLength );
}

std::string unify::string::StringReplace( const std::string in, std::string find, std::string replace )
{
	if ( find.length() == 0 )
	{
		return in;
	}

	std::string out;

	size_t left = 0; // Our search starting index.
	size_t right = 0; // Our right, found/not found, end index.
	do
	{
		right = in.find( find, left );

		// Break out of loop as soon as we can't find any more instances of the string.
		if( right == std::string::npos )
		{
			// Append the rest of the left over string.
			out += in.substr( left, std::string::npos );
			break;
		}

		// Replace instance of found value with replacement value.
		out += in.substr( left, right - left )  + replace;
		left = right + find.length();
	} while ( right != std::string::npos ); // Just an arbitrary catch all to ensure we don't loop infinitly, even if just to be clear.
	return out;	
}

std::string unify::string::CleanWhitespace( std::string in )
{
	if ( in.empty() ) return std::string();

	// Find the first and last non-whitespace character...
	size_t left = 0, right = in.length();
	for( left; left < right && ( in[ left ] == ' ' || in[ left ] == '\t' || in[ left ] == '\n' ); ++left );
	for( right; left < ( right - 1 ) && ( in[ right - 1 ] == ' ' || in[ right - 1 ] == '\t' || in[ right - 1 ] == '\n' ); --right );

	if( left == right ) return std::string();

	std::string out{};
	bool skipSpace = false;
	for( size_t i = left; i < right; ++i )
	{
		if ( in[ i ] == ' ' || in[ i ] == '\t' || in[ i ] == '\n' )
		{
			if( skipSpace ) continue;
			out.push_back( ' ' );
			skipSpace = true;
		}
		else
		{
			skipSpace = false;
			out.push_back( in[i] );
		}
	}

	return out;
}

std::string unify::string::ToLower( std::string in )
{
	std::string out( in );
	for( std::size_t i = 0; i < in.length(); ++i )
	{
		char c = in[ i ];
		out[ i ] = (c >= 'A' && c <= 'Z') ? ( 'a' + (c - 'A') ) : c;
	}
	return out;
}

std::string unify::string::ToUpper( std::string in )
{
	std::string out( in );
	for (std::size_t i = 0; i < in.length(); ++i)
	{
		char c = in[i];
		out[i] = (c >= 'a' && c <= 'z') ? ('A' + (c - 'a')) : c;
	}
	return out;
}

std::string unify::string::ListPart( std::string sString, std::vector< char > seperators, int iPartIndex )
{
	if( sString == "" ) return "";

	auto isSeperator = [seperators]( char c ){ auto itr = seperators.begin(), end = seperators.end(); for( ; itr != end && c != *itr; ++itr ); return itr != end; };
										 
	int iInBrackets = 0;	// How deep in brackets we are
	bool bInQuote = false;	// In quotations
	int pc = 0;				//Part count ( part we are on)
	int iStart = 0, iLenToCopy = 0;

	for( int c = 0; c < (int)sString.length(); c++ )
	{
		//Brackets... <...>
		//if (!bInQuote && (szString[c] == '<' || szString[c] == '[' || szString[c] == '('))	iInBrackets++;
		//if (!bInQuote && (szString[c] == '>' || szString[c] == ']' || szString[c] == ')')) iInBrackets--;
		if( sString[c] == '\"' ) bInQuote = !bInQuote;
		
		// Check for the seperator...
		if( !bInQuote && !iInBrackets && isSeperator( sString[c]  ) ) {
			pc++;

			if( pc == iPartIndex ) {
				iStart = c + 1;	// Set our starting poit to the next character
			}
			if( pc > iPartIndex ) break;
		}
		else if( pc == iPartIndex ) iLenToCopy++;
	}

	// Check if our end has been set (if not, we never found our string
	if( iLenToCopy == 0 ) return "";

	return sString.substr( iStart, iLenToCopy );
}

unsigned int unify::string::ListPartCount( std::string sString, std::vector< char > seperators )
{
	if( sString == "" ) return 0;

	auto isSeperator = [ seperators ]( char c ) { auto itr = seperators.begin(), end = seperators.end(); for( ; itr != end && c != *itr; ++itr ); return itr != end; };

	int iInBrackets = 0;
	bool bInQuote = false; //in quotations
	unsigned int pc = 0; //Part count
	for( int c = 0; c < (int)sString.length(); c++ )
	{

		// Brackets... <...>
		if( sString[c] == '<' ) {
			iInBrackets++;
			continue;
		}
		if( sString[c] == '>' ) {
			iInBrackets--;
			continue;
		}
		if( iInBrackets != 0 ) continue;

		// Quotes...
		if( sString[c] == '\"' )
		{
			bInQuote = !bInQuote;
			continue;
		}
		
		if( bInQuote ) continue;

		if( isSeperator( sString[c] ) ) pc++;
	}
	
	return pc + 1;
}

bool unify::string::CaseInsensitiveLessThanTest::operator() (std::string string1, std::string string2) const
{
    return _stricmp(string1.c_str(), string2.c_str()) < 0;
}

bool unify::string::CaseInsensitiveLessThanTestCharPtr::operator() ( char * string1, char * string2 ) const
{
	return _stricmp( string1, string2 ) < 0;
}

std::vector< char > unify::string::SplitWhitespace()
{
	std::vector< char > splitDelimitors;
	splitDelimitors.push_back( ' ' );
	splitDelimitors.push_back( '\n' );
	splitDelimitors.push_back( '\t' );
	return splitDelimitors;
}
