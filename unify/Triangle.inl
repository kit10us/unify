// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

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
