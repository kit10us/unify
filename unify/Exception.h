/* Copyright (c) 2002 - 2019, Evil Quail LLC
 * All Rights Reserved
 */
#pragma once

#include <unify/Unify.h>
#include <exception>
#include <string>

namespace unify
{
    class Exception : public std::exception
    {
    public:
        Exception( std::string what )
			: std::exception( what.c_str() )
        {
        }
    };
}