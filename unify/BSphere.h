/* Copyright (c) 2002 - 2019, Evil Quail LLC
 * All Rights Reserved
 */

#pragma once

#include <unify/Unify.h>
#include <unify/V2.h>
#include <unify/V3.h>
#include <unify/V4.h>

namespace unify
{
	// An accumilated radius (from center).
	template< typename T = float >
	class BSphere
	{
	public:
		BSphere();
		BSphere( V3< T > center );
		BSphere( V3< T > center, T radius );

		V3< T > center;
		T radius;

		V3< T > GetCenter() const;
		T GetRadius() const;

		BSphere & operator+=( const BSphere< T > & sphere );
		BSphere & operator+=( V3< T > point );

		bool Contains( V3< T > point ) const;
		bool Collides( BSphere< T > sphere ) const;
	};

	#include <unify/BSphere.inl>
}


