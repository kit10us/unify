// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/String.h>

// IsAlpha (is a letter)
bool unify::IsAlpha( const char ch )
{
	if( ch >= 'a' && ch <= 'z' ) return true;
	if( ch >= 'A' && ch <= 'Z' ) return true;
	return false;
}

// IsNumeric (is a number)
bool unify::IsNumeric( const char ch )
{
	if( ch >= '0' && ch <= '9' ) return true;
	return false;
}

/// <summary>
/// Compare two strings for equvilancy, ignoring case.
/// </summary>
bool unify::StringIs( std::string a, std::string b )
{
	return _stricmp( a.c_str(), b.c_str()) == 0;
}

/// <summary>
/// Compare a string for equvilancy with any of a list of strings, ignoring case.
/// </summary>
bool unify::StringIsAny( std::string a, const std::list< std::string > & list )
{
	for( const auto & b : list )
	{
		if( _stricmp( a.c_str(), b.c_str() ) == 0 ) return true;
	}
	return false;
}

bool unify::BeginsWith( std::string a, std::string b )
{
	if ( a.length() < b.length() ) return false;
	return StringIs( a.substr( 0, b.length() ), b );
}

bool unify::EndsWith( std::string a, std::string b )
{
	if ( a.length() < b.length() ) return false;
	return StringIs( a.substr( a.length() - b.length() ), b );
}

bool unify::StringIsInt( std::string sOne )
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

bool unify::StringIsFloat( std::string sOne )
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

// Removes all instances of character 'chr' from the left of 'stringIn'.
std::string unify::TrimLeft( std::string stringIn, const char chr )
{
	if ( stringIn.empty() ) return stringIn;
	unsigned int uCount = 0;
	for( uCount = 0; uCount < stringIn.length() && stringIn[ uCount ] == chr; uCount++ );
	return stringIn.erase( 0, uCount );
}

// Removes all instances of character 'chr' from the right of 'stringIn'.
std::string unify::TrimRight( std::string stringIn, const char chr )
{
	if ( stringIn.empty() ) return stringIn;
	unsigned int uCount = 0;
	for( uCount = 0; uCount >= 0  && stringIn[ stringIn.length() - (uCount + 1) ] == chr; uCount++ );
	return stringIn.erase( stringIn.length() - uCount, stringIn.length() - 1 );
}

// Performs both TrimLeft and TrimRight...
std::string unify::Trim( std::string stringIn, const char chr )
{
	return TrimRight( TrimLeft(  stringIn, chr ), chr );
}

// Returns a portion of a string (uLength)...
std::string unify::RightString( std::string stringIn, std::string::size_type uLength )
{
	if( stringIn.length() == 0 ) return std::string();
	if( uLength > stringIn.length() ) uLength = (unsigned int)stringIn.length();
	return stringIn.substr( stringIn.length() - uLength, uLength );
}

// Returns a portion of a string (uLength) from it's beginning...
std::string unify::LeftString( std::string stringIn, unsigned int uLength )
{
	return stringIn.substr( 0, uLength );
}

// Returns a string minus a portion from the front/left side of the string...
// new size = size - uLessLength
std::string unify::StringMinusLeft( std::string sStringIn, unsigned int uLessLength )
{
	if( uLessLength >= sStringIn.length() ) return std::string();
	return sStringIn.substr( uLessLength, (unsigned int)sStringIn.length() - uLessLength );
}

// Returns a string minus a portion from the end/right side of the string...
std::string unify::StringMinusRight( std::string sStringIn, unsigned int uLessLength )
{
	if( uLessLength >= sStringIn.length() ) return std::string();
	return sStringIn.substr( 0, (unsigned int)sStringIn.length() - uLessLength );
}

std::string unify::StringReplace( const std::string in, std::string find, std::string replace )
{
	std::string out;

	size_t left = 0;
	size_t right = 0;
	do
	{
		right = in.find( find, left );
		out += in.substr( left, right - left )  + replace;
		left = right + 1;
	} while ( right != std::string::npos );
	return out;	
}

std::string unify::CleanWhitespace( std::string in )
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

std::string unify::ToLower( std::string in )
{
	std::string out( in );
	for( std::size_t i = 0; i < in.length(); ++i )
	{
		char c = in[ i ];
		out[ i ] = (c >= 'A' && c <= 'Z') ? ( c + ('a' - 'A') ) : c;
	}
	return out;
}

std::string unify::ListPart( std::string sString, std::vector< char > seperators, int iPartIndex )
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

unsigned int unify::ListPartCount( std::string sString, std::vector< char > seperators )
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

bool unify::CaseInsensitiveLessThanTest::operator() (std::string string1, std::string string2) const
{
    return _stricmp(string1.c_str(), string2.c_str()) < 0;
}

bool unify::CaseInsensitiveLessThanTestCharPtr::operator() ( char * string1, char * string2 ) const
{
	return _stricmp( string1, string2 ) < 0;
}

std::vector< char > unify::SplitWhitespace()
{
	std::vector< char > splitDelimitors;
	splitDelimitors.push_back( ' ' );
	splitDelimitors.push_back( '\n' );
	splitDelimitors.push_back( '\t' );
	return splitDelimitors;
}
