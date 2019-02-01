// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/test/IOutputHandler.h>
#include <memory>
#include <unify/Unify.h>
#include <string>

namespace unify
{
	namespace test
	{
		/// <summary>
		/// Interface for handling a test event.
		/// </summary>
		class IEventHandler
		{
		public:
			typedef std::shared_ptr< IEventHandler > ptr;

			virtual ~IEventHandler() {}

			/// <summary>
			/// Called when a test event happens.
			/// </summary>
			/// <param name="type">Type of event.</param>
			virtual void Event( IOutputHandler::ptr output, std::string name, OutputType type ) = 0;
		};
	}
}