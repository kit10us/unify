// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test the unify::Any.
//

#include <iostream>
#include <string>
#include <unify/Any.h>
#include <unify/TestSuite.h>

int main( int argc, char ** argv )
{
	using namespace unify;

	TestSuite testSuite( "Any", "   " );

	testSuite.BeginSuite();
	{
		testSuite.BeginCase( "Any not empty" );
		Any anyInt12 = 12;
		testSuite.Assert( "Any not empty", ! anyInt12.empty() );
		testSuite.EndCase();

		testSuite.BeginCase( "Int match" );
		testSuite.Assert( "Int match", unify::any_cast< int >( anyInt12 ) == 12 );
		testSuite.EndCase();
	}
	testSuite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	std::cin.ignore();

	return 0;
}