// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <memory>
#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/test/IEventHandler.h>

namespace unify
{
	namespace test
	{
		class DefaultEventHandler : public IEventHandler
		{
		public:
			virtual ~DefaultEventHandler();
			virtual void Event( std::string name, EventType type );
		};
	}
}