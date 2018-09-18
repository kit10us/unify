// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Matrix.h>
#include <unify/test/IEventHandler.h>
#include <unify/test/IOutputHandler.h>
#include <unify/test/IAssertHandler.h>
#include <map>
#include <string>

namespace unify
{
	namespace test
	{
		/// <description>
		/// Used to test various features in a uniformed matter.
		/// </description>
		class Suite
		{
		public:
			Suite();
			virtual ~Suite();

			/// <description>
			/// Triggered when a suite begins.
			/// </description>
			void BeginSuite( std::string name );

			/// <description>
			/// Triggered when a suite ends.
			/// </description>
			void EndSuite();

			/// <description>
			/// Triggered when a test begins.
			/// </description>
			void BeginCase( std::string name );

			/// <description>
			/// Triggered when a test ends.
			/// </description>
			void EndCase();

			/// <description>
			/// Call to report information.
			/// </desciption>
			void Info( std::string message );

			/// <description>
			/// Called to report a warning.
			/// </desciption>
			void Warning( std::string message );

			/// <description>
			/// Called on an assertion.
			/// </desciption>
			void Assert( std::string message, bool test );

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
