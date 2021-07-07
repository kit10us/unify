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

using namespace unify;
using namespace test;

DefaultOutputHandler::~DefaultOutputHandler()
{
}

void DefaultOutputHandler::Output( std::string message, OutputType type )
{
	using namespace std;

	switch( type )
	{
	case OutputType::BeginSuite:
		cout << "Begin test suite \"" << message << "\"" << endl;
		break;

	case OutputType::EndSuite:
		cout << "End Test suite \"" << message << "\"" << endl;
		break;

	case OutputType::BeginCase:
		cout << "   Begin case \"" << message << "\"" << endl;
		break;

	case OutputType::EndCase:
		cout << "   End case \"" << message << "\"" << endl;
		break;

	case OutputType::Info:
		cout << "         Info \"" << message << "\"" << endl;
		break;

	case OutputType::Warning:
		cout << "         Warning \"" << message << "\"" << endl;
		break;

	case OutputType::AssertPassed:
		cout << "      Assert \"" << message << "\" passed" << endl;
		break;

	case OutputType::AssertFailed:
		cout << "      Assert \"" << message << "\" failed!" << endl;
		break;
	}
}
