// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <string>

namespace unify
{
	class ColorUnit;

	/// <summary>
	/// Order of color components.
	/// </summary>
	enum Order {
		RGBA,
		ARGB,
		BGRA,
		ABGR,
	};

	/// <summary>
	/// A 32 bit color, 8 bits per component.
	/// </summary>
	class Color
	{
	public:
		typedef unsigned char Component;

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

		/// <summary>
		/// Set all color components.
		/// </summary>
        void SetRGBA( Component r, Component g, Component b, Component a );

		/// <summary>
		/// Returns the red color component.
		/// </summary>
		Component GetRed() const;

		/// <summary>
		/// Returns the green color component.
		/// </summary>
		Component GetGreen() const;

		/// <summary>
		/// Returns the blue color component.
		/// </summary>
		Component GetBlue() const;

		/// <summary>
		/// Returns the alpha color component.
		/// </summary>
		Component GetAlpha() const;

		/// <summary>
		/// Sets the red component of the color.
		/// </summary>
		void SetRed( Component r );

		/// <summary>
		/// Sets the green component of the color.
		/// </summary>		
		void SetGreen( Component g );

		/// <summary>
		/// Sets the blue component of the color.
		/// </summary>		
		void SetBlue( Component b );

		/// <summary>
		/// Sets the alpha component of the color.
		/// </summary>
		void SetAlpha( Component a );

		/// <summary>
		/// Interpulate between two colors colors. 
		void Interpulate( const Color colorA, const Color colorB, const float ratio );

		/// <summary>
		/// Returns a string representation fo a color.
		/// </summary>
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
}