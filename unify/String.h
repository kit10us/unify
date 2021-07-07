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
#include <unify/Cast.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>

namespace unify
{
	namespace string
	{
		// Char
		bool IsAlpha( const char ch );
		bool IsNumeric( const char ch );

		/// <summary>
		/// Compare two strings for equvilancy, ignoring case.
		/// </summary>
		bool StringIs( std::string a, std::string is );
			
		/// <summary>
		/// Compare mutliple strings for equvilancy, ignoring case.
		/// </summary>
		template< typename foo = std::string, typename... bar >
		bool StringIs( std::string a, std::string is, std::string Rest... );

		/// <summary>
		/// Compare a string for equvilancy with any of a list of strings, ignoring case.
		/// </summary>
		bool StringIsAny( std::string a, const std::list< std::string > & list );

		/// <summary>
		/// Returns true if source begins with the string beginsWith.
		/// </summary>
		bool BeginsWith( std::string source, std::string beginsWith );

		/// <summary>
		/// Returns true if the source ends with the string endsWith.
		/// </summary>
		bool EndsWith( std::string source, std::string endsWith );
	
		bool StringIsInt( std::string sOne );
		bool StringIsFloat( std::string sOne );

		/// <summary>
		/// Removes all instances of character 'chr' from the left of 'stringIn'.
		/// </summary>
		std::string TrimLeft( std::string stringIn, const char chr );

		/// <summary>
		/// Removes all instances of character 'chr' from the right of 'stringIn'.
		/// </summary>
		std::string TrimRight( std::string stringIn, const char chr );

		/// <summary>
		/// Performs both TrimLeft and TrimRight...
		/// </summary>
		std::string Trim( std::string stringIn, const char chr = ' ' );

		/// <summary>
		/// Retruns the trimmed string from a specific string, exclusive.
		/// </summary>
		std::string TrimFrom( std::string stringIn, std::string to );

		/// <summary>
		/// Returns the trimmed string to a specific string, exclusive.
		/// </summary>
		std::string TrimTo( std::string stringIn, const char from );

		std::string RightString( std::string stringIn, std::string::size_type uLength );
		std::string LeftString( std::string stringIn, unsigned int uLength );
		std::string StringMinusLeft( std::string sStringIn, unsigned int uLessLength );
		std::string StringMinusRight( std::string sStringIn, unsigned int uLessLength );

		/// <summary>
		/// Replace every instance of "find" within the "in" string with "replace".
		/// </summary>
		std::string StringReplace( const std::string in, std::string find, std::string replace );
	
		/// <summary>
		/// Returns a string where all sets (single or in a row) cariage returns, tabs or spaces are replaced with one space.
		/// For example, "\n\n\n  \t\tHello,  \tWorld\n!     \t\n "  >>  "Hello, World!" (note: no leading or training spaces either)
		/// Doesn't reduce ANY single spaces.
		/// </summary>
		std::string CleanWhitespace( std::string sIn );

		std::string ToLower( std::string in );
		std::string ToUpper( std::string in );
	
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
	} // namespace string
} // namespace unify
