// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Angle.h>

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

        operator V3< T >()
        {
            return V3< T >( static_cast< T >( x ), static_cast< T >( y ), static_cast< T >( z ) );
        }

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
