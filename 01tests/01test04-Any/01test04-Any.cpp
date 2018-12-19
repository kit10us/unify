// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test the Any.
//

#include <string>
#include <conio.h>
#include <unify/Any.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "Any" );
	{
		suite.BeginCase( "Any not empty" );
		Any anyInt12 = 12;
		suite.Assert( "Any not empty", ! anyInt12.empty() );
		suite.EndCase();

		suite.BeginCase( "Int match" );
		suite.Assert( "Int match", any_cast< int >( anyInt12 ) == 12 );
		suite.EndCase();
	}
	suite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	while( ! _getch() );

	return 0;
}