// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>

namespace unify
{
	/// <summary>
	///	An Angle abstract so we can move between degrees and radians easily, and simplify math by pushing the actual conversion format
	/// to the beginning and end of the lifetime of the math - that is to say, we don't care if A + B is degrees or radians, we only 
	/// care that the result is in degrees or radians.
	/// </summary>
	class Angle
    {
		friend Angle AngleInRadians( float radians );
		friend Angle AngleInDegrees( float degrees );
		friend Angle AnglePI();
		friend Angle AnglePI2();
		friend Angle AnglePIHalf();
		
		float m_radians;
        Angle( float radians );

    public:

		Angle();
		Angle( const Angle & angle );
		Angle( std::string angle );

		// binary operators
		Angle & operator = ( const Angle & angle );

		Angle & operator += ( const Angle & angle );
		Angle & operator -= ( const Angle & angle );
		Angle & operator *= ( const Angle & angle );
		Angle & operator /= ( const Angle & angle );

		Angle operator + ( const Angle & angle) const;
		Angle operator - ( const Angle & angle ) const;
		Angle operator * ( const Angle & angle ) const;
		Angle operator / ( const Angle & angle ) const;

        bool operator == ( const Angle & angle ) const;
		bool operator != ( const Angle & angle ) const;

        Angle & operator *= ( float scalar );
		Angle & operator /= ( float scalar );

		Angle operator * ( float scalar ) const;
		Angle operator / ( float scalar ) const;

		bool operator > ( const Angle & angle );
		bool operator >= ( const Angle & angle );
		bool operator < ( const Angle & angle );
		bool operator <= ( const Angle & angle );

		float ToRadians() const;
        float ToDegrees() const;

		///<summary>
		/// Ensures our value is within 360 degrees, without loss of precision (if we are 367, then we become 7, etc.).
		/// Returns the change in magnitude relative to 360 (367 returns 1, -728 returns -2, etc.).
        ///</summary>
        int Fix360();

		/// <summary>
		/// Returns the sine of this angle.
		/// </summary>
		float SinOf() const;

		/// <summary>
		/// Returns the cosine of this angle.
		/// </summary>
		float CosOf() const;

		std::string ToString( bool radians = true ) const;
    };

	Angle AngleInRadians( float radians );
	Angle AngleInDegrees( float degrees );
	Angle AnglePI();
	Angle AnglePI2();
	Angle AnglePIHalf();
}