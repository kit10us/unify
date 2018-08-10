// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/Ray.h>

using namespace unify;

Ray Ray::RayFromLineSegment( const V3< float > & startPoint, const V3< float > & endPoint )
{
	return { startPoint, endPoint - startPoint };

}

Ray Ray::RayFromOrginAndDirection( const V3< float > & origin, const V3< float > & direction )
{
	return { origin, direction };
}

Ray::Ray()
{
    // POD - no initialization.
}

Ray::Ray( const V3< float > & originIn, const V3< float > & directionIn )
	: origin( originIn )
	, direction( directionIn )
{
}

V3< float > Ray::InvDirection() const
{
	return V3< float >::V3Inverse( direction );
}

V3< int > Ray::Sign() const
{
	V3< float > invDirection = InvDirection();
	return V3< int >( invDirection.x < 0, invDirection.y < 0, invDirection.z < 0 );
}

