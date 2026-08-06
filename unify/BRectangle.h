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

namespace unify
{
	/// <summary>
	/// A 2D bounding rectangle.
	/// </summary>
	template< typename T >
	class BRectangle
	{
		public:
		V2< T > ul;
		V2< T > dr;

		BRectangle();
		BRectangle( const V2< T > & ul, const V2< T > & dr );

		BRectangle < T > operator * (const V2< T >& muliplcand);

		bool operator == (const BRectangle& other) const;

		/// <summary>
		/// In-place normalize the bounding rectangle, ensuring that the ul is less than or equal to the dr.
		/// </summary>
		/// <returns> true if the bounding rectangle was changed, false if it was already normalized.</returns>
		bool Normalize();

		/// <summary>
		/// Returns a normalized copy of the bounding rectangle, ensuring that the ul is less than or equal to the dr.
		/// </summary>
		/// <returns>a normalized copy of the bounding rectangle.</returns>
		BRectangle Normalized() const;
		
		/// <summary>
		/// Generate a square from specified bounding corners.
		/// </summary>
		/// <param name="bounds"></param>
		void GenerateCorners( V2< T > * bounds );

		/// <summary>
		/// Given a point, if that point is beyond our current bounds, increase our bounds to encompass it.
		/// </summary>
		void Add( const V2< T > & point );

		/// <summary>
		/// Returns true if a point is within our bounding rectangle.
		/// </summary>
		bool Contains( const V2< T > & point );
		
		/// <summary>
		/// Returns true if a point is within our bounding rectangle.
		/// </summary>
		bool Contains( const BRectangle< T > & brect );

		/// <summary>
		/// Returns the size of the rectangle.
		/// </summary>
		const V2< T > Size();
	};

	// For foreward compatibility, we will define BRect as an alias for BRectangle.
	template<typename T>
	using BRect = BRectangle<T>;

	#include <unify/BRectangle.inl>
}

