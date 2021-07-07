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
#include <unify/V2.h>
#include <unify/V3.h>
#include <unify/V4.h>

namespace unify
{
	/// <summary>
	/// A sphere used to track a volume, typically of an object.
	/// </summary>
	template< typename T = float >
	class BSphere
	{
	public:
		// Public members to reduce possible speed issues.
		V3< T > center;
		T radius;

		BSphere();
		BSphere( const V3< T > & center );
		BSphere( const V3< T > & center, const T & radius );

		BSphere & operator+=( const BSphere< T > & sphere );
		BSphere & operator+=( V3< T > point );

		/// <summary>
		/// Returns the center of the bounding sphere.
		/// </summary>
		V3< T > GetCenter() const;

		/// <summary>
		/// Retruns the radius of the sphere.
		/// </summary>
		T GetRadius() const;

		/// <summary>
		/// Retruns the diameter of the sphere.
		/// </summary>
		T GetDiameter() const;

		/// <summary>
		/// Returns true if point lies within the bounding sphere.
		/// </summary>
		bool Contains( V3< T > point ) const;

		/// <summary>
		/// Returns true if a sphere overlaps/collides with another sphere.
		/// </summary>
		bool Collides( BSphere< T > sphere ) const;
	};

	#include <unify/BSphere.inl>
}


