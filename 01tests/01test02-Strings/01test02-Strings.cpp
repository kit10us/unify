// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test the unify::Any.
//

#include <iostream>
#include <unify/String.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "String" );
	{
		suite.BeginCase( "Replace" );
		suite.Assert( "no affect (something that doesn't exist)", unify::StringReplace( "abababab", "c", "d" ) == std::string( "abababab" ) );
		suite.Assert( "character with character", unify::StringReplace( "abababab", "a", "c" ) == std::string( "cbcbcbcb" ) );
		suite.Assert( "string with character", unify::StringReplace( "aabbaabbaabbaabb", "aa", "c" ) == std::string( "cbbcbbcbbcbb" ) );
		suite.Assert( "character with string", unify::StringReplace( "abababab", "a", "cd" ) == std::string( "cdbcdbcdbcdb" ) );
		suite.Assert( "string with string", unify::StringReplace( "aabbaabbaabbaabb", "aa", "cd" ) == std::string( "cdbbcdbbcdbbcdbb" ) );
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

	std::cout << "Press any Enter to finish...\n";
	std::cin.ignore();

	return 0;
}