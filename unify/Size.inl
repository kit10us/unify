// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

template< typename T >
Size< T >::Size()
{
}

template< typename T >
Size< T >::Size( T _width, T _height )
: width( _width )
, height( _height )
{
}

template< typename T >
Size< T >::Size( const Size< T > & size )
: width( size.width )
, height( size.height )
{
}

template< typename T >
Size< T >::Size( std::string text )
{
	std::vector< T > split = Split< T >( text, ',' );
    width = split[ 0 ];
    height = split[ 1 ];
}

template< typename T >
T Size< T >::Width() const
{
	return width;
}

template< typename T >
T Size< T >::Height() const
{
	return height;
}

template< typename T >
void Size< T >::Zero()
{
	width = 0;
	height = 0;
}

template< typename T >
Size< T > & Size< T >::operator = ( const V2< T > & vec )
{
	width = vec.x;
	height = vec.y;
	return *this;
}
		
template< typename T >
Size< T > & Size< T >::operator = ( const Size< T > & size )
{
	width = size.width;
	height = size.height;
	return *this;
}

template< typename T >
Size< T > & Size< T >::operator += ( const Size< T > & size )
{
	width += size.width;
	height += size.height;
	return *this;
}

template< typename T >
Size< T > & Size< T >::operator -= ( const Size< T > & size )
{
	width -= size.width;
	height -= size.height;
	return *this;
}

template< typename T >
Size< T > & Size< T >::operator *= ( const Size< T > & size )
{
	width *= size.width;
	height *= size.height;
	return *this;
}

template< typename T >
Size< T > & Size< T >::operator /= ( const Size< T > & size )
{
	width /= size.width;
	height /= size.height;
	return *this;
}

template< typename T >
Size< T > & Size< T >::operator *= ( T val )
{
	width *= val;
	height *= val;
	return *this;
}

template< typename T >
Size< T > & Size< T >::operator /= ( T val )
{
	width /= val;
	height /= val;
	return *this;
}

template< typename T >
Size< T > Size< T >::operator + ( const Size< T > & size) const
{
	return Size< T >( width + size.width, height + size.height );
}

template< typename T >
Size< T > Size< T >::operator - ( const Size< T > & size ) const
{
	return Size< T >( width - size.width, height - size.height );
}

template< typename T >
Size< T > Size< T >::operator * ( const Size< T > & size ) const
{
	return Size< T >( width * size.width, height * size.height );
}

template< typename T >
Size< T > Size< T >::operator / ( const Size< T > & size ) const
{
	return Size< T >( width / size.width, height / size.height );
}

template< typename T >
Size< T > Size< T >::operator * ( T val ) const
{
	return Size< T >( width * val, height * val );
}

template< typename T >
Size< T > Size< T >::operator / ( T val ) const
{
	return Size< T >( width / val, height / val );
}

template< typename T >
bool Size< T >::operator == ( const Size< T >& size ) const
{
	return( width == size.width && height == size.height );
}

template< typename T >
bool Size< T >::operator != ( const Size< T >& size ) const
{
	return( width != size.width || height != size.height );
}

template< typename T >
std::string Size< T >::ToString() const
{
	return Cast< std::string >( width ) + ", " + Cast< std::string >( height );
}

template< typename T >
T Size< T >::Units() const
{
    return width * height;
}

template< typename T >
T Size< T >::LinearIndex( T h, T v ) const
{
    return h + v * width;
}

template< typename T >
V2< T > Size< T >::LinearToV2( T index ) const
{
    T x = index / width;
    return V2< T >( x, index - ( x * width ) );
}

template< typename T >
float Size< T >::AspectRatioHW() const
{
	return (float)height / width;
}

template< typename T >
float Size< T >::AspectRatioWH() const
{
	return (float)width / height;
}

template< typename T >
unify::V2< T > unify::Size< T >::Center() const
{
	return unify::V2< T >( width / 2, height / 2 );
}
