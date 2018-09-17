// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test various Unify features that are too small a scope to deserve a seperate test suite.
//    Test may be promoted to seperate suites as desired.
//

#include <iostream>
#include <unify/Color.h>
#include <unify/ColorUnit.h>
#include <unify/V2.h>
#include <unify/Parameters.h>
#include <unify/Optional.h>
#include <unify/TestSuite.h>

int main( int argc, char ** argv )
{
	using namespace unify;

	TestSuite testSuite( "General", "   " );

	testSuite.BeginSuite();
	{
		testSuite.BeginCase( "String casts" );
		testSuite.Assert( "float conversion", Cast< float >( "   12.21  " ) == 12.21f );
		testSuite.Assert( "unsigned char conversion", Cast< unsigned char >( "   12  " ) == 12 );
		testSuite.Assert( "int conversion", Cast< int >( "   12  " ) == 12 );
		testSuite.Assert( "bool conversion true", Cast< bool >( "   true  " ) == true );
		testSuite.Assert( "bool conversion false", Cast< bool >( "   false  " ) == false );
		testSuite.EndCase();

		testSuite.BeginCase( "Color" );
		testSuite.Assert( "Color from text", Color( "255, 127, 63, 31" ) == Color::ColorRGBA( 255, 127, 63, 31 ) );
		testSuite.EndCase();

		testSuite.BeginCase( "ColorUnit" );
		testSuite.Assert( "ColorUnit from text", ColorUnit( "1, 0.5, 0.25, 0.125" ) == ColorUnit::ColorUnitRGBA( 1, 0.5, 0.25, 0.125 ) ); 
		testSuite.EndCase();

		testSuite.BeginCase( "Parameter" );
		Parameters parameters;
		parameters.Set( "first", 1234567 );
		parameters.Set( "second", "second" );
		parameters.Set( "third", 3.33f );
		testSuite.Assert( "verify value of first parameter, int", parameters.Get< int >( "first" ) == (int)1234567 );
		testSuite.Assert( "verify parameter \"second\" exists", parameters.Exists( "second" ) );
		testSuite.EndCase();

		// Optional test...
		{
			/*
			TODO: When used, so we know what we need to test.
			Optional< int > optionalInt12 = 12;
			Optional< int > optionalInt;
			cout << "Optional< int >( ) == Not Set : " << (optionalInt.IsSet() ? "FAIL" : "PASS") << endl;
			cout << "Optional< int >( 12 ) == 12 : " << (optionalInt12 == 12 ? "PASS" : "FAIL") << endl;
			*/
		}
	}
	testSuite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	std::cin.ignore();

    return 0;
}