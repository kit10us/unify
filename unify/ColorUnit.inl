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
		const float max = std::max<>({ component.r, component.g, component.b, component.a });
		return ColorUnit(component.r / max, component.g / max, component.b / max, component.a / max);
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
	ColorUnit::ColorUnit(float r, float g, float b, float a)
	{
		component.a = a;
		component.r = r;
		component.g = g;
		component.b = b;
	}

	inline
	ColorUnit::ColorUnit(const ColorUnit& color)
	{
		component.a = color.component.a;
		component.r = color.component.r;
		component.g = color.component.g;
		component.b = color.component.b;
	}

	inline
	ColorUnit::ColorUnit(std::string text, Order order, float defaultAlpha)
	{
		using namespace unify::String;

		component.r = 0;
		component.g = 0;
		component.b = 0;
		component.a = defaultAlpha;

		if (StringIs(text, "white"))
		{
			component.r = 1.0f;
			component.g = 1.0f;
			component.b = 1.0f;
		}
		else if (StringIs(text, "black"))
		{
			// Nothing (use the above defaults).
		}
		else if (StringIs(text, "red"))
		{
			component.r = 1.0f;
		}
		else if (StringIs(text, "green"))
		{
			component.g = 1.0f;
		}
		else if (StringIs(text, "blue"))
		{
			component.b = 1.0f;
		}
		else if (StringIs(text, "clear"))
		{
			component.a = 0.0f;
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
				component.r = split[0];
				component.g = split[1];
				component.b = split[2];
			}
			else if (split.size() == 4)
			{
				switch (order)
				{
				case RGBA:
					component.r = split[0];
					component.g = split[1];
					component.b = split[2];
					component.a = split[3];
					break;
				case ARGB:
					component.a = split[0];
					component.r = split[1];
					component.g = split[2];
					component.b = split[3];
					break;
				case BGRA:
					component.b = split[0];
					component.g = split[1];
					component.r = split[2];
					component.a = split[3];
					break;
				case ABGR:
					component.a = split[0];
					component.b = split[1];
					component.g = split[2];
					component.r = split[3];
					break;
				}
			}
		}
	}

	inline
	float ColorUnit::SumComponents()
	{
		return component.a + component.r + component.g + component.b;
	}

	inline
	ColorUnit& ColorUnit::operator += (const ColorUnit& col)
	{
		component.a += col.component.a;
		component.r += col.component.r;
		component.g += col.component.g;
		component.b += col.component.b;
		return *this;
	}

	inline
	ColorUnit& ColorUnit::operator -= (const  ColorUnit& col)
	{
		component.a -= col.component.a;
		component.r -= col.component.r;
		component.g -= col.component.g;
		component.b -= col.component.b;
		return *this;
	}

	inline
	ColorUnit& ColorUnit::operator *= (float val)
	{
		component.a *= val;
		component.r *= val;
		component.g *= val;
		component.b *= val;
		return *this;
	}

	inline
	ColorUnit& ColorUnit::operator /= (float val)
	{
		component.a /= val;
		component.r /= val;
		component.g /= val;
		component.b /= val;
		return *this;
	}

	inline
	ColorUnit ColorUnit::operator + (const ColorUnit& col) const
	{
		return ColorUnitARGB(component.a + col.component.a, component.r + col.component.r, component.g + col.component.g, component.b + col.component.b);
	}

	inline
	ColorUnit ColorUnit::operator - (const ColorUnit& col) const
	{
		return ColorUnitARGB(component.a - col.component.a, component.r - col.component.r, component.g - col.component.g, component.b - col.component.b);
	}

	inline
	ColorUnit ColorUnit::operator * (const ColorUnit& col) const
	{
		return ColorUnitARGB(component.a * col.component.a, component.r * col.component.r, component.g * col.component.g, component.b * col.component.b);
	}

	inline
	ColorUnit ColorUnit::operator / (const ColorUnit& col) const
	{
		return ColorUnitARGB(component.a / col.component.a, component.r / col.component.r, component.g / col.component.g, component.b / col.component.b);
	}

	inline
	ColorUnit ColorUnit::operator * (float val) const
	{
		return ColorUnitARGB(component.a * val, component.r * val, component.g * val, component.b * val);
	}

	inline
	ColorUnit ColorUnit::operator / (float val) const
	{
		return ColorUnitARGB(component.a / val, component.r / val, component.g / val, component.b / val);
	}

	inline
	bool ColorUnit::operator == (const ColorUnit& col) const
	{
		return(component.a == col.component.a && component.r == col.component.r && component.g == col.component.g && component.b == col.component.b);
	}

	inline
	bool ColorUnit::operator != (const ColorUnit& col) const
	{
		return(component.a != col.component.a || component.r != col.component.r || component.g != col.component.g || component.b != col.component.b);
	}

	inline
	void ColorUnit::SetRed(float pr)
	{
		component.r = pr;
	}

	inline
	void ColorUnit::SetGreen(float pg)
	{
		component.g = pg;
	}

	inline
	void ColorUnit::SetBlue(float pb)
	{
		component.b = pb;
	}

	inline
	void ColorUnit::SetAlpha(float pa)
	{
		component.a = pa;
	}

	inline
	void ColorUnit::SetRGBA(float ri, float gi, float bi, float ai)
	{
		component.r = ri;
		component.g = gi;
		component.b = bi;
		component.a = ai;
	}

	inline
	std::string ColorUnit::ToString(ColorUnit::Order order) const
	{
		switch (order)
		{
		case RGBA:
		default:
			return Cast< std::string >(component.r) + ", " + Cast< std::string >(component.g) + ", " + Cast< std::string >(component.b) + ", " + Cast< std::string >(component.a);
		case ARGB:
			return Cast< std::string >(component.a) + ", " + Cast< std::string >(component.r) + ", " + Cast< std::string >(component.g) + ", " + Cast< std::string >(component.b);
		case BGRA:
			return Cast< std::string >(component.b) + ", " + Cast< std::string >(component.g) + ", " + Cast< std::string >(component.r) + ", " + Cast< std::string >(component.a);
		case ABGR:
			return Cast< std::string >(component.a) + ", " + Cast< std::string >(component.b) + ", " + Cast< std::string >(component.g) + ", " + Cast< std::string >(component.r);
		}
	}
}