// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>

namespace unify
{
	template< typename T >
	class Triangle
	{
	public:
		T v[ 3 ];

		Triangle( const T & v1, const T & v2, const T & v3 );
		Triangle & operator = ( const Triangle & triangle );

        // Operators for single value applied to all.
        Triangle & operator+=( T value );
        Triangle operator+( T value );
	};
	#include <unify/Triangle.inl>
}

