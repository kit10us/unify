// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test varois Unify geometry features.
//

#include <conio.h>
#include <string>
#include <unify/FastMap.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	FastMap< std::string, int > stringIntFastMap;

	suite.BeginSuite( "FastMap" );
	{
		suite.BeginCase( "Count is correct" );
		{
			suite.Assert( "count is 0", stringIntFastMap.Count() == 0 );
		}
		suite.EndCase();

		suite.BeginCase( "Adding values" );
		{
			suite.TryCatch( "key not value (default), \"default\"", [&]{ stringIntFastMap.Add( "default" ); }, false );
			suite.TryCatch( "key \"first\"", [&]{ stringIntFastMap.Add( "first", 1 ); }, false );
			suite.TryCatch( "key \"second\"", [&]{ stringIntFastMap.Add( "second", 2 ); }, false );
			suite.TryCatch( "key \"another\"", [&]{ stringIntFastMap.Add( "another", 10 ); }, false );
			suite.TryCatch( "key \"twenty\"", [&]{ stringIntFastMap.Add( "twenty", 20 ); }, false );
		}
		suite.EndCase();

		suite.BeginCase( "Count is correct" );
		{
			suite.Assert( "count is 5",  stringIntFastMap.Count() == 5 );
		}
		suite.EndCase();

		suite.BeginCase( "Exists" );
		{
			suite.Assert( "key \"default\"", stringIntFastMap.Exists( "default" ) );
			suite.Assert( "key \"first\"", stringIntFastMap.Exists( "first" ) );
			suite.Assert( "key \"second\"", stringIntFastMap.Exists( "second" ));
			suite.Assert( "key \"another\"", stringIntFastMap.Exists( "another" ) );
			suite.Assert( "key \"twenty\"", stringIntFastMap.Exists( "twenty" ) );
			suite.Assert( "key \"thirty\" doesn't exist", stringIntFastMap.Exists( "thirty" ) == false );
		}
		suite.EndCase();

		suite.BeginCase( "Can find by key" );
		{
			suite.TryCatchAssert( "key \"default\"", [&]{ return stringIntFastMap.Find( "default" ) == 0; } );
			suite.TryCatchAssert( "key \"first\"", [&]{ return stringIntFastMap.Find( "first" ) == 1; } );
			suite.TryCatchAssert( "key \"second\"", [&]{ return stringIntFastMap.Find( "second" ) == 2; } );
			suite.TryCatchAssert( "key \"another\"", [&]{ return stringIntFastMap.Find( "another" ) == 3; } );
			suite.TryCatchAssert( "key \"twenty\"", [&]{ return stringIntFastMap.Find( "twenty" ) == 4; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&]{ stringIntFastMap.Find( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Key names by index" );
		{
			suite.TryCatchAssert( "value 0 is \"default\"", [&] { return stringIntFastMap.GetName( 0 ) == "default"; } );
			suite.TryCatchAssert( "value 1 is  \"first\"", [&] { return stringIntFastMap.GetName( 1 ) == "first"; } );
			suite.TryCatchAssert( "value 2 is \"second\"", [&] { return stringIntFastMap.GetName( 2 ) == "second"; } );
			suite.TryCatchAssert( "value 3 is \"another\"", [&] { return stringIntFastMap.GetName( 3 ) == "another"; } );
			suite.TryCatchAssert( "value 4 is \"twenty\"", [&] { return stringIntFastMap.GetName( 4 ) == "twenty"; } );
			suite.TryCatch( "value 5 doesn't exist", [&] { stringIntFastMap.GetName( 5 ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Get value from name" );
		{
			suite.TryCatchAssert( "key \"default\" = 0", [&] { return stringIntFastMap.GetValue( "default" ) == 0; } );
			suite.TryCatchAssert( "key \"first\" = 1", [&] { return stringIntFastMap.GetValue( "first" ) == 1; } );
			suite.TryCatchAssert( "key \"second\" = 2", [&] { return stringIntFastMap.GetValue( "second" ) == 2; } );
			suite.TryCatchAssert( "key \"another\" = 10", [&] { return stringIntFastMap.GetValue( "another" ) == 10; } );
			suite.TryCatchAssert( "key \"twenty\" = 20", [&] { return stringIntFastMap.GetValue( "twenty" ) == 20; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntFastMap.GetValue( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Set value from index" );
		{
			suite.TryCatch( "key 0 to 100", [&] { stringIntFastMap.SetValue( 0, 100 ); }, false );
			suite.TryCatch( "key 1 to 101", [&] { stringIntFastMap.SetValue( 1, 101 ); }, false );
			suite.TryCatch( "key 2 to 102", [&] { stringIntFastMap.SetValue( 2, 102 ); }, false );
			suite.TryCatch( "key 3 to 110", [&] { stringIntFastMap.SetValue( 3, 110 ); }, false );
			suite.TryCatch( "key 4 to 120", [&] { stringIntFastMap.SetValue( 4, 120 ); }, false );
			suite.TryCatch( "key 5 doesn't exist", [&] { stringIntFastMap.SetValue( 5, 130 ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Get value from name is updated correctly" );
		{
			suite.TryCatchAssert( "key \"default\" = 100", [&] { return stringIntFastMap.GetValue( "default" ) == 100; } );
			suite.TryCatchAssert( "key \"first\" = 101", [&] { return stringIntFastMap.GetValue( "first" ) == 101; } );
			suite.TryCatchAssert( "key \"second\" = 102", [&] { return stringIntFastMap.GetValue( "second" ) == 102; } );
			suite.TryCatchAssert( "key \"another\" = 110", [&] { return stringIntFastMap.GetValue( "another" ) == 110; } );
			suite.TryCatchAssert( "key \"twenty\" = 120", [&] { return stringIntFastMap.GetValue( "twenty" ) == 120; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntFastMap.GetValue( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Set value from key" );
		{
			suite.TryCatch( "key \"default\" to 1000", [&] { stringIntFastMap.SetValue( 0, 1000 ); }, false );
			suite.TryCatch( "key \"first\" to 1001", [&] { stringIntFastMap.SetValue( 1, 1001 ); }, false );
			suite.TryCatch( "key \"second\" to 1002", [&] { stringIntFastMap.SetValue( 2, 1002 ); }, false );
			suite.TryCatch( "key \"another\" to 1010", [&] { stringIntFastMap.SetValue( 3, 1010 ); }, false );
			suite.TryCatch( "key \"twenty\" to 1020", [&] { stringIntFastMap.SetValue( 4, 1020 ); }, false );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntFastMap.SetValue( 5, 1030 ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Get value from name is updated correctly" );
		{
			suite.TryCatchAssert( "key \"default\" = 1000", [&] { return stringIntFastMap.GetValue( "default" ) == 1000; } );
			suite.TryCatchAssert( "key \"first\" = 1001", [&] { return stringIntFastMap.GetValue( "first" ) == 1001; } );
			suite.TryCatchAssert( "key \"second\" = 1002", [&] { return stringIntFastMap.GetValue( "second" ) == 1002; } );
			suite.TryCatchAssert( "key \"another\" = 1010", [&] { return stringIntFastMap.GetValue( "another" ) == 1010; } );
			suite.TryCatchAssert( "key \"twenty\" = 1020", [&] { return stringIntFastMap.GetValue( "twenty" ) == 1020; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntFastMap.GetValue( "thirty" ); }, true );
		}
		suite.EndCase();
	}
	suite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	while( !_getch() );

    return 0;
}