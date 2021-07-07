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


template< typename T >
RowColumn<T>::RowColumn()
: row( 0 )
, column( 0 )
{
}

template< typename T >
RowColumn<T>::RowColumn( T _row, T _column )
	: row( _row )
	, column( _column )
{
}

template< typename T >
RowColumn<T>::RowColumn( const RowColumn< T > & rc )
	: row( rc.row )
	, column( rc.column )
{
}

template< typename T >
RowColumn< T >::RowColumn( std::string text )
{
	std::vector< T > split = Split< T >( text, ',' );
    row = split[ 0 ];
    column = split[ 1 ];
}

template< typename T >
void RowColumn<T>::Zero()
{
	row = 0;
	column = 0;
}

template< typename T >
RowColumn<T> & RowColumn<T>::operator = ( const V2<T> & vec )
{
	row = vec.x;
	column = vec.y;
	return *this;
}
		
template< typename T >
RowColumn<T> & RowColumn<T>::operator = ( const RowColumn<T> & rc )
{
	row = rc.row;
	column = rc.column;
	return *this;
}

template< typename T >
RowColumn<T> & RowColumn<T>::operator += ( const RowColumn<T> & rc )
{
	row += rc.row;
	column += rc.column;
	return *this;
}

template< typename T >
RowColumn<T> & RowColumn<T>::operator -= ( const RowColumn<T> & rc )
{
	row -= rc.row;
	column -= rc.column;
	return *this;
}

template< typename T >
RowColumn<T> & RowColumn<T>::operator *= ( const RowColumn<T> & rc )
{
	row *= rc.row;
	column *= rc.column;
	return *this;
}

template< typename T >
RowColumn<T> & RowColumn<T>::operator /= ( const RowColumn<T> & rc )
{
	row /= rc.row;
	column /= rc.column;
	return *this;
}

template< typename T >
RowColumn<T> & RowColumn<T>::operator *= ( T val )
{
	row *= val;
	column *= val;
	return *this;
}

template< typename T >
RowColumn< T > & RowColumn< T >::operator /= ( T val )
{
	row /= val;
	column /= val;
	return *this;
}

// binarcolumn
template< typename T >
RowColumn< T > RowColumn< T >::operator + ( const RowColumn< T > & rc) const
{
	return RowColumn< T >( row + rc.row, column + rc.column );
}

template< typename T >
RowColumn< T > RowColumn< T >::operator - ( const RowColumn< T > & rc ) const
{
	return RowColumn< T >( row - rc.row, column - rc.column );
}

template< typename T >
RowColumn< T > RowColumn< T >::operator * ( const RowColumn< T > & rc ) const
{
	return RowColumn< T >( row * rc.row, column * rc.column );
}

template< typename T >
RowColumn< T > RowColumn< T >::operator / ( const RowColumn< T > & rc ) const
{
	return RowColumn< T >( row / rc.row, column / rc.column );
}

template< typename T >
RowColumn< T > RowColumn< T >::operator * ( T val ) const
{
	return RowColumn< T >( row * val, column * val );
}

template< typename T >
RowColumn< T > RowColumn< T >::operator / ( T val ) const
{
	return RowColumn< T >( row / val, column / val );
}

template< typename T >
bool RowColumn< T >::operator == ( const RowColumn< T >& rc ) const
{
	return( row == rc.row && column == rc.column );
}

template< typename T >
bool RowColumn< T >::operator != ( const RowColumn& rc ) const
{
	return( row != rc.row || column != rc.column );
}

template< typename T >
T RowColumn< T >::CellCount() const
{
	return row * column;
}

