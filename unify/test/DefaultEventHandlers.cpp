// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/test/DefaultEventHandlers.h>

using namespace unify;
using namespace test;

DefaultEventHandler::~DefaultEventHandler()
{
}

void DefaultEventHandler::Event( std::string name, EventType type )
{
	using namespace std;

	switch( type )
	{
		case  EventType::SuiteBegin:
			cout << "Begin test suite \"" << name << "\"" << endl;
			break;

		case EventType::SuiteEnd:
			cout << "Test suite \"" << name << "\" test suite done." << endl;
			break;
		case EventType::CaseBegin:
			cout << "   Begin test case \"" << name << "\"" << endl;
			break;
		case EventType::CaseEnd:
			cout << "   End test case \"" << name << "\"" << endl;
			break;
	}
}
