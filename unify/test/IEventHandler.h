// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <memory>
#include <unify/Unify.h>
#include <string>

namespace unify
{
	namespace test
	{
		/// <summary>
		/// The type of output. Allows the same interface for each output type.
		/// </summary>
		enum class EventType
		{
			SuiteBegin,
			SuiteEnd,
			CaseBegin,
			CaseEnd,
			COUNT
		};

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
			virtual void Event( std::string name, EventType type ) = 0;
		};
	}
}