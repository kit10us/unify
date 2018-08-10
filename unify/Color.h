// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <string>

namespace unify
{
	class ColorUnit;

	class Color
	{
	public:
		typedef unsigned char Component;

		enum Order {
			RGBA,
			ARGB,
			BGRA,
			ABGR,
		};

        union {
		    unsigned int c;
            struct {
				Component r;
                Component g;
				Component b;
                Component a;
            } component;
			unsigned char linear[4];
        };

		Color();
		Color( Component r, Component g, Component b, Component a );
		Color( const Color & color );
		explicit Color( std::string text, Order order = RGBA, Component defaultAlpha = 255 );
		explicit Color( const ColorUnit & colorUnit );

        // CONVERSIONS
		operator ColorUnit() const;
		operator unsigned int() const;

        // Overloaded operators
        // Note: We use a larger type to provide clamping. This might affect performance.
		Color & operator += ( const Color & col );
		Color & operator -= ( const Color & col );
		Color & operator *= ( const Color & col );
		Color & operator /= ( const Color & col );
        Color & operator *= ( float val );
		Color & operator /= ( float val );

		// binary operators
		Color operator + ( const Color & col ) const;
		Color operator - ( const Color & col ) const;
		Color operator * ( const Color & col ) const;
		Color operator / ( const Color & col ) const;
		Color operator * ( float val ) const;
		Color operator / ( float val ) const;

		bool operator == ( const Color & col ) const;
		bool operator != ( const Color & col ) const;

        void SetRGBA( Component r, Component g, Component b, Component a );

		Component GetRed() const;
		Component GetGreen() const;
		Component GetBlue() const;
		Component GetAlpha() const;

		void SetRed( Component r );
		void SetGreen( Component g );
		void SetBlue( Component b );
		void SetAlpha( Component a );

		void Modulate( const Color in1, const Color in2 );
		void ModulateByRatio( const Color in1, const Color in2, const float ratio );
		void Modulate4( const Color in1, const Color in2, const Color in3, const Color in4 );

		std::string ToString( Order order = RGBA ) const;

		// Named constructors...
		static Color ColorRGBA( Component r, Component g, Component b, Component a );
		static Color ColorRGBA( unsigned int rgba );
		static Color ColorARGB( Component a, Component r, Component g, Component b );
		static Color ColorARGB( unsigned int argb );
		static Color ColorRGB( Component r, Component g, Component b );
		static Color ColorWhite( Component a = 255 );
		static Color ColorRed( Component r = 255, Component a = 255 );
		static Color ColorGreen( Component g = 255, Component a = 255 );
		static Color ColorBlue( Component c = 255, Component a = 255 );
		static Color ColorYellow( Component y = 255, Component a = 255 );
		static Color ColorCyan( Component c = 255, Component a = 255 );
		static Color ColorMagenta( Component m = 255, Component a = 255 );
		static Color ColorGrey( Component grey, Component a = 255 );
		static Color ColorBlack( Component a = 255);
		static Color ColorZero();
	};
}  // namespace unify