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

#include <unify/Cast.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "General" );
	{
		suite.BeginCase( "Cast to strings" );
		suite.Assert( "float conversion", Cast< float >( "   12.21  " ) == 12.21f );
		suite.Assert( "unsigned char conversion", Cast< unsigned char >( "   12  " ) == 12 );
		suite.Assert( "int conversion", Cast< int >( "   12  " ) == 12 );
		suite.Assert( "bool conversion true", Cast< bool >( "   true  " ) == true );
		suite.Assert( "bool conversion false", Cast< bool >( "   false  " ) == false );
		suite.EndCase();

		suite.BeginCase("Casts from strings");
		
		suite.Assert("unsigned char conversion", Cast<std::string, unsigned char>(121) == "121");
		suite.Assert("unsigned char conversion not", Cast<std::string, unsigned char>(212) != "121");

		suite.Assert("char conversion", Cast<std::string, int>(121) == "121");
		suite.Assert("char conversion not", Cast<std::string, int>(212) != "121");
		suite.Assert("char negative conversion", Cast<std::string, int>(-121) == "-121");
		suite.Assert("char negaitve conversion not", Cast<std::string, int>(-212) != "-121");

		suite.Assert("unsigned int conversion", Cast<std::string, unsigned int>(1221) == "1221");
		suite.Assert("unsigned int conversion not", Cast<std::string, unsigned int>(2121) != "1221");

		suite.Assert("int conversion", Cast<std::string, int>(1221) == "1221");
		suite.Assert("int conversion not", Cast<std::string, int>(2121) != "1221");
		suite.Assert("int negative conversion", Cast<std::string, int>(-1221) == "-1221");
		suite.Assert("int negaitve conversion not", Cast<std::string, int>(-2121) != "-1221");

		suite.Assert("float conversion", Cast<std::string, float>(12.21f) == "12.210000");
		suite.Assert("float conversion", Cast<std::string, float>(21.21f) != "12.210000");
		suite.Assert("float conversion", Cast<std::string, float>(-12.21f) == "-12.210000");
		suite.Assert("float conversion", Cast<std::string, float>(-21.21f) != "-12.210000");

		suite.Assert("double conversion", Cast<std::string, double>(12.21) == "12.210000");
		suite.Assert("double conversion", Cast<std::string, double>(21.21) != "12.210000");
		suite.Assert("double conversion", Cast<std::string, double>(-12.21) == "-12.210000");
		suite.Assert("double conversion", Cast<std::string, double>(-21.21) != "-12.210000");

		suite.Assert("unsigned short conversion", Cast<std::string, unsigned short>(1221) == "1221");
		suite.Assert("unsigned short conversion not", Cast<std::string, unsigned short>(2121) != "1221");

		suite.Assert("short conversion", Cast<std::string, short>(1221) == "1221");
		suite.Assert("short conversion not", Cast<std::string, short>(2121) != "1221");
		suite.Assert("short negative conversion", Cast<std::string, short>(-1221) == "-1221");
		suite.Assert("short negaitve conversion not", Cast<std::string, short>(-2121) != "-1221");

		suite.Assert("unsigned long conversion", Cast<std::string, unsigned long>(1221) == "1221");
		suite.Assert("unsigned long conversion not", Cast<std::string, unsigned long>(2121) != "1221");

		suite.Assert("short conversion", Cast<std::string, long>(1221) == "1221");
		suite.Assert("short conversion not", Cast<std::string, long>(2121) != "1221");
		suite.Assert("short negative conversion", Cast<std::string, long>(-1221) == "-1221");
		suite.Assert("short negaitve conversion not", Cast<std::string, long>(-2121) != "-1221");

		suite.EndCase();
	}
	suite.EndSuite();
    return 0;
}