// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test the unify::Any.
//

#include <iostream>
#include <unify/String.h>
#include <unify/TestSuite.h>

int main( int argc, char ** argv )
{
	using namespace unify;

	TestSuite testSuite( "String", "   " );

	testSuite.BeginSuite();
	{
		testSuite.BeginCase( "Replace" );
		testSuite.Assert( "no affect (something that doesn't exist)", unify::StringReplace( "abababab", "c", "d" ) == std::string( "abababab" ) );
		testSuite.Assert( "character with character", unify::StringReplace( "abababab", "a", "c" ) == std::string( "cbcbcbcb" ) );
		testSuite.Assert( "string with character", unify::StringReplace( "aabbaabbaabbaabb", "aa", "c" ) == std::string( "cbbcbbcbbcbb" ) );
		testSuite.Assert( "character with string", unify::StringReplace( "abababab", "a", "cd" ) == std::string( "cdbcdbcdbcdb" ) );
		testSuite.Assert( "string with string", unify::StringReplace( "aabbaabbaabbaabb", "aa", "cd" ) == std::string( "cdbbcdbbcdbbcdbb" ) );
		testSuite.EndCase();

		testSuite.BeginCase( "Misc." );
		testSuite.Assert( "CleanWhitespace", CleanWhitespace( " \t \t \n  no \t  \t whitespace \t \t \n \n  " ) == "no whitespace" );
		testSuite.Assert( "Begins with succeed", BeginsWith( "a new town", "a ne" ) == true );
		testSuite.Assert( "Begins with fail",  BeginsWith( "a new town", "new " ) == false );
		testSuite.Assert( "Ends with succeed", EndsWith( "a new town", " town" ) == true );
		testSuite.Assert( "Ends with fail", EndsWith( "a new town", "new " ) == false );
		testSuite.Assert( "ToLower", ToLower( "All Lower Case, Zero UPPER!" ) == "all lower case, zero upper!" );
		testSuite.Assert( "ToUpper", ToUpper( "All Lower Case, Zero UPPER!" ) == "ALL LOWER CASE, ZERO UPPER!" );
		testSuite.EndCase();
	}
	testSuite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	std::cin.ignore();

	return 0;
}