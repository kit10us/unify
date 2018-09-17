// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <iostream>
#include <unify/Matrix.h>
#include <unify/TestSuite.h>

using namespace unify;

TestSuite::TestSuite( std::string description, std::string incrementPrefix )
	: m_suiteDescription{ description }
	, m_incrementPrefix{ incrementPrefix }
{
	using namespace std;

}

TestSuite::~TestSuite()
{
}

void TestSuite::BeginSuite()
{
	using namespace std;

	cout << "Begin test suite \"" << m_suiteDescription << "\"" << endl;
}

void TestSuite::EndSuite()
{
	using namespace std;

	cout << "Test suite \"" << m_suiteDescription << "\" test suite done." << endl;
}

void TestSuite::BeginCase( std::string description )
{
	using namespace std;

	m_testCaseDescription = description;
	cout << m_incrementPrefix << "Begin test case \"" << description << "\"" << endl;
}

void TestSuite::EndCase()
{
	using namespace std;

	cout << m_incrementPrefix << "End test case \"" << m_testCaseDescription << "\"" << endl;
}

void TestSuite::IncrementFailures( AssertType type )
{
	switch( type )
	{
	case AssertType::Continue:
		m_continueFailures++;;
		break;
	case AssertType::Stop:
		m_stopFailures++;
		break;
	}
}

/// <description>
/// Perform an assert, however, do not stop exection, for example, if test
/// </description>
void TestSuite::Assert( std::string description, bool test, AssertType type )
{
	using namespace std;

	cout << m_incrementPrefix << m_incrementPrefix << "Assert " << description << "... ";
	if (!test)
	{
		cout << "Test failed!" << endl;
		switch( type )
		{
		case AssertType::Continue:
			break;
		case AssertType::Stop:
			assert( false );
			break;
		}
	}
	else
	{
		cout << "Test passed." << endl;
	}
}
