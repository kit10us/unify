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
#include <unify/String.h>
#include <unify/Angle.h>
#include <unify/Exception.h>
#include <cmath>

namespace unify
{
	template < class T > class V2;

	template< typename T = float >
	class V3
	{
	public:
		T x, y, z;

		V3();
		V3( T xyz );
		V3( T x, T y, T z );
    	V3( const V3< T > & vec );
		V3( const T arr[ 3 ] );
		V3( const V2< T > & v2, float z = 0.0f );
        explicit V3( std::string text );

		// OPERATOR OVERLOADING MEMBER FUNCTIONS

		V3< T > & operator += ( const V3< T > & vec );
		V3< T > & operator -= ( const V3< T > & vec );
		V3< T > & operator *= ( const V3< T > & vec );
		V3< T > & operator /= ( const V3< T > & vec );
		V3< T > & operator *= ( T val );
		V3< T > & operator /= ( T val );

		// binary operators
		V3< T > operator + ( const V3< T > & vec) const;
		V3< T > operator - ( const V3< T > & vec ) const;
		V3< T > operator * ( const V3< T > & vec ) const;
		V3< T > operator / ( const V3< T > & vec ) const;
		V3< T > operator * ( T val ) const;
		V3< T > operator / ( T val ) const;
		const V3< T > & operator = ( const V3< T > & vec );

		bool operator == ( const V3< T > & vec ) const;
		bool operator != ( const V3< T > & vec ) const;
		bool operator < ( const V3< T > & vec ) const;
		bool operator <= ( const V3< T > & vec ) const;
		bool operator > ( const V3< T > & vec ) const;
		bool operator >= ( const V3< T > & vec ) const;

        T & operator[]( size_t i );
        const T & operator[]( size_t i ) const;

        std::string ToString() const;

        T Length() const;
		T Normalize();
		T Normalize( const V3< T > & norm );
		V3< T > Absolute() const;
		const T DistanceTo( const V3<T> & to ) const;
		T Dot( const V3< T > & a ) const;
		Angle DotAngle( const V3< T > & a ) const;
		bool IsZero() const;

		// Swizzles...
		V3< T > xyz() const;
		V3< T > xzy() const;
		V3< T > yzx() const;
		V3< T > yxz() const;
		V3< T > zyx() const;
		V3< T > zxy() const;

		// Named constructors...
		static V3< T > V3Zero();
        static V3< T > V3Lerp( V3< T > first, V3< T > second, float ratio );
        static V3< T > V3Cross( const V3< T > & a, const V3< T > & b );
        static V3< T > V3X( T x );
        static V3< T > V3Y( T y );
        static V3< T > V3Z( T z );
		static V3< T > V3Normalized( const V3< T > & in );
		static V3< T > V3Inverse( const V3< T > & v3 );
		static V3< T > V3RotateAbout( V3< T > position, float distance, unify::Angle rotation, V3< T > pivot );
	};
	#include <unify/V3.inl>
}
