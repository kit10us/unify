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


namespace unify
{
	template< typename T >
	inline
	Ray<T>::Ray()
	: origin{}
	, direction{0.0f, 0.0f, 1.0f}
	{
	}

	template< typename T >
	inline
	Ray<T>::Ray( const V3< T > originIn, const V3< T > directionIn )
		: origin( originIn )
		, direction( directionIn )
	{
	}

	template< typename T >
	inline
	V3< T > Ray<T>::Inverse() const
	{
		return V3< T >::V3Inverse( direction );
	}

	template< typename T >
	inline
	V3< int > Ray<T>::Sign() const
	{
		V3< T > invDirection = InvDirection();
		return V3< int >( invDirection.x < 0, invDirection.y < 0, invDirection.z < 0 );
	}

	template< typename T >
	inline
	Ray<T> RayFromOriginAndDirection( const V3<T> origin, const V3<T> direction )
	{
		return { origin, direction };
	}

	template< typename T >
	inline
	Ray<T> RayFromLineSegment( const V3<T> startPoint, const V3<T> endPoint )
	{
		return { startPoint, endPoint - startPoint };

	}
}