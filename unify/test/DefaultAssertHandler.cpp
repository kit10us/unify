// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/test/DefaultAssertHandler.h>

using namespace unify;
using namespace test;

DefaultAssertHandler::~DefaultAssertHandler()
{
}

void DefaultAssertHandler::Assert( std::string message, bool test )
{
	using namespace std;

	cout << "   Test \"" << message << "\" ";

	if ( !test )
	{
		cout << "failed!" << endl;
		assert( false );
	}
	else
	{
		cout << "passed." << endl;
	}
}
