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
		friend ColorUnit ColorUnitRGBA( float r, float g, float b, float a );
		friend ColorUnit ColorUnitARGB( float a, float r, float g, float b );
		friend ColorUnit ColorUnitRGB( float r, float g, float b );
		friend ColorUnit ColorUnitWhite( float a );
		friend ColorUnit ColorUnitRed( float r, float a );
		friend ColorUnit ColorUnitGreen( float g, float a );
		friend ColorUnit ColorUnitBlue( float b, float a );	
		friend ColorUnit ColorUnitYellow( float b, float a );
		friend ColorUnit ColorUnitCyan( float b, float a );
		friend ColorUnit ColorUnitMagenta( float b, float a );
		friend ColorUnit ColorUnitGrey( float grey, float a );
		friend ColorUnit ColorUnitBlack( float a );
		friend ColorUnit ColorUnitZero();
		friend ColorUnit ColorUnitLerp( ColorUnit l, ColorUnit r, float ratio );

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

		ColorUnit operator + ( const ColorUnit & col ) const;
		ColorUnit operator - ( const ColorUnit & col ) const;
		ColorUnit operator * ( const ColorUnit & col ) const;
		ColorUnit operator / ( const ColorUnit & col ) const;
		ColorUnit operator * ( float val ) const;
		ColorUnit operator / ( float val ) const;

		bool operator == ( const ColorUnit & col ) const;
		bool operator != ( const ColorUnit & col ) const;

		/// <summary>
		/// Set the red component.
		/// </summary
		void SetRed( float r );

		/// <summary>
		/// Set the green component.
		/// </summary
		void SetGreen( float g );

		/// <summary>
		///Set the blue component.
		/// </summary
		void SetBlue( float b );

		/// <summary>
		/// Set the alpha component.
		/// </summary
		void SetAlpha( float a );

		std::string ToString( Order order = RGBA ) const;
	};

	ColorUnit ColorUnitRGBA( float r, float g, float b, float a );
	ColorUnit ColorUnitARGB( float a, float r, float g, float b );
	ColorUnit ColorUnitRGB( float r, float g, float b );
	ColorUnit ColorUnitWhite( float a = 1.0f );
	ColorUnit ColorUnitRed( float r = 1.0f, float a = 1.0f );
	ColorUnit ColorUnitGreen( float g = 1.0f, float a = 1.0f );
	ColorUnit ColorUnitBlue( float b = 1.0f, float a = 1.0f );
	ColorUnit ColorUnitYellow( float b = 1.0f, float a = 1.0f );
	ColorUnit ColorUnitCyan( float b = 1.0f, float a = 1.0f );
	ColorUnit ColorUnitMagenta( float b = 1.0f, float a = 1.0f );
	ColorUnit ColorUnitGrey( float grey, float a = 1.0f );
	ColorUnit ColorUnitBlack( float a = 1.0f );
	ColorUnit ColorUnitZero();
	ColorUnit ColorUnitLerp( ColorUnit l, ColorUnit r, float ratio );
}
