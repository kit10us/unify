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

#include <unify/String.h>
#include <algorithm>


namespace unify
{
	inline
	ColorUnit ColorUnit::Normalize() const
	{
		const float max = std::max<>({ r, g, b, a });
		return ColorUnit(r / max, g / max, b / max, a / max);
	}

	inline
	ColorUnit ColorUnitRGBA(float r, float g, float b, float a)
	{
		return ColorUnit(r, g, b, a);
	}

	inline
	ColorUnit ColorUnitARGB(float a, float r, float g, float b)
	{
		return ColorUnitRGBA(r, g, b, a);
	}

	inline
	ColorUnit ColorUnitRGB(float r, float g, float b)
	{
		return ColorUnitRGBA(r, g, b, 1.0f);
	}

	inline
	ColorUnit ColorUnitWhite(float a)
	{
		return ColorUnitRGBA(1.0f, 1.0f, 1.0f, a);
	}

	inline
	ColorUnit ColorUnitRed(float r, float a)
	{
		return ColorUnitRGBA(r, 0.0f, 0.0f, a);
	}

	inline
	ColorUnit ColorUnitGreen(float g, float a)
	{
		return ColorUnitRGBA(0.0f, g, 0.0f, a);
	}

	inline
	ColorUnit ColorUnitBlue(float b, float a)
	{
		return ColorUnitRGBA(0.0f, 0.0f, b, a);
	}

	inline
	ColorUnit ColorUnitYellow(float b, float a)
	{
		return ColorUnitRGBA(b, b, 0.0f, a);
	}

	inline
	ColorUnit ColorUnitCyan(float b, float a)
	{
		return ColorUnitRGBA(b, b, 0.0f, a);
	}

	inline
	ColorUnit ColorUnitMagenta(float b, float a)
	{
		return ColorUnitRGBA(b, 0.0f, b, a);
	}

	inline
	ColorUnit ColorUnitGrey(float grey, float a)
	{
		return ColorUnitRGBA(grey, grey, grey, a);
	}

	inline
	ColorUnit ColorUnitBlack(float a)
	{
		return ColorUnitRGBA(0, 0, 0, a);
	}

	inline
	ColorUnit ColorUnitZero()
	{
		return ColorUnitRGBA(0, 0, 0, 0);
	}

	inline
	ColorUnit ColorUnitLerp(ColorUnit l, ColorUnit r, float ratio)
	{
		return l * (1.0f - ratio) + r * ratio;
	}

	inline
	ColorUnit::ColorUnit()
	{
	}

	inline
	ColorUnit::ColorUnit(float r_in, float g_in, float b_in, float a_in)
	{
		a = a_in;
		r = r_in;
		g = g_in;
		b = b_in;
	}

	inline
	ColorUnit::ColorUnit(const ColorUnit& color)
	{
		a = color.a;
		r = color.r;
		g = color.g;
		b = color.b;
	}

	inline
	ColorUnit::ColorUnit(std::string text, Order order, float defaultAlpha)
	{
		using namespace ::unify::String;
		r = 0;
		g = 0;
		b = 0;
		a = defaultAlpha;

		if (StringIs(text, "white"))
		{
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
		}
		else if (StringIs(text, "black"))
		{
			// Nothing (use the above defaults).
		}
		else if (StringIs(text, "red"))
		{
			r = 1.0f;
		}
		else if (StringIs(text, "green"))
		{
			g = 1.0f;
		}
		else if (StringIs(text, "blue"))
		{
			b = 1.0f;
		}
		else if (StringIs(text, "clear"))
		{
			a = 0.0f;
		}
		else
		{
			std::vector< float > split = Split< float >(text, ',');
			if (split.size() == 1)
			{
				split = SplitOnWhitespace< float >(text);
			}

			if (split.size() == 3)
			{
				r = split[0];
				g = split[1];
				b = split[2];
			}
			else if (split.size() == 4)
			{
				switch (order)
				{
				case RGBA:
					r = split[0];
					g = split[1];
					b = split[2];
					a = split[3];
					break;
				case ARGB:
					a = split[0];
					r = split[1];
					g = split[2];
					b = split[3];
					break;
				case BGRA:
					b = split[0];
					g = split[1];
					r = split[2];
					a = split[3];
					break;
				case ABGR:
					a = split[0];
					b = split[1];
					g = split[2];
					r = split[3];
					break;
				}
			}
		}
	}

	inline
	float ColorUnit::SumComponents()
	{
		return a + r + g + b;
	}

	inline
	ColorUnit& ColorUnit::operator += (const ColorUnit& col)
	{
		a += col.a;
		r += col.r;
		g += col.g;
		b += col.b;
		return *this;
	}

	inline
	ColorUnit& ColorUnit::operator -= (const  ColorUnit& col)
	{
		a -= col.a;
		r -= col.r;
		g -= col.g;
		b -= col.b;
		return *this;
	}

	inline
	ColorUnit& ColorUnit::operator *= (float val)
	{
		a *= val;
		r *= val;
		g *= val;
		b *= val;
		return *this;
	}

	inline
	ColorUnit& ColorUnit::operator /= (float val)
	{
		a /= val;
		r /= val;
		g /= val;
		b /= val;
		return *this;
	}

	inline
	ColorUnit ColorUnit::operator + (const ColorUnit& col) const
	{
		return ColorUnitARGB(a + col.a, r + col.r, g + col.g, b + col.b);
	}

	inline
	ColorUnit ColorUnit::operator - (const ColorUnit& col) const
	{
		return ColorUnitARGB(a - col.a, r - col.r, g - col.g, b - col.b);
	}

	inline
	ColorUnit ColorUnit::operator * (const ColorUnit& col) const
	{
		return ColorUnitARGB(a * col.a, r * col.r, g * col.g, b * col.b);
	}

	inline
	ColorUnit ColorUnit::operator / (const ColorUnit& col) const
	{
		return ColorUnitARGB(a / col.a, r / col.r, g / col.g, b / col.b);
	}

	inline
	ColorUnit ColorUnit::operator * (float val) const
	{
		return ColorUnitARGB(a * val, r * val, g * val, b * val);
	}

	inline
	ColorUnit ColorUnit::operator / (float val) const
	{
		return ColorUnitARGB(a / val, r / val, g / val, b / val);
	}

	inline
	bool ColorUnit::operator == (const ColorUnit& col) const
	{
		return(a == col.a && r == col.r && g == col.g && b == col.b);
	}

	inline
	bool ColorUnit::operator != (const ColorUnit& col) const
	{
		return(a != col.a || r != col.r || g != col.g || b != col.b);
	}

	inline
	void ColorUnit::SetRed(float pr)
	{
		r = pr;
	}

	inline
	void ColorUnit::SetGreen(float pg)
	{
		g = pg;
	}

	inline
	void ColorUnit::SetBlue(float pb)
	{
		b = pb;
	}

	inline
	void ColorUnit::SetAlpha(float pa)
	{
		a = pa;
	}

	inline
	void ColorUnit::SetRGBA(float ri, float gi, float bi, float ai)
	{
		r = ri;
		g = gi;
		b = bi;
		a = ai;
	}

	inline
	std::optional<std::string> ColorUnit::ToString(ColorUnit::Order order) const
	{
		auto r_s = ::unify::ToString(r);
		auto g_s = ::unify::ToString(g);
		auto b_s = ::unify::ToString(b);
		auto a_s = ::unify::ToString(a);

		if (!r_s || !g_s || !b_s || !a_s)
		{
			return std::nullopt;
		}

		switch (order)
		{
		case RGBA:
		default:
			return *r_s + ", " + *g_s + ", " + *b_s + ", " + *a_s;
		case ARGB:
			return *a_s + ", " + *r_s + ", " + *g_s + ", " + *b_s;
		case BGRA:
			return *b_s + ", " + *g_s + ", " + *r_s + ", " + *a_s;
		case ABGR:
			return *a_s + ", " + *b_s + ", " + *g_s + ", " + *r_s;
		}
	}
}