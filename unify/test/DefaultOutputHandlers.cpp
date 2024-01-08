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


#include <unify/test/DefaultOutputHandlers.h>

#ifdef _WIN32
#include <Windows.h>
#include <debugapi.h>
#endif // _WIN32

using namespace unify;
using namespace test;

DefaultOutputHandler::~DefaultOutputHandler()
{
}

void DefaultOutputHandler::Output( std::string message, OutputType type )
{
	using namespace std;

	auto out = [](std::string output)
		{
			cout << output << endl;
	#ifdef _WIN32
			OutputDebugStringA((output + "\n").c_str() );
	#endif // _WIN32

		};

	switch( type )
	{
	case OutputType::BeginSuite:
		out("Begin test suite \"" + message + "\"");
		break;

	case OutputType::EndSuite:
		out( "End Test suite \"" + message + "\"" );
		break;

	case OutputType::BeginCase:
		out( "   Begin case \"" + message + "\"" );
		break;

	case OutputType::EndCase:
		out( "   End case \"" + message + "\"" );
		break;

	case OutputType::Info:
		out( "         Info \"" + message + "\"" );
		break;

	case OutputType::Warning:
		out( "         Warning \"" + message + "\"" );
		break;

	case OutputType::AssertPassed:
		out( "      Assert \"" + message + "\" passed" );
		break;

	case OutputType::AssertFailed:
		out( "      Assert \"" + message + "\" failed!" );
		break;
	}
}
