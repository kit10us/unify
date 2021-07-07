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

namespace unify
{
	template < class T >
	class Size3
	{
	public:
		T width, height, depth;

		Size3();
		Size3( T width, T height, T depth );
		Size3( const Size3< T > & size );
		explicit Size3( std::string text );
				
		void Zero();

		// Conversion operators...
		Size3< T > & operator = ( const V3< T > & vec );

		// binary operators...
		Size3< T > & operator = ( const Size3< T > & size );

		Size3< T > & operator += ( const Size3< T > & size );
		Size3< T > & operator -= ( const Size3< T > & size );
		Size3< T > & operator *= ( const Size3< T > & size );
		Size3< T > & operator /= ( const Size3< T > & size );
		Size3< T > & operator *= ( T val );
		Size3< T > & operator /= ( T val );

		Size3< T > operator + ( const Size3< T > & size) const;
		Size3< T > operator - ( const Size3< T > & size ) const;
		Size3< T > operator * ( const Size3< T > & size ) const;
		Size3< T > operator / ( const Size3< T > & size ) const;
		Size3< T > operator * ( T val ) const;
		Size3< T > operator / ( T val ) const;

		bool operator == ( const Size3< T > & size ) const;
		bool operator != ( const Size3< T > & size ) const;

        template< typename T2 >
        operator Size< T2 >()
        {
            return Size< T2 >( static_cast< T2 >( width ), static_cast< T2 >( height ), static_cast< T2 >( depth ) );
        }

		std::string ToString() const;


        T Units() const;

        // Returns a linear index assuming horizontal major. 
        T LinearIndex( T h, T v, T d ) const;
    };
	#include <unify/Size3.inl>
}