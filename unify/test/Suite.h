// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Matrix.h>
#include <unify/test/IEventHandler.h>
#include <unify/test/IOutputHandler.h>
#include <unify/test/IAssertHandler.h>
#include <map>
#include <string>
#include <functional>

namespace unify
{
	namespace test
	{
		/// <summary>
		/// Used to test various features in a uniformed matter.
		/// </summary>
		class Suite
		{
		public:
			Suite();
			virtual ~Suite();

			/// <summary>
			/// Triggered when a suite begins.
			/// </summary>
			void BeginSuite( std::string name );

			/// <summary>
			/// Triggered when a suite ends.
			/// </summary>
			void EndSuite();

			/// <summary>
			/// Triggered when a test begins.
			/// </summary>
			void BeginCase( std::string name );

			/// <summary>
			/// Triggered when a test ends.
			/// </summary>
			void EndCase();

			/// <summary>
			/// Call to report information.
			/// </desciption>
			void Info( std::string message );

			/// <summary>
			/// Called to report a warning.
			/// </desciption>
			void Warning( std::string message );

			/// <summary>
			/// Perform a suite assertion.
			/// </desciption>
			void Assert( std::string message, bool test );

			/// <summary>
			/// Assert on an exception.
			/// </desciption>
			void TryCatch( std::string message, std::function< void() > test, bool assertOnException );

			/// <summary>
			/// Assert on test returning false, or an exception.
			/// </desciption>
			void TryCatchAssert( std::string message, std::function< bool() > test );

		private:
			std::string m_suiteName;
			std::string m_caseName;
			std::map< EventType, IEventHandler::ptr > m_eventHandler;
			std::map< OutputType, IOutputHandler::ptr > m_outputHandler;
			unsigned int m_assertCount;
			IAssertHandler::ptr m_assertHandler;
		};
	}
}
