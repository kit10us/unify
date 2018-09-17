// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Matrix.h>

namespace unify
{
	/// <description>
	/// Assert types, which specify what to do when an assert fails.
	/// </description>
	enum class AssertType 
	{
		Stop,
		Continue
	};

	/// <description>
	/// Used to test various features in a uniformed matter
	/// </description>
	class TestSuite
	{
	public:
		TestSuite( std::string description, std::string incrementPrefix );
		virtual ~TestSuite();

		void BeginSuite();
		void EndSuite();

		void IncrementFailures( AssertType type );
		void BeginCase( std::string description );
		void EndCase();
		void Assert( std::string description, bool test, AssertType type = AssertType::Stop );
	private:
		std::string m_suiteDescription;
		std::string m_incrementPrefix;
		std::string m_testCaseDescription;
		int m_continueFailures;
		int m_stopFailures;
	};
}
