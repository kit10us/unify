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
/// Test various Unify geometry features.
/// </summary>

#include <string>
#include <unify/Lookup.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	Lookup< std::string, int > stringIntLookup;

	suite.BeginSuite( "Lookup" );
	{
		suite.BeginCase( "Count is correct" );
		{
			suite.Assert( "count is 0", stringIntLookup.Count() == 0 );
		}
		suite.EndCase();

		suite.BeginCase( "Adding values" );
		{
			suite.TryCatch( "key not value (default), \"default\"", [&]{ stringIntLookup.Add( "default", 0 ); }, false );
			suite.TryCatch( "key \"first\"", [&]{ stringIntLookup.Add( "first", 1 ); }, false );
			suite.TryCatch( "key \"second\"", [&]{ stringIntLookup.Add( "second", 2 ); }, false );
			suite.TryCatch( "key \"another\"", [&]{ stringIntLookup.Add( "another", 10 ); }, false );
			suite.TryCatch( "key \"twenty\"", [&]{ stringIntLookup.Add( "twenty", 20 ); }, false );
		}
		suite.EndCase();

		suite.BeginCase( "Count is correct" );
		{
			suite.Assert( "count is 5",  stringIntLookup.Count() == 5 );
		}
		suite.EndCase();

		suite.BeginCase( "Exists" );
		{
			suite.Assert( "key \"default\"", stringIntLookup.Exists( "default" ) );
			suite.Assert( "key \"first\"", stringIntLookup.Exists( "first" ) );
			suite.Assert( "key \"second\"", stringIntLookup.Exists( "second" ));
			suite.Assert( "key \"another\"", stringIntLookup.Exists( "another" ) );
			suite.Assert( "key \"twenty\"", stringIntLookup.Exists( "twenty" ) );
			suite.Assert( "key \"thirty\" doesn't exist", stringIntLookup.Exists( "thirty" ) == false );
		}
		suite.EndCase();

		suite.BeginCase( "Can find by key" );
		{
			suite.TryCatchAssert( "key \"default\"", [&]{ return stringIntLookup.Find( "default" ) == 0; } );
			suite.TryCatchAssert( "key \"first\"", [&]{ return stringIntLookup.Find( "first" ) == 1; } );
			suite.TryCatchAssert( "key \"second\"", [&]{ return stringIntLookup.Find( "second" ) == 2; } );
			suite.TryCatchAssert( "key \"another\"", [&]{ return stringIntLookup.Find( "another" ) == 3; } );
			suite.TryCatchAssert( "key \"twenty\"", [&]{ return stringIntLookup.Find( "twenty" ) == 4; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&]{ stringIntLookup.Find( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Key names by index" );
		{
			suite.TryCatchAssert( "value 0 is \"default\"", [&] { return stringIntLookup.GetName( 0 ) == "default"; } );
			suite.TryCatchAssert( "value 1 is  \"first\"", [&] { return stringIntLookup.GetName( 1 ) == "first"; } );
			suite.TryCatchAssert( "value 2 is \"second\"", [&] { return stringIntLookup.GetName( 2 ) == "second"; } );
			suite.TryCatchAssert( "value 3 is \"another\"", [&] { return stringIntLookup.GetName( 3 ) == "another"; } );
			suite.TryCatchAssert( "value 4 is \"twenty\"", [&] { return stringIntLookup.GetName( 4 ) == "twenty"; } );
			suite.TryCatch( "value 5 doesn't exist", [&] { stringIntLookup.GetName( 5 ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Get value from name" );
		{
			suite.TryCatchAssert( "key \"default\" = 0", [&] { return stringIntLookup.GetValue( "default" ) == 0; } );
			suite.TryCatchAssert( "key \"first\" = 1", [&] { return stringIntLookup.GetValue( "first" ) == 1; } );
			suite.TryCatchAssert( "key \"second\" = 2", [&] { return stringIntLookup.GetValue( "second" ) == 2; } );
			suite.TryCatchAssert( "key \"another\" = 10", [&] { return stringIntLookup.GetValue( "another" ) == 10; } );
			suite.TryCatchAssert( "key \"twenty\" = 20", [&] { return stringIntLookup.GetValue( "twenty" ) == 20; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntLookup.GetValue( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Set value from index" );
		{
			suite.TryCatch( "key 0 to 100", [&] { stringIntLookup.SetValue( 0, 100 ); }, false );
			suite.TryCatch( "key 1 to 101", [&] { stringIntLookup.SetValue( 1, 101 ); }, false );
			suite.TryCatch( "key 2 to 102", [&] { stringIntLookup.SetValue( 2, 102 ); }, false );
			suite.TryCatch( "key 3 to 110", [&] { stringIntLookup.SetValue( 3, 110 ); }, false );
			suite.TryCatch( "key 4 to 120", [&] { stringIntLookup.SetValue( 4, 120 ); }, false );
			suite.TryCatch( "key 5 doesn't exist", [&] { stringIntLookup.SetValue( 5, 130 ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Get value from name is updated correctly" );
		{
			suite.TryCatchAssert( "key \"default\" = 100", [&] { return stringIntLookup.GetValue( "default" ) == 100; } );
			suite.TryCatchAssert( "key \"first\" = 101", [&] { return stringIntLookup.GetValue( "first" ) == 101; } );
			suite.TryCatchAssert( "key \"second\" = 102", [&] { return stringIntLookup.GetValue( "second" ) == 102; } );
			suite.TryCatchAssert( "key \"another\" = 110", [&] { return stringIntLookup.GetValue( "another" ) == 110; } );
			suite.TryCatchAssert( "key \"twenty\" = 120", [&] { return stringIntLookup.GetValue( "twenty" ) == 120; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntLookup.GetValue( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Set value from key" );
		{
			suite.TryCatch( "key \"default\" to 1000", [&] { stringIntLookup.SetValue( 0, 1000 ); }, false );
			suite.TryCatch( "key \"first\" to 1001", [&] { stringIntLookup.SetValue( 1, 1001 ); }, false );
			suite.TryCatch( "key \"second\" to 1002", [&] { stringIntLookup.SetValue( 2, 1002 ); }, false );
			suite.TryCatch( "key \"another\" to 1010", [&] { stringIntLookup.SetValue( 3, 1010 ); }, false );
			suite.TryCatch( "key \"twenty\" to 1020", [&] { stringIntLookup.SetValue( 4, 1020 ); }, false );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntLookup.SetValue( 5, 1030 ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Get value from name is updated correctly" );
		{
			suite.TryCatchAssert( "key \"default\" = 1000", [&] { return stringIntLookup.GetValue( "default" ) == 1000; } );
			suite.TryCatchAssert( "key \"first\" = 1001", [&] { return stringIntLookup.GetValue( "first" ) == 1001; } );
			suite.TryCatchAssert( "key \"second\" = 1002", [&] { return stringIntLookup.GetValue( "second" ) == 1002; } );
			suite.TryCatchAssert( "key \"another\" = 1010", [&] { return stringIntLookup.GetValue( "another" ) == 1010; } );
			suite.TryCatchAssert( "key \"twenty\" = 1020", [&] { return stringIntLookup.GetValue( "twenty" ) == 1020; } );
			suite.TryCatch( "key \"thirty\" doesn't exist", [&] { stringIntLookup.GetValue( "thirty" ); }, true );
		}
		suite.EndCase();

		suite.BeginCase( "Iterator" );
		{
			auto itr = stringIntLookup.begin();
			auto end = stringIntLookup.end();
			suite.Assert( "Begin is not end", itr != end );
			suite.TryCatchAssert( "First iterator \"default\" dereferenced (*) correctly", [&]{ return (*itr).key == "default" && (*itr).value == 1000; } ); 

			{
				itr->key; // Need to get past "c:\dev\unify\01tests\01test07-lookup\01test07-lookup.cpp(144): fatal error C1001: An internal error has occurred in the compiler." "(compiler file 'msc1.cpp', line 1468)"
				suite.TryCatchAssert( "First iterator \"default\" accessed (->) correctly", [&]{ return itr->key == "default" && itr->value == 1000; } );
			}

			suite.TryCatch( "Modify first iterator \"default\" value to 2000", [&]{ (*itr).value = 2000; }, false );
			suite.TryCatchAssert( "Key \"default\" = 2000", [&]{ return stringIntLookup.GetValue( 0 ) == 2000; } );
			
			suite.TryCatchAssert( "Post-increment to next value is \"first\"", [&]{ return (++itr)->key == "first"; } );
			suite.TryCatchAssert( "Post-decrement to previous value is \"default\"", [&]{ return (--itr)->key == "default"; } );
			
			suite.TryCatchAssert( "Pre-increment to next value is \"default\"", [&] { return (itr++)->key == "default"; } );
			suite.TryCatchAssert( "Pre-decrement to previous value is \"first\"", [&] { return (itr++)->key == "first"; } );

			suite.TryCatchAssert( "Iterator is \"second\"", [&] { return itr->key == "second"; } );

			suite.TryCatchAssert( "Pre-increment is \"another\"", [&] { return (++itr)->key == "another"; } );
			suite.TryCatchAssert( "Pre-iterator is \"twenty\"", [&] { return (++itr)->key == "twenty"; } );
			suite.Assert( "Last iterator is not end", itr != end );
			suite.Assert( "Increment one past last is end", (++itr) == end );
		}
		suite.EndCase();
	}
	suite.EndSuite();
	return 0;
}