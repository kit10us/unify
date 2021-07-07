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
			/// </summary>
			void Info( std::string message );

			/// <summary>
			/// Called to report a warning.
			/// </summary>
			void Warning( std::string message );

			/// <summary>
			/// Perform a suite assertion.
			/// </summary>
			void Assert( std::string message, bool test );

			/// <summary>
			/// Try to perform a functor, Assert on an exception.
			/// </summary>
			void TryCatch( std::string message, std::function< void() > test, bool passOnException );

			/// <summary>
			/// Assert on test returning false, or an exception.
			/// </summary>
			void TryCatchAssert( std::string message, std::function< bool() > test );

		private:
			std::string m_suiteName;
			std::string m_caseName;
			IEventHandler::ptr m_eventHandler;
			IOutputHandler::ptr m_outputHandler;
			unsigned int m_assertCount;
			IAssertHandler::ptr m_assertHandler;
		};
	}
}
