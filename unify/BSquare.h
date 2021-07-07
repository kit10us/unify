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
	/// A boudning sphere.
	/// </summary>
	template< typename T >
	class BSquare
	{
	public:
		V2< T > sup;
		V2< T > inf;

		BSquare();
		BSquare( const V2< T > & inf, const V2< T > & sup );

		BSquare< T > operator * ( const V2< T > & muliplcand );
		
		void GenerateCorners( V2< T > * bounds );
		void Initialize( const V2< T > & inf = V2< T >::Zero(), const V2< T > & sup = V2< T >::Zero() );
		void AddPoint( const V2< T > & point );
		BSquare & AddBSquare( const BSquare< T > & boundingSquare );
		bool ContainsPoint( const V2< T > & point );
		const V2< T > Size();
	};
	#include <unify/BSquare.inl>
}

