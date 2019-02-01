// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/test/IEventHandler.h>
#include <unify/test/IOutputHandler.h>
#include <memory>

namespace unify
{
	namespace test
	{
		class DefaultEventHandler : public IEventHandler
		{
		public:
			virtual ~DefaultEventHandler();
			virtual void Event( IOutputHandler::ptr output, std::string name, OutputType type );
		};
	}
}