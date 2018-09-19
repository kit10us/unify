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
		/// <definition>
		/// Construct an angle from radians.
		/// </definition>
		friend Angle AngleInRadians( float radians );

		/// <definition>
		/// Construct an angle from degrees.
		/// </definition>
		friend Angle AngleInDegrees( float degrees );

		/// <definition>
		/// Construct an angle with the value of pi.
		/// </definition>
		friend Angle AnglePI();

		/// <definition>
		/// Construct an angle with the value of pi * 2.
		/// </definition>
		friend Angle AnglePI2();

		/// <definition>
		/// Construct an angle with the value of half pi.
		/// </definition>
		friend Angle AnglePIHalf();
		
		float m_radians; // We store in radians, and convert what ever time delta format.

		/// <definition>
		/// Construct an angle in radians.
		/// </definition>
		Angle( float radians );

	public:
		/// <definition>
		/// Construct an angle to the value of zero.
		/// </definition>
		Angle();
	
		/// <definition>
		///  Copy constructor.
		/// </definition>
		Angle( const Angle & angle );

		/// <definition>
		/// Construct an angle from a string.
		/// </definition>
		Angle( std::string angle );

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

		/// <summary>
		/// Returns angle in radians.
		/// </summary>
		float ToRadians() const;

		/// <summary>
		/// Returns angle in degress.
		/// </summary>
        float ToDegrees() const;

		///<summary>
		/// Ensures our value is within 360 degrees, without loss of precision (if we are 367, then we become 7, etc.).
		/// Returns the change in magnitude relative to 360 (367 returns 1, -728 returns -2, etc.).
        ///</summary>
        int Normalize();

		/// <summary>
		/// Returns the sine of this angle.
		/// </summary>
		float SinOf() const;

		/// <summary>
		/// Returns the cosine of this angle.
		/// </summary>
		float CosOf() const;

		/// <summary>
		/// Convert from radians to a string.
		/// </summary>
		std::string ToString( bool radians = true ) const;
	};

	/// <definition>
	/// Construct an angle from radians.
	/// </definition>
	Angle AngleInRadians( float radians );

	/// <definition>
	/// Construct an angle from degrees.
	/// </definition>
	Angle AngleInDegrees( float degrees );

	/// <definition>
	/// Construct an angle with the value of pi.
	/// </definition>
	Angle AnglePI();

	/// <definition>
	/// Construct an angle with the value of pi * 2.
	/// </definition>
	Angle AnglePI2();

	/// <definition>
	/// Construct an angle with rthe value of half pi.
	/// </definition>
	Angle AnglePIHalf();
}
