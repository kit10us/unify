// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

template< typename T >
V2< T >::V2()
	: x{}
	, y{}
{
}

template< typename T >
V2< T >::V2( T _x, T _y )
	: x( _x )
	, y( _y )
{
}

template< typename T >
V2< T >::V2( const V2< T > & vec )
	: x( vec.x )
	, y( vec.y )
{
}

template< typename T >
V2< T >::V2( const Size< T > & size )
	: x( size.width )
	, y( size.height )
{
}

template< typename T >
V2< T >::V2( std::string text )
{
	std::vector< T > split = Split< T >( text, ',' );
    x = split[ 0 ];
    y = split[ 1 ];
}

template< typename T >
V2< T > & V2< T >::operator = ( const Size< T > & size )
{
	x = size.width;
	y = size.height;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator = ( const V3< T > & vec3 )
{
	x = vec3.x * vec3.z;
	y = vec3.y * vec3.z;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator = ( const V2< T > & vec )
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator += ( const V2< T > & vec )
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator -= ( const V2< T > & vec )
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator *= ( const V2< T > & vec )
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator /= ( const V2< T > & vec )
{
	x /= vec.x;
	y /= vec.y;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator *= ( T val )
{
	x *= val;
	y *= val;
	return *this;
}

template< typename T >
V2< T > & V2< T >::operator /= ( T val )
{
	x /= val;
	y /= val;
	return *this;
}

// binary
template< typename T >
V2< T > V2< T >::operator + ( const V2< T > & vec) const
{
	return V2< T >( x + vec.x, y + vec.y );
}

template< typename T >
V2< T > V2< T >::operator - ( const V2< T > & vec ) const
{
	return V2< T >( x - vec.x, y - vec.y );
}

template< typename T >
V2< T > V2< T >::operator * ( const V2< T > & vec ) const
{
	return V2< T >( x * vec.x, y * vec.y );
}

template< typename T >
V2< T > V2< T >::operator / ( const V2< T > & vec ) const
{
	return V2< T >( x / vec.x, y / vec.y );
}

template< typename T >
V2< T > V2< T >::operator * ( T val ) const
{
	return V2< T >( x * val, y * val );
}

template< typename T >
V2< T > V2< T >::operator / ( T val ) const
{
	return V2< T >( x / val, y / val );
}

template< typename T >
bool V2< T >::operator == ( const V2< T >& vec ) const
{
	return( x == vec.x && y == vec.y );
}

template< typename T >
bool V2< T >::operator != ( const V2& vec ) const
{
	return( x != vec.x || y != vec.y );
}

template< typename T >
T & V2< T >::operator[]( size_t i )
{
    switch( i )
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        throw unify::Exception( "Out of range!" );
    }
}

template< typename T >
const T & V2< T >::operator[]( size_t i ) const
{
    switch( i )
    {
    case 0:
        return x;
    case 1:
        return y;
    default:
        throw unify::Exception( "Out of range!" );
    }
}

template< typename T >
T V2< T >::Length() const
{
	return sqrt( (x * x) + (y * y) );
}

template< typename T >
void V2< T >::Normalize()
{
	T l = Length();
	x /= l;
	y /= l;
}

template< typename T >
V2< T > V2< T >::Absolute() const
{
	return{ abs( x ), abs( y ) };
}

template< typename T >
const T V2< T >::DistanceTo(const V2< T > & to) const
{
	V2<T> d;
	d = to - *this;
	return sqrt(( d.x * d.x ) + ( d.y * d.y ));
}

template< typename T >
T V2< T >::Dot(const V2< T > & a) const
{
	return x * a.x + y * a.y;
}

template< typename T >
Angle V2< T >::Angle(const V2< T > & a) const
{
	return AngleInRadians(acos(Dot(a) / ( Length() * a.Length() )));
}

template< typename T >
bool V2< T >::IsZero() const
{
	return ( x == 0 ) && ( y == 0 ) && ( z == 0 );
}

template< typename T >
std::string V2< T >::ToString() const
{
    return Cast< std::string >( x ) + ", " + Cast< std::string >( y );
}

// Named constructors

template< typename T >
V2< T > V2< T >::V2Zero()
{
	return V2( 0, 0 );
}	

template< typename T >
V2< T > V2< T >::V2Lerp(V2< T > first, V2< T > second, float ratio)
{
	V2< T > point(first + ( second - first ) * ratio);
	return point;
}

template< typename T >
V2< T > V2< T >::V2X(T x)
{
	return unify::V2< T >(x, 0, 0);
}

template< typename T >
V2< T > V2< T >::V2Y(T y)
{
	return unify::V2< T >(0, y, 0);
}

template< typename T >
V2< T > V2< T >::V2Normalized(const V2< T > & in)
{
	V2< T > v(in);
	v.Normalize();
	return v;
}

template< typename T >
V2< T > V2< T >::V2Inverse(const V2< T > & in)
{
	return V2< T >( -in.x, -in.y);
}

template< typename T >
T V2< T >::V2Dot(const V2< T > & l, const V2< T > &  r)
{
	return l.Dot(r);
}
