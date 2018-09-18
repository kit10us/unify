// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <memory>
#include <unify/Unify.h>
#include <unify/String.h>

namespace unify
{
	namespace test
	{
		/// <description>
		/// The type of output. Allows the same interface for each output type.
		/// </description>
		enum class OutputType
		{
			Info,
			Warning,
			COUNT
		};

		/// <description>
		/// Interface for handling an assertion.
		/// </description>
		class IOutputHandler
		{
		public:
			typedef std::shared_ptr< IOutputHandler > ptr;

			virtual ~IOutputHandler() {}

			/// <summary>
			/// Called when we trigger output.
			/// </summary>
			/// <param name="message">Message for output.</param>
			/// <param name="test">There result of the assert test.</param>
			virtual void Output( std::string message, OutputType type ) = 0;
		};
	}
}