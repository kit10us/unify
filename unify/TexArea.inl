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

 
namespace unify
{
	inline
	TexArea::TexArea(float ul_u, float ul_v, float dr_u, float dr_v)
		: ul(ul_u, ul_v)
		, dr(dr_u, dr_v)
	{
	}

	inline
	TexArea::TexArea(const TexCoords coordsUL, const TexCoords coordsDR)
		: ul(coordsUL)
		, dr(coordsDR)
	{
	}

	inline
	TexArea::TexArea(const std::string text)
	{
		// Named
		if (String::StringIs(text, "full"))
		{
			ul.u = 0.0f;
			ul.v = 0.0f;
			dr.u = 1.0f;
			dr.v = 1.0f;
		}
		else
		{
			std::vector< float > split = String::Split< float >(text, ',');
			ul.u = split[0];
			ul.v = split[1];
			dr.u = split[2];
			dr.v = split[3];
		}
	}

	inline
	bool TexArea::operator==(const TexArea& area) const
	{
		return ul == area.ul && dr == area.dr;
	}

	inline
	bool TexArea::operator!=(const TexArea& area) const
	{
		return !(*this == area);
	}

	inline
	float TexArea::Width() const
	{
		return dr.u - ul.u;
	}

	inline
	float TexArea::Height() const
	{
		return dr.v - ul.v;
	}

	inline
	Size< float > TexArea::Size() const
	{

		return unify::Size< float >(dr.u - ul.u, dr.v - ul.v);
	}

	inline
	TexCoords TexArea::UL() const
	{
		return ul;
	}

	inline
	TexCoords TexArea::UR() const
	{
		return TexCoords(dr.u, ul.v);
	}

	inline
	TexCoords TexArea::DL() const
	{
		return TexCoords(ul.u, dr.v);
	}

	inline
	TexCoords TexArea::DR() const
	{
		return dr;
	}

	inline
	bool TexArea::IsZero() const
	{
		return Width() == Height() == 0.0f;
	}

	inline
	TexArea unify::TexAreaOne()
	{
		return TexArea(0, 0, 1, 1);
	}

	inline
	TexArea unify::TexAreaZero()
	{
		return TexArea(0, 0, 0, 0);
	}

	inline
	TexArea unify::TexAreaFull()
	{
		return TexArea(0, 0, 1, 1);
	}

	inline
	TexArea unify::TexAreaDouble()
	{
		return TexArea(0, 0, 2, 2);
	}

	template<>
	inline
	std::string Cast(const TexArea in)
	{
		const auto& ul = in.ul;
		const auto& dr = in.dr;
		return "{" + Cast< std::string >(ul) + ", " + Cast< std::string >(dr) + "}";
	}
}