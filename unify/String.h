// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/Cast.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>

namespace unify
{
	// Char
	bool IsAlpha( const char ch );
	bool IsNumeric( const char ch );

	// Caseless compare.
	bool StringIs( std::string a, std::string b );
	bool StringIsAny( std::string a, const std::list< std::string > & list );
	bool BeginsWith( std::string a, std::string b );
	bool EndsWith( std::string a, std::string b );
	
	bool StringIsInt( std::string sOne );
	bool StringIsFloat( std::string sOne );

	std::string TrimLeft( std::string stringIn, const char chr );
	std::string TrimRight( std::string stringIn, const char chr );
	std::string Trim( std::string stringIn, const char chr = ' ' );
	std::string RightString( std::string stringIn, std::string::size_type uLength );
	std::string LeftString( std::string stringIn, unsigned int uLength );
	std::string StringMinusLeft( std::string sStringIn, unsigned int uLessLength );
	std::string StringMinusRight( std::string sStringIn, unsigned int uLessLength );
	std::string StringReplace( const std::string in, std::string find, std::string replace );
	
	/// <summary>
	/// Returns a string where all sets (single or in a row) cariage returns, tabs or spaces are replaced with one space.
	/// For example, "\n\n\n  \t\tHello,  \tWorld\n!     \t\n "  >>  "Hello, World!" (note: no leading or training spaces either)
    /// Doesn't reduce ANY single spaces.
	/// </summary>
	std::string CleanWhitespace( std::string sIn );

	std::string ToLower( std::string in );

	
	// Considers a string as a part of a segmented list by a character, returns that part of the list...
	// Returns ASAP.
	// The first iPartIndex is 0.
	std::string ListPart( std::string sString, std::vector< char > seperators, int iPartIndex );	
	unsigned int ListPartCount(std::string sString, std::vector< char > seperators );

	// Binary functor for case insensitive string compares. Useful for maps.
    class CaseInsensitiveLessThanTest
    {
    public:
        bool operator() (std::string string1, std::string string2) const;
    };  

	// Binary functor for case insensitive string compares. Useful for maps.
	class CaseInsensitiveLessThanTestCharPtr
	{
	public:
		bool operator() ( char * string1, char * string2 ) const;
	};

	// TODO: For our needs, multiple spaces as delimitors need to be considered as one.
	template< typename T >
	std::vector< T > Split( std::string sourceString, const char delimitor );

	/// <summar>
	/// Returns a vector of whitespace characters including space, newline, and tab.
	std::vector< char > SplitWhitespace();

	/// <summary>
	/// Split a string into a vector of string pieces based on multiple delimitors. includeEmpties effectively includes empty strings if mutliple delimitors
	/// occur in a row. eq. 
	/// </summary>
	/// <example>
	/// "a,,b,c" = ["a", "b", "c" ] { if includeEmtpies = false } else = ["a", "", "b", "c"]
	/// (' ', '\n')"a b   c\n  d" = [ "a", "b", "c", "d" ]{ if includeEmtpies = false } else = ["a", "", "", "b", "c", "" (for '\n'), ""]
	/// </example>
	template< typename T >
	std::vector< T > Split( std::string sourceString, const std::vector< char > & delimitors, bool includeEmpties = false );

	template< typename T >
	std::vector< T > SplitOnWhitespace( std::string sourceString );

	#include <unify/String.inl>
} // namespace unify
