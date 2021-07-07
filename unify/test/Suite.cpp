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
