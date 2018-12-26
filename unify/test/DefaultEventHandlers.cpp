// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/test/DefaultEventHandlers.h>

using namespace unify;
using namespace test;

DefaultEventHandler::~DefaultEventHandler()
{
}

void DefaultEventHandler::Event( IOutputHandler::ptr output, std::string name, OutputType type )
{
	output->Output( name, type ); 
	using namespace std;
}
