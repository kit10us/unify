/* Copyright (c) 2002 - 2019, Kit10 Studios LLC
 * All Rights Reserved
 */
#pragma once

#include <unify/Exception.h>

namespace unify
{
	/// <summary>
	/// A standardized exception.
	/// </summary>
	class BadCast : public Exception
    {
    public:
        BadCast( std::string what )
			: Exception( what.c_str() )
        {
        }
    };
}