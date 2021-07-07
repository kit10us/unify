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


#pragma once

#include <unify/Unify.h>
#include <unify/V3.h>
#include <unify/V4.h>
#include <unify/Angle.h>

namespace unify
{
	class Quaternion
	{
		friend Quaternion QuaternionIdentity();
		friend Quaternion QuaternionFromEuler( const unify::V3< float > & euler );
		friend Quaternion QuaternionSlerp( const Quaternion & quaternionA, const Quaternion & quaternionB, float mix );
		friend Quaternion QuaternionLookAt( unify::V3< float > eye, unify::V3< float > at, unify::V3< float > up );
	public:
		float x;
		float y;
		float z;
		float w;

		Quaternion();
		Quaternion( V3< float > axis, Angle angle );
		Quaternion( float x, float y, float z, float w );
		Quaternion( const Quaternion & quaternion );
		Quaternion( class Matrix m );

		bool IsIdentity() const;

		Quaternion Conjugate() const;
		Quaternion Normalize() const;

		V3< float > Up() const;

		// assignment operators
		Quaternion & operator += ( const Quaternion & quaternion );
		Quaternion & operator -= ( const Quaternion & quaternion );
		Quaternion & operator *= ( const Quaternion & quaternion );
		Quaternion & operator *= ( float value );

		// binary operators
		Quaternion operator + ( const Quaternion & quaternion ) const;
		Quaternion operator - ( const Quaternion & quaternion ) const;
		Quaternion operator * ( const Quaternion & quaternion ) const;
		Quaternion operator * ( float value ) const;

		bool operator == ( const Quaternion & quaternion ) const;
		bool operator != ( const Quaternion & quaternion ) const;

		V3< float > operator *= ( V3< float > v ) const;

		std::string ToString() const;
	};

	V3< float > operator * ( V3 < float > v, Quaternion q );

	V3< float > operator * ( Quaternion q, V3 < float > v );

	Quaternion QuaternionIdentity();
	Quaternion QuaternionFromEuler( const unify::V3< float > & euler );
	Quaternion QuaternionSlerp( const Quaternion & quaternionA, const Quaternion & quaternionB, float mix );
	Quaternion QuaternionLookAt( unify::V3< float > eye, unify::V3< float > at, unify::V3< float > up );
}
