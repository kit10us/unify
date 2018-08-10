// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

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
