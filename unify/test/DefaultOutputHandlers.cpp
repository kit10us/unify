// Copyright (c) 2002 - 2019, Evil Quail LLC
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
		case OutputType::Info:
			cout << "      Test info: " << message << "." << endl;
			break;
		case OutputType::Warning:
			cout << "      Test warning: " << message << "." << endl;
			break;
	}
}
