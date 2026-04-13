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

#include <unify/Color.h>
#include <unify/ColorUnit.h>
#include <unify/Cast.h>


namespace unify
{
	template<>
	inline
	Color Cast(ColorUnit col)
	{
		auto cap = std::max<>({ col.component.r, col.component.g, col.component.b, col.component.a });
		return Color(255 * unify::Color::Component(col.component.r / cap), 255 * unify::Color::Component(col.component.g / cap), 255 * unify::Color::Component(col.component.b / cap), 255 * unify::Color::Component(col.component.a / cap));
	}

	template<>
	inline
	ColorUnit Cast(Color col)
	{
		return ColorUnit(255.0f / col.component.r, 255.0f / col.component.g, 255.0f / col.component.b, 255.0f / col.component.a);
	}
}