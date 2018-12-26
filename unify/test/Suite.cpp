// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <iostream>
#include <unify/Matrix.h>
#include <unify/test/Suite.h>
#include <unify/test/DefaultEventHandlers.h>
#include <unify/test/DefaultOutputHandlers.h>
#include <unify/test/DefaultAssertHandler.h>

using namespace unify;
using namespace test;

Suite::Suite()
{
	m_eventHandler = IEventHandler::ptr{ new DefaultEventHandler };
	m_outputHandler = IOutputHandler::ptr{ new DefaultOutputHandler };
	m_assertHandler = IAssertHandler::ptr{ new DefaultAssertHandler };
}

Suite::~Suite()
{
}

void Suite::BeginSuite( std::string name )
{
	m_suiteName = name;
	if( m_eventHandler )
	{
		m_eventHandler->Event( m_outputHandler, m_suiteName, OutputType::BeginSuite );
	}
}

void Suite::EndSuite()
{
	if (m_eventHandler)
	{
		m_eventHandler->Event( m_outputHandler, m_suiteName, OutputType::EndSuite );
	}
	m_suiteName = "";
}

void Suite::BeginCase( std::string name )
{
	m_caseName = name;
	if ( m_outputHandler )
	{
		m_outputHandler->Output( m_caseName, OutputType::BeginCase );
	}
}

void Suite::EndCase()
{
	if ( m_outputHandler )
	{
		m_outputHandler->Output( m_caseName, OutputType::EndCase );
	}
	m_caseName = "";
}

void Suite::Info( std::string message )
{
	if ( m_outputHandler )
	{
		m_outputHandler->Output( message, OutputType::Info );
	}
}

void Suite::Warning( std::string message )
{
	if ( m_outputHandler )
	{
		m_outputHandler->Output( message, OutputType::Warning );
	}
}

void Suite::Assert( std::string message, bool test )
{
	if ( !test )
	{
		m_assertCount++;
	}
	
	if ( m_assertHandler )
	{
		m_assertHandler->Assert( m_outputHandler, message, test );
	}
}

void Suite::TryCatch( std::string message, std::function< void() > test, bool passOnException )
{
	bool result = passOnException ? false : true;
	try
	{
		test();
	}
	catch( ... )
	{
		result = passOnException ? true : false;
	}
	Assert( message, result );
}

void Suite::TryCatchAssert( std::string message, std::function< bool() > test )
{
	bool result{ true };
	try
	{
		result = test();
	}
	catch (...)
	{
		result = false;
	}
	Assert( message, result );
}
