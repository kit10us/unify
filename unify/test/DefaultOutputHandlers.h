// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <memory>
#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/test/IOutputHandler.h>

namespace unify
{
	namespace test
	{
		class DefaultOutputHandler : public IOutputHandler
		{
		public:
			virtual ~DefaultOutputHandler();

			/// <description>
			/// Called for output of message.
			/// </description>
			/// <param name="message">
			/// Message for the assert.
			/// </param>
			/// <param name="type">
			/// Type of the assert.
			/// </param>
			virtual void Output( std::string message, OutputType type );
		};
	}
}