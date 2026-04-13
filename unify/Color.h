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
#include <unify/String.h>
#include <algorithm>
#include <string>

namespace unify
{
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
		using Component = uint8_t;

		friend Color ColorRGBA(Component r, Component g, Component b, Component a);

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
		Color(Component r, Component g, Component b, Component a);
		Color(const Color& color);
		explicit Color(std::string text, Order order = RGBA, Component defaultAlpha = 255);

		// CONVERSIONS
		operator unsigned int() const;

		// Overloaded operators
		// Note: We use a larger type to provide clamping. This might affect performance.
		Color& operator += (const Color& col);
		Color& operator -= (const Color& col);
		Color& operator *= (const Color& col);
		Color& operator /= (const Color& col);
		Color& operator *= (float val);
		Color& operator /= (float val);

		// binary operators
		Color operator + (const Color& col) const;
		Color operator - (const Color& col) const;
		Color operator * (const Color& col) const;
		Color operator / (const Color& col) const;
		Color operator * (float val) const;
		Color operator / (float val) const;

		bool operator == (const Color& col) const;
		bool operator != (const Color& col) const;

		/// <summary>
		/// Set all color components.
		/// </summary>
		void SetRGBA(Component r, Component g, Component b, Component a);

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
		void SetRed(Component r);

		/// <summary>
		/// Sets the green component of the color.
		/// </summary>		
		void SetGreen(Component g);

		/// <summary>
		/// Sets the blue component of the color.
		/// </summary>		
		void SetBlue(Component b);

		/// <summary>
		/// Sets the alpha component of the color.
		/// </summary>
		void SetAlpha(Component a);

		/// <summary>
		/// Interpolate between two colors colors.
		/// </summary> 
		void Interpolate(const Color colorA, const Color colorB, const float ratio);

		/// <summary>
		///	Get the order of the color.
		/// </summary>
		/// <returns>order</returns>
		unify::Order Order() const;

		/// <summary>
		/// Returns a string representation fo a color.
		/// </summary>
		std::string ToString(unify::Order order = RGBA) const;
	};

	inline Color ColorRGBA(Color::Component r, Color::Component g, Color::Component b, Color::Component a);
	inline Color ColorRGBA(unsigned int rgba);
	inline Color ColorARGB(Color::Component a, Color::Component r, Color::Component g, Color::Component b);
	inline Color ColorARGB(unsigned int argb);
	inline Color ColorRGB(Color::Component r, Color::Component g, Color::Component b);
	inline Color ColorWhite(Color::Component a = 255);
	inline Color ColorRed(Color::Component r = 255, Color::Component a = 255);
	inline Color ColorGreen(Color::Component g = 255, Color::Component a = 255);
	inline Color ColorBlue(Color::Component c = 255, Color::Component a = 255);
	inline Color ColorYellow(Color::Component y = 255, Color::Component a = 255);
	inline Color ColorCyan(Color::Component c = 255, Color::Component a = 255);
	inline Color ColorMagenta(Color::Component m = 255, Color::Component a = 255);
	inline Color ColorGrey(Color::Component grey, Color::Component a = 255);
	inline Color ColorBlack(Color::Component a = 255);
	inline Color ColorZero();
}

#include <unify/Color.inl>
