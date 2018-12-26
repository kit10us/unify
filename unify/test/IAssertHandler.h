// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/test/IOutputHandler.h>
#include <memory>
#include <unify/Unify.h>
#include <unify/String.h>

namespace unify
{
	namespace test
	{
		/// <summary>
		/// Interface for handling an assertion.
		/// </summary>
		class IAssertHandler
		{
		public:
			typedef std::shared_ptr< IAssertHandler > ptr;

			virtual ~IAssertHandler() {}

			/// <summary>
			/// Called when we perform an assertion.
			/// </summary>
			/// <param name="message">Message for output.</param>
			/// <param name="test">There result of the assert test.</param>
			virtual void Assert( IOutputHandler::ptr output, std::string message,  bool test ) = 0;
		};
	}
}