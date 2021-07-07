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


template< typename T>
Triangle< T >::Triangle( const T & v1, const T & v2, const T & v3 )
{
	v[ 0 ] = v1;
	v[ 1 ] = v2;
	v[ 2 ] = v3;
}

template< typename T>
Triangle< T > & Triangle< T >::operator = ( const Triangle & triangle )
{
	v[ 0 ] = triangle.v[ 0 ];
	v[ 1 ] = triangle.v[ 1 ];
	v[ 2 ] = triangle.v[ 2 ];
	return *this;
}

template< typename T >
Triangle< T > & Triangle< T >::operator+=( T value )
{
    std::for_each( &v[ 0 ], &v[ 2 ], std::bind2nd( std::plus< T >(), value ) );
    return *this;
}

template< typename T >
Triangle< T > Triangle< T >::operator+( T value )
{
    Triangle newTriangle( *this );
    newTriangle += value;
    return newTriangle;
}
