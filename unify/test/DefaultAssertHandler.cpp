// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/test/DefaultAssertHandler.h>

using namespace unify;
using namespace test;

DefaultAssertHandler::~DefaultAssertHandler()
{
}

void DefaultAssertHandler::Assert( IOutputHandler::ptr output, std::string message, bool test )
{
	using namespace std;

	if ( !test )
	{
		output->Output( message, OutputType::AssertFailed );
		assert( false );
	}
	else
	{
		output->Output( message, OutputType::AssertPassed );
	}
}
