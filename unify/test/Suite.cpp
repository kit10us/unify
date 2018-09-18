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
	m_eventHandler[EventType::SuiteBegin] = IEventHandler::ptr{ new DefaultEventHandler };
	m_eventHandler[EventType::SuiteEnd] = IEventHandler::ptr{ new DefaultEventHandler };
	m_eventHandler[EventType::CaseBegin] = IEventHandler::ptr{ new DefaultEventHandler };
	m_eventHandler[EventType::CaseEnd] = IEventHandler::ptr{ new DefaultEventHandler };

	m_outputHandler[OutputType::Info] = IOutputHandler::ptr{ new DefaultOutputHandler };
	m_outputHandler[OutputType::Warning] = IOutputHandler::ptr{ new DefaultOutputHandler };

	m_assertHandler = IAssertHandler::ptr{ new DefaultAssertHandler };
}

Suite::~Suite()
{
}

void Suite::BeginSuite( std::string name )
{
	using namespace std;

	m_suiteName = name;

	auto handler = m_eventHandler.find( EventType::SuiteBegin );
	if( handler != m_eventHandler.end() )
	{
		handler->second->Event( m_suiteName, EventType::SuiteBegin );
	}
}

void Suite::EndSuite()
{
	using namespace std;
	m_suiteName = "";
}

void Suite::BeginCase( std::string name )
{
	using namespace std;
	m_caseName = name;
}

void Suite::EndCase()
{
	using namespace std;
	m_caseName = "";
}

void Suite::Info( std::string message )
{
	auto handler = m_outputHandler.find( OutputType::Info );
	if (handler != m_outputHandler.end())
	{
		handler->second->Output( message, OutputType::Info );
	}
}

void Suite::Warning( std::string message )
{
	auto handler = m_outputHandler.find( OutputType::Warning );
	if (handler != m_outputHandler.end())
	{
		handler->second->Output( message, OutputType::Warning );
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
		m_assertHandler->Assert( message, test );
	}
}
