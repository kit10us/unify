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

namespace unify
{
	/// <summary>
	/// A 2D bounding rectangle.
	/// </summary>
	template< typename T >
	class BRectangle
	{
	public:
		V2< T > sup;
		V2< T > inf;

		BRectangle();
		BRectangle( const V2< T > & inf, const V2< T > & sup );

		BRectangle < T > operator * (const V2< T >& muliplcand);
		
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
		/// Given a bounding rectangle, if that bounding square is beyond our current bounds, increase our bounds to encompass it.
		/// </summary>
		BRectangle & Add( const BRectangle< T > & boundingRectangle );

		/// <summary>
		/// Returns true if a point is within our bounding rectangle.
		/// </summary>
		bool Contains( const V2< T > & point );
		
		/// <summary>
		/// Returns the size of the rectangle.
		/// </summary>
		const V2< T > Size();
	};
	#include <unify/BRectangle.inl>
}

