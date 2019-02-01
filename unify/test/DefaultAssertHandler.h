// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <memory>
#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/test/IAssertHandler.h>

namespace unify
{
	namespace test
	{
		class DefaultAssertHandler : public IAssertHandler
		{
		public:
			virtual ~DefaultAssertHandler();
			virtual void Assert( IOutputHandler::ptr output, std::string message, bool test );
		};
	}
}