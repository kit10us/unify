// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/V3.h>

namespace unify
{
	class Ray
	{
	public:
		static Ray RayFromLineSegment( const V3< float > & startPoint, const V3< float > & endPoint );
		static Ray RayFromOrginAndDirection( const V3< float > & origin, const V3< float > & direction );

		V3< float > origin;
		V3< float > direction;

		V3< float > InvDirection() const;
		V3< int > Sign() const;

        Ray();
		Ray( const V3< float > & originIn, const V3< float > & directionIn );
	};
}