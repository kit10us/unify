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
	/// A rectangle.
	/// </summary>
	template< typename T = int >
	class Rect
	{
	public:
		T left;
		T top;
		T right;
		T bottom;

		Rect();
		Rect( T l, T t, T r, T b );
		Rect( const V2< T > & ul, const V2< T > & dr );
        Rect( const V2< T > & ul, const Size< T > & size );

		T Width() const;
		T Height() const;

		V2< T > UL() const;
		V2< T > UR() const;
		V2< T > DL() const;
		V2< T > DR() const;

		Size< T > Size() const;

		void And( const Rect< T > & rect );

		Rect & operator += ( const Rect< T > & rect );
		Rect & operator -= ( const Rect< T > & rect );
		Rect operator + ( const Rect< T > & rect ) const;
		Rect operator - ( const Rect< T > & rect ) const;
		const Rect & operator = ( const Rect< T > & rect );

		void SizeTo( T width, T height );
		bool IsIn( T x, T y ) const;
		bool IsIn( const V2< T > & point ) const;
		void MoveTo( T x, T y );
		void MoveBy( T x, T y );
		void MoveTo( const V2< T > & pVec );
		void MoveBy( const V2< T > & pVec );
		void AddToRegion( const V2< T > & pVec );
	};
	#include <unify/Rect.inl>
}
