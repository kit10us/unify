// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

template< typename T >
Size3<T>::Size3()
{
}

template< typename T >
Size3<T>::Size3( T _width, T _height, T _depth )
	: width( _width )
	, height( _height )
	, depth( _depth )
{
}

template< typename T >
Size3<T>::Size3( const Size3< T > & size )
	: width( size.width )
	, height( size.height )
	, depth( size.depth )
{
}

template< typename T >
Size3< T >::Size3( std::string text )
{
	std::vector< T > split = Split< T >( text, ',' );
    width = split[ 0 ];
    height = split[ 1 ];
    depth = split[ 2 ];
}

template< typename T >
void Size3<T>::Zero()
{
	width = 0;
	height = 0;
	depth = 0;
}

template< typename T >
Size3<T> & Size3<T>::operator = ( const V3<T> & vec )
{
	width = vec.x;
	height = vec.y;
	depth = vec.z;
	return *this;
}
		
template< typename T >
Size3<T> & Size3<T>::operator = ( const Size3<T> & size )
{
	width = size.width;
	height = size.height;
	depth = size.depth;
	return *this;
}

template< typename T >
Size3<T> & Size3<T>::operator += ( const Size3<T> & size )
{
	width += size.width;
	height += size.height;
	depth += size.depth;
	return *this;
}

template< typename T >
Size3<T> & Size3<T>::operator -= ( const Size3<T> & size )
{
	width -= size.width;
	height -= size.height;
	depth -= size.depth;
	return *this;
}

template< typename T >
Size3<T> & Size3<T>::operator *= ( const Size3<T> & size )
{
	width *= size.width;
	height *= size.height;
	depth *= size.depth;
	return *this;
}

template< typename T >
Size3<T> & Size3<T>::operator /= ( const Size3<T> & size )
{
	width /= size.width;
	height /= size.height;
	depth /= size.depth;
	return *this;
}

template< typename T >
Size3<T> & Size3<T>::operator *= ( T val )
{
	width *= val;
	height *= val;
	depth *= val;
	return *this;
}

template< typename T >
Size3< T > & Size3< T >::operator /= ( T val )
{
	width /= val;
	height /= val;
	depth /= val;
	return *this;
}

// binarheight
template< typename T >
Size3< T > Size3< T >::operator + ( const Size3< T > & size) const
{
	return Size3< T >( width + size.width, height + size.height, depth + size.depth );
}

template< typename T >
Size3< T > Size3< T >::operator - ( const Size3< T > & size ) const
{
	return Size3< T >( width - size.width, height - size.height, depth - size.depth );
}

template< typename T >
Size3< T > Size3< T >::operator * ( const Size3< T > & size ) const
{
	return Size3< T >( width * size.width, height * size.height, depth * size.depth );
}

template< typename T >
Size3< T > Size3< T >::operator / ( const Size3< T > & size ) const
{
	return Size3< T >( width / size.width, height / size.height, depth / size.depth );
}

template< typename T >
Size3< T > Size3< T >::operator * ( T val ) const
{
	return Size3< T >( width * val, height * val, depth * val );
}

template< typename T >
Size3< T > Size3< T >::operator / ( T val ) const
{
	return Size3< T >( width / val, height / val, depth / val );
}

template< typename T >
bool Size3< T >::operator == ( const Size3< T >& size ) const
{
	return( width == size.width && height == size.height && depth == size.depth );
}

template< typename T >
bool Size3< T >::operator != ( const Size3< T >& size ) const
{
	return( width != size.width || height != size.height || depth != size.depth );
}

template< typename T >
std::string Size3< T >::ToString() const
{
	return Cast< std::string >( width ) + ", " + Cast< std::string >( height ) + ", " + Cast< std::string >( depth );
}

template< typename T >
T Size3< T >::Units() const
{
    return width * height;
}

template< typename T >
T Size3< T >::LinearIndex( T h, T v, T d ) const
{
    return h + v * width + d * width * height;
}
