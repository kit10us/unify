// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

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

