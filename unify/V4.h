// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Exception.h>

namespace unify
{
	template< typename T > class V3;

	template< typename T >
	class V4
	{
	public:
		T x, y, z, w;

		V4();
		V4( T all );
		V4( T x, T y, T z, T w );
		V4( const V4< T > & v4 );
		V4( const T arr[ 4 ] );
		V4( const V3< T > & v3, float w = 1.0f );
        explicit V4( std::string text );

		void Zero();
		T Length() const;
		bool IsZero() const;
		void Normalize();
		V4< T > Absolute() const;
		T Dot( const V4< T > & v2 ) const;
		//void Transform( const TMatrix * pMat );

		// OPERATOR OVERLOADING MEMBER FUNCTIONS

		V4< T > & operator += ( const V4< T > & vec );
		V4< T > & operator -= ( const V4< T > & vec );
		V4< T > & operator *= ( const V4< T > & vec );
		V4< T > & operator /= ( const V4< T > & vec );
		V4< T > & operator *= ( T val );
		V4< T > & operator /= ( T val );

		// unary operators
		//V4< T > operator + () const;
		//V4< T > operator - () const;

		// binary operators
		V4< T > operator + ( const V4< T > & vec) const;
		V4< T > operator - ( const V4< T > & vec ) const;
		V4< T > operator * ( const V4< T > & vec ) const;
		V4< T > operator / ( const V4< T > & vec ) const;
		V4< T > operator * ( T val ) const;
		V4< T > operator / ( T val ) const;

		//friend V4< T > operator * ( T, const struct V4< T > & );

		bool operator == ( const V4< T > & vec ) const;
		bool operator != ( const V4< T > & vec ) const;

        T & operator[]( size_t i );
        const T & operator[]( size_t i ) const;

		void Select( const V4< T > & v1, const V4< T > & v2, const V4< float > & control );

        std::string ToString() const;
	};
	#include <unify/V4.inl>
}

