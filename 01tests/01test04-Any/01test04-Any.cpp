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

#include <string>
#include <unify/Any.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "Any" );
	{
		suite.BeginCase("Any not empty (int)");
		Any anyInt12 = 12;
		suite.Assert("Any not empty", !anyInt12.empty());
		suite.EndCase();

		suite.BeginCase("Int match");
		suite.Assert("Int match", any_cast<int>(anyInt12) == 12);
		suite.EndCase();

		suite.BeginCase("Strings");
		Any anyString = "Hello, world!";
		suite.Assert("Any string stored correctly.", any_cast<const char*>(anyString) != nullptr);
		suite.Assert("Any string equivalency.", std::string(any_cast<const char*>(anyString)) == "Hello, world!");
		suite.EndCase();

	}
	suite.EndSuite();
	return 0;
}