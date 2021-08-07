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
#include <unify/String.h>
#include <vector>

namespace unify
{
	template < class T > class V2;

	template < class T >
	class Size
	{
	public:
		T width, height;

		Size();
		Size( T width, T height );
		Size( const Size< T > & size );
		explicit Size( std::string text );
				
		void Zero();

		// Conversion operators...
		Size< T > & operator = ( const V2< T > & vec );

		// binary operators...
		Size< T > & operator = ( const Size< T > & size );

		Size< T > & operator += ( const Size< T > & size );
		Size< T > & operator -= ( const Size< T > & size );
		Size< T > & operator *= ( const Size< T > & size );
		Size< T > & operator /= ( const Size< T > & size );
		Size< T > & operator *= ( T val );
		Size< T > & operator /= ( T val );

		Size< T > operator + ( const Size< T > & size) const;
		Size< T > operator - ( const Size< T > & size ) const;
		Size< T > operator * ( const Size< T > & size ) const;
		Size< T > operator / ( const Size< T > & size ) const;
		Size< T > operator * ( T val ) const;
		Size< T > operator / ( T val ) const;

		bool operator == ( const Size< T > & size ) const;
		bool operator != ( const Size< T > & size ) const;

        template< typename T2 >
        operator Size< T2 >()
        {
            return Size< T2 >( static_cast< T2 >( width ), static_cast< T2 >( height ) );
        }

		std::string ToString() const;

		T Width() const;
		T Height() const;

        T Units() const;

        // Returns a linear index assuming horizontal major. 
        T LinearIndex( T h, T v ) const;

        /// Returns an interum point based on the linear index assuming horizontal major.
        V2< T > LinearToV2( T index ) const;

		float AspectRatioHW() const;
		float AspectRatioWH() const;

		unify::V2< T > Center() const;
	};
	#include <unify/Size.inl>
}
