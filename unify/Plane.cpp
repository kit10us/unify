/*
 * Unify Library
 * https://github.com/kit10us/unify
 *Copyright(c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library(a.k.a.Unify)
 *
 * Unify is free software : you can redistribute itand /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.If not, see < https://www.gnu.org/licenses/>.
 */


#include <unify/Plane.h>

using namespace unify;

Plane Plane::PlaneFromPoints( const unify::V3< float > & v1, const unify::V3< float > & v2, const unify::V3< float > & v3 )
{
	V3< float > v21( v1 - v2 );
	V3< float > v31( v1 - v3 );

	V3< float > n = V3< float >::V3Cross( v21, v31 );

	Plane out( n.x, n.y, n.z, n.x  * v1.x + n.y * v1.y + n.z * v1.z );
	return out;
}

Plane::Plane()
{
}

Plane::Plane( float a, float b, float c, float d )
: a( a )
, b( b )
, c( c )
, d( d )
{
}

float Plane::DotCoord( const V3< float > & v2 ) const
{
	unify::V4< float > v1( a, b, c, d );
	unify::V4< float > v2x4( v2, 1.0f );
	return v1.Dot( v2x4 );
}

float Plane::DotNormal( const V3< float > & v2 ) const
{
	unify::V4< float > v1( a, b, c, d );
	unify::V4< float > v2x4( v2, 0.0f );
	return v1.Dot( v2x4 );
}

bool Plane::IntersectLine( unify::V3< float > & out, const unify::V3< float > & v1, const unify::V3< float > & v2 ) const
{
	out; v1; v2;
	assert( 0 );
	return false;
}
