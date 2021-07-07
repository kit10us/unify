/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


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

