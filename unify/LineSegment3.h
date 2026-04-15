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
#include <unify/V3.h>


namespace unify
{
	/// <summary>
	/// A line segment in 3D space.
	/// </summary>
	template< typename T = float >
	class LineSegment3
	{
	public:
		// Public members to reduce possible speed issues.
		V3< T > begin;
		V3< T > end;

		LineSegment3() = default;

		LineSegment3( const V3< T > begin, const V3< T > end );

		/// <summary>
		/// Returns the length of the line segment.
		/// </summary>
		T Length() const;
    };
}

#include <unify/LineSegment3.inl>
