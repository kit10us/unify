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


/// <summary>
/// Test the Any.
/// </summary>

#include <unify/String.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;
	using namespace string;

	Suite suite;

	suite.BeginSuite( "String" );
	{
		suite.BeginCase( "StringIs" );
		suite.Assert( "single is", StringIs( "first", "first" ) );
		suite.Assert( "single is not", !StringIs( "first", "second" ) );
		suite.Assert("single is mixed case", StringIs("first", "FiRsT"));
		suite.Assert( "mutliple mixed case is", StringIs( "first", "FIRST", "FiRst" ) );
		suite.Assert( "mutliple mixed case is not", !StringIs( "first", "second", "third" ) );
		suite.EndCase();

		suite.BeginCase("StringIsAny");
		suite.Assert("single is any", StringIsAny("first", { "first" }));
		suite.Assert("single is not any", !StringIsAny("first", { "second" }));
		suite.Assert("multiple is any", StringIsAny("first", { "second", "first", "third" }));
		suite.Assert("multiple is not any", !StringIsAny("first", { "second", "fourth", "third" }));
		suite.EndCase();

		suite.BeginCase( "Replace" );
		suite.Assert( "no affect (something that doesn't exist)", StringReplace( "abababab", "c", "d" ) == std::string( "abababab" ) );
		suite.Assert( "character with character", StringReplace( "abababab", "a", "c" ) == std::string( "cbcbcbcb" ) );
		suite.Assert( "string with character", StringReplace( "aabbaabbaabbaabb", "aa", "c" ) == std::string( "cbbcbbcbbcbb" ) );
		suite.Assert( "character with string", StringReplace( "abababab", "a", "cd" ) == std::string( "cdbcdbcdbcdb" ) );
		suite.Assert( "string with string", StringReplace( "aabbaabbaabbaabb", "aa", "cd" ) == std::string( "cdbbcdbbcdbbcdbb" ) );
		suite.EndCase();

		suite.BeginCase("Split");
		std::vector<std::string> results;
		results = Split<std::string>("one,two,three", { ',' });
		suite.Assert("Split number of elements", results.size() == 3);
		suite.Assert("First word \"one\"", results[0] == "one");
		suite.Assert("Second word \"one\"", results[1] == "two");
		suite.Assert("Thrid word \"one\"", results[2] == "three");
		suite.EndCase();

		suite.BeginCase( "Misc." );
		suite.Assert( "CleanWhitespace", CleanWhitespace( " \t \t \n  no \t  \t whitespace \t \t \n \n  " ) == "no whitespace" );
		suite.Assert( "Begins with succeed", BeginsWith( "a new town", "a ne" ) == true );
		suite.Assert( "Begins with fail",  BeginsWith( "a new town", "new " ) == false );
		suite.Assert( "Ends with succeed", EndsWith( "a new town", " town" ) == true );
		suite.Assert( "Ends with fail", EndsWith( "a new town", "new " ) == false );
		suite.Assert( "ToLower", ToLower( "All Lower Case, Zero UPPER!" ) == "all lower case, zero upper!" );
		suite.Assert( "ToUpper", ToUpper( "All Lower Case, Zero UPPER!" ) == "ALL LOWER CASE, ZERO UPPER!" );
		suite.EndCase();
	}
	suite.EndSuite();
	return 0;
}