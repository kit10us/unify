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
/// Test various Unify features that are too small a scope to deserve a seperate test suite.
/// Test may be promoted to seperate suites as desired.
/// </summary>

#include <unify/Color.h>
#include <unify/ColorUnit.h>
#include <unify/V2.h>
#include <unify/Parameters.h>
#include <unify/Optional.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "General" );
	{
		suite.BeginCase( "Color" );
		suite.Assert( "Color from text", Color( "255, 127, 63, 31" ) == ColorRGBA( 255, 127, 63, 31 ) );
		suite.EndCase();

		suite.BeginCase( "ColorUnit" );
		suite.Assert( "ColorUnit from text", ColorUnit( "1, 0.5, 0.25, 0.125" ) == ColorUnitRGBA( 1, 0.5, 0.25, 0.125 ) ); 
		suite.EndCase();

		suite.BeginCase( "Parameter" );
		Parameters parameters;
		parameters.Set( "first", 1234567 );
		parameters.Set( "second", "second" );
		parameters.Set( "third", 3.33f );
		suite.Assert( "verify value of first parameter, int", parameters.Get< int >( "first" ) == (int)1234567 );
		suite.Assert( "verify parameter \"second\" exists", parameters.Exists( "second" ) );
		suite.EndCase();

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
	suite.EndSuite();
    return 0;
}