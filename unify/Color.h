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

		friend Color ColorRGBA( Component r, Component g, Component b, Component a );
		friend Color ColorRGBA( unsigned int rgba );
		friend Color ColorARGB( Component a, Component r, Component g, Component b );
		friend Color ColorARGB( unsigned int argb );
		friend Color ColorRGB( Component r, Component g, Component b );
		friend Color ColorWhite( Component a );
		friend Color ColorRed( Component r, Component a );
		friend Color ColorGreen( Component g, Component a );
		friend Color ColorBlue( Component c, Component a );
		friend Color ColorYellow( Component y, Component a );
		friend Color ColorCyan( Component c, Component a );
		friend Color ColorMagenta( Component m, Component a );
		friend Color ColorGrey( Component grey, Component a );
		friend Color ColorBlack( Component a );
		friend Color ColorZero();

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
	};

	Color ColorRGBA( Color::Component r, Color::Component g, Color::Component b, Color::Component a );
	Color ColorRGBA( unsigned int rgba );
	Color ColorARGB( Color::Component a, Color::Component r, Color::Component g, Color::Component b );
	Color ColorARGB( unsigned int argb );
	Color ColorRGB( Color::Component r, Color::Component g, Color::Component b );
	Color ColorWhite( Color::Component a = 255 );
	Color ColorRed( Color::Component r = 255, Color::Component a = 255 );
	Color ColorGreen( Color::Component g = 255, Color::Component a = 255 );
	Color ColorBlue( Color::Component c = 255, Color::Component a = 255 );
	Color ColorYellow( Color::Component y = 255, Color::Component a = 255 );
	Color ColorCyan( Color::Component c = 255, Color::Component a = 255 );
	Color ColorMagenta( Color::Component m = 255, Color::Component a = 255 );
	Color ColorGrey( Color::Component grey, Color::Component a = 255 );
	Color ColorBlack( Color::Component a = 255 );
	Color ColorZero(); 
}