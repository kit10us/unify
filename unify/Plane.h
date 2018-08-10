// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/V3.h>
#include <unify/V4.h>

namespace unify
{
	class Plane
	{
	public:
		static Plane PlaneFromPoints( const unify::V3< float > & v1, const unify::V3< float > & v2, const unify::V3< float > & v3 );

		Plane();
		Plane( float a, float b, float c, float d );

		float DotCoord( const V3< float > & v2 ) const;
		float DotNormal( const V3< float > & v2 ) const;

		bool IntersectLine( unify::V3< float > & out, const unify::V3< float > & v1, const unify::V3< float > & v2 ) const;

		float a, b, c, d;
	};
}
