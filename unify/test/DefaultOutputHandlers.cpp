// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

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
