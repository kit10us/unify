// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <string>

namespace unify
{
	class Color;

	/// <summary>
	// Definition of colors whose components are normalized (0.0 to 1.0) at common ranges.
	/// </summary>
	class ColorUnit
	{
	public:
		enum Order {
			RGBA,
			ARGB,
			BGRA,
			ABGR,
		};

		// Named constructors...
		static ColorUnit ColorUnitRGBA( float r, float g, float b, float a );
		static ColorUnit ColorUnitARGB( float a, float r, float g, float b );
		static ColorUnit ColorUnitRGB( float r, float g, float b );
		static ColorUnit ColorUnitWhite( float a = 1.0f );
		static ColorUnit ColorUnitRed( float r = 1.0f, float a = 1.0f );
		static ColorUnit ColorUnitGreen( float g = 1.0f, float a = 1.0f );
		static ColorUnit ColorUnitBlue( float b = 1.0f, float a = 1.0f );	
		static ColorUnit ColorUnitYellow( float b = 1.0f, float a = 1.0f );
		static ColorUnit ColorUnitCyan( float b = 1.0f, float a = 1.0f );
		static ColorUnit ColorUnitMagenta( float b = 1.0f, float a = 1.0f );
		static ColorUnit ColorUnitGrey( float grey, float a = 1.0f );
		static ColorUnit ColorUnitBlack( float a = 1.0f);
		static ColorUnit ColorUnitZero();
		static ColorUnit ColorUnitLerp( ColorUnit l, ColorUnit r, float ratio );

		union {
			struct {
				float r, g, b, a;
			} component;
			float linear[4];
		};

		ColorUnit();
		ColorUnit( float r, float g, float b, float a );
		ColorUnit( const ColorUnit & color );
		explicit ColorUnit( std::string text, Order order = RGBA, float defaultAlpha = 1.0f );

		void SetRGBA( float r, float g, float b, float a );

		// CONVERSIONS
		operator Color();

		// Combines the various components into a single scalar using addition: result = a + r + g + b;
		float SumComponents();

		// OPERATOR OVERLOADING MEMBER FUNCTIONS
		ColorUnit & operator += ( const ColorUnit & col );
		ColorUnit & operator -= ( const ColorUnit & col );
		ColorUnit & operator *= ( float val );
		ColorUnit & operator /= ( float  val );

		// unary operators
		//V3 operator + () const;
		//V3 operator - () const;

		// binary operators
		ColorUnit operator + ( const ColorUnit & col ) const;
		ColorUnit operator - ( const ColorUnit & col ) const;
		ColorUnit operator * ( const ColorUnit & col ) const;
		ColorUnit operator / ( const ColorUnit & col ) const;
		ColorUnit operator * ( float val ) const;
		ColorUnit operator / ( float val ) const;

		//friend V3 operator * ( float, const struct V3& );

		bool operator == ( const ColorUnit & col ) const;
		bool operator != ( const ColorUnit & col ) const;

		void SetRed( float r );
		void SetGreen( float g );
		void SetBlue( float b );
		void SetAlpha( float a );

		std::string ToString( Order order = RGBA ) const;
	};
} // namespace unify
