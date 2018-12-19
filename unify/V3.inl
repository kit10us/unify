// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

template< typename T >
V3< T >::V3()
{
	// DO NOTHING
}

template< typename T >
V3< T >::V3( T _xyz )
	: x( _xyz )
	, y( _xyz )
	, z( _xyz )
{
}

template< typename T >
V3< T >::V3( T _x, T _y, T _z ) 
: x( _x )
, y( _y )
, z( _z )
{
}

template< typename T >
V3< T >::V3( const V3< T > & vec )
: x( vec.x )
, y( vec.y )
, z( vec.z )
{
}

template< typename T >
V3< T >::V3( const T arr[ 3 ] )
: x( arr[ 0 ] )
, y( arr[ 1 ] )
, z( arr[ 2 ] )
{
}

template< typename T >
V3< T >::V3( const V2< T > & v2, float z )
: x( v2.x )
, y( v2.y )
, z( z )
{
}

template< typename T >
V3< T >::V3( std::string text )
{
	std::vector< T > split = string::Split< T >( text, ',' );
    x = split[ 0 ];
    y = split[ 1 ];
    z = split[ 2 ];
}

template< typename T >
V3< T > & V3< T >::operator += ( const V3< T > & vec )
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
	return *this;
}

template< typename T >
V3< T > & V3< T >::operator -= ( const V3< T > & vec )
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
	return *this;
}

template< typename T >
V3< T > & V3< T >::operator *= ( const V3< T > & vec )
{
	x *= vec.x;
	y *= vec.y;
	z *= vec.z;
	return *this;
}

template< typename T >
V3< T > & V3< T >::operator /= ( const V3< T > & vec )
{
	x /= vec.x;
	y /= vec.y;
	z /= vec.z;
	return *this;
}

template< typename T >
V3< T > & V3< T >::operator *= ( T val )
{
	x *= val;
	y *= val;
	z *= val;
	return *this;
}

template< typename T >
V3< T > & V3< T >::operator /= ( T val )
{
	x /= val;
	y /= val;
	z /= val;
	return *this;
}

// binary
template< typename T >
V3< T > V3< T >::operator + ( const V3< T > & vec) const
{
	return V3< T >( x + vec.x, y + vec.y, z + vec.z );
}

template< typename T >
V3< T > V3< T >::operator - ( const V3< T > & vec ) const
{
	return V3< T >( x - vec.x, y - vec.y, z - vec.z );
}

template< typename T >
V3< T > V3< T >::operator * ( const V3< T > & vec ) const
{
	return V3< T >( x * vec.x, y * vec.y, z * vec.z );
}

template< typename T >
V3< T > V3< T >::operator / ( const V3< T > & vec ) const
{
	return V3< T >( x / vec.x, y / vec.y, z / vec.z );
}

template< typename T >
V3< T > V3< T >::operator * ( T val ) const
{
	return V3< T >( x * val, y * val, z * val );
}

template< typename T >
V3< T > V3< T >::operator / ( T val ) const
{
	return V3< T >( x / val, y / val, z / val );
}

template< typename T >
const V3< T > & V3< T >::operator = ( const V3< T > & vec )
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
	return *this;
}

template< typename T >
bool V3< T >::operator == ( const V3< T > & vec ) const
{
	return( x == vec.x && y == vec.y && z == vec.z );
}

template< typename T >
bool V3< T >::operator != ( const V3< T > & vec ) const
{
	return( x != vec.x || y != vec.y || z != vec.z );
}

template< typename T >
bool V3< T >::operator <= ( const V3< T > & vec ) const
{
	return( x <= vec.x && y <= vec.y && z <= vec.z );
}

template< typename T >
bool V3< T >::operator < ( const V3< T > & vec ) const
{
	return( x < vec.x && y < vec.y && z < vec.z );
}

template< typename T >
bool V3< T >::operator >= ( const V3< T > & vec ) const
{
	return( x >= vec.x && y >= vec.y && z >= vec.z );
}

template< typename T >
bool V3< T >::operator > ( const V3< T > & vec ) const
{
	return( x > vec.x && y > vec.y && z > vec.z );
}


template< typename T >
T & V3< T >::operator[]( size_t i )
{
    switch( i )
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        throw unify::Exception( "Out of range!" );
    }
}

template< typename T >
const T & V3< T >::operator[]( size_t i ) const
{
    switch( i )
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    default:
        throw unify::Exception( "Out of range!" );
    }
}

template< typename T >
T V3< T >::Length() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

template< typename T >
T V3< T >::Normalize()
{
	T length = Length();
	x /= length;
	y /= length;
	z /= length;
	return length;
}

template< typename T >
T V3< T >::Normalize( const V3< T > & norm )
{
	*this = norm;
	return Normalize();
}

template< typename T >
V3< T > V3< T >::Absolute() const
{
	return{ abs( x ), abs( y ), abs( z ) };
}

template< typename T >
const T V3< T >::DistanceTo( const V3< T > & to ) const
{
	V3<T> d;
	d = to - *this;
	return sqrt( ( d.x * d.x ) + ( d.y * d.y ) + ( d.z * d.z ) );
}

template< typename T >
T V3< T >::Dot( const V3< T > & a ) const
{
	return x * a.x + y * a.y + z * a.z;
}

template< typename T >
Angle V3< T >::DotAngle( const V3< T > & a ) const
{
	return AngleInRadians( acos(Dot( a ) / (Length() * a.Length())) );
}

template< typename T >
std::string V3< T >::ToString() const
{
	return Cast< std::string >(x) + ", " + Cast< std::string >(y) + ", " + Cast< std::string >(z);
}

template< typename T >
bool V3< T >::IsZero() const
{
	return ( x == 0 ) && ( y == 0 ) && ( z == 0 );
}

template< typename T >
V3< T > V3< T >::xyz() const
{
	return V3< T >( x, y, z );
}

template< typename T >
V3< T > V3< T >::xzy() const
{
	return V3< T >( x, z, y );
}

template< typename T >
V3< T > V3< T >::yzx() const
{
	return V3< T >( y, z, x );
}

template< typename T >
V3< T > V3< T >::yxz() const
{
	return V3< T >( y, x, z );
}

template< typename T >
V3< T > V3< T >::zyx() const
{
	return V3< T >( z, y, x );
}

template< typename T >
V3< T > V3< T >::zxy() const
{
	return V3< T >( z, x, y );
}

template< typename T >
V3< T > V3< T >::V3Zero()
{
	return V3< T >( 0, 0, 0 );
}

template< typename T >
V3< T > V3< T >::V3Lerp( V3< T > first, V3< T > second, float ratio )
{
    V3< T > point( first + (second - first) * ratio );
    return point;
}

template< typename T >
V3< T > V3< T >::V3Cross( const V3< T > & a, const V3< T > & b )
{
    V3< T > point( a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,a.x * b.y - a.y * b.x );
    return point;
}

template< typename T >
V3< T > V3< T >::V3X( T x )
{
    return unify::V3< T >( x, 0, 0 );
}

template< typename T >
V3< T > V3< T >::V3Y( T y )
{
    return unify::V3< T >( 0, y, 0 );
}

template< typename T >
V3< T > V3< T >::V3Z( T z )
{
    return unify::V3< T >( 0, 0, z );
}

template< typename T >
V3< T > V3< T >::V3Normalized( const V3< T > & in )
{
	V3< T > v( in );
	v.Normalize();
	return v;
}

template< typename T >
V3< T > V3< T >::V3Inverse( const V3< T > & in )
{
	return V3< T >( -in.x, -in.y, -in.z );
}

template< typename T >
V3< T > V3< T >::V3RotateAbout(V3< T > position, float distance, unify::Angle rotation, V3< T > pivot )
{
	float rx = rotation.ToRadians() * pivot.x;
	float ry = rotation.ToRadians() * pivot.y;
	float rz = rotation.ToRadians() * pivot.z;

	float rotationMatrix[9] = 
	{ 
		 cos( ry ) *  cos( rz ), -cos( rx ) *  sin( rz ) +  sin( rx ) *  sin( ry ) *  cos( rz ),   sin( rx ) *  sin( rx ) +  cos( rz ) *  sin( ry ) * sin( rz ),
		 cos( ry ) *  sin( rz ),  cos( rx ) *  cos( rz ) +  sin( rx ) *  sin( ry ) *  sin( rz ),  -sin( rx ) *  cos( rz ) +  cos( rz ) +  sin( rx ) * sin( ry ), 
		-sin( ry ),               sin( rx ) *  cos( ry ),                                           cos( rx ) *  cos( ry ) 
	};

	auto finalPosition = position + pivot * distance;
	return finalPosition;
}

