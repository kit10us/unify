/* Copyright (c) 2002 - 2019, Quentin S. Smith
 * All Rights Reserved
 */

template< typename T >
BBox< T >::BBox()
	: inf { V3< T >::V3Zero() }
	, sup { V3< T >::V3Zero() }
{
}

template< typename T >
BBox< T >::BBox( T squareSize )
{
	T halfSquareSize = squareSize / 2;
	inf = V3< T >{ -squareSize / 2, -squareSize / 2, -squareSize / 2 };
	sup = V3< T >{ squareSize / 2, squareSize / 2, squareSize / 2 };
}

template< typename T >
BBox< T >::BBox( const V3< T > & inInf, const V3< T > & inSup )
	: BBox()
{
	*this += inInf;
	*this += inSup;
}

template< typename T >
BBox< T > BBox< T >::operator * ( const V3< T > & multiplicand ) const
{
	return BBox< T >( inf * multiplicand, sup * multiplicand );
}

template< typename T >
BBox< T > & BBox< T >::operator *= ( const V3< T > & multiplicand )
{
	inf *= multiplicand;
	sup *= multiplicand;
	return *this;
}

template< typename T >
BBox< T > BBox< T >::operator * ( T multiplicand ) const
{
	BBox< T > bbox( *this );
	bbox *= multiplicand;
	return bbox;
}

template< typename T >
BBox< T > & BBox< T >::operator *= ( T multiplicand )
{
	return *this *= unify::V3< T >( multiplicand, multiplicand, multiplicand );
}																			   

template< typename T >
BBox< T > BBox< T >::operator + ( const V3< T > & point ) const
{
	BBox< T > bbox( *this );
	bbox += point;
	return bbox;
}

template< typename T >
BBox< T > & BBox< T >::operator += ( const V3< T > & point )
{
	if ( point.x > sup.x ) sup.x = point.x;
	else if ( point.x < inf.x ) inf.x = point.x;

	if ( point.y > sup.y ) sup.y = point.y;
	else if ( point.y < inf.y ) inf.y = point.y;

	if ( point.z > sup.z ) sup.z = point.z;
	else if ( point.z < inf.z ) inf.z = point.z;
	return *this;
}

template< typename T >
BBox< T > BBox< T >::operator + ( const BBox< T > & bbox ) const
{		 
	BBox< T > result( *this );
	result += bbox;
	return result;
}

template< typename T >
BBox< T > & BBox< T >::operator += ( const BBox< T > & bbox )
{
	*this += bbox.inf;
	*this += bbox.sup;
	return *this;
}

// Generate the 8 vertices that make up the bounding box...
template< typename T >
void BBox< T >::GenerateCorners( V3< T > * bounds )
{
	bounds[ 0 ] = V3< T >( inf.x, inf.y, inf.z );
	bounds[ 1 ] = V3< T >( sup.x, inf.y, inf.z );
	bounds[ 2 ] = V3< T >( inf.x, sup.y, inf.z );
	bounds[ 3 ] = V3< T >( sup.x, sup.y, inf.z );
	bounds[ 4 ] = V3< T >( inf.x, inf.y, sup.z );
	bounds[ 5 ] = V3< T >( sup.x, inf.y, sup.z );
	bounds[ 6 ] = V3< T >( inf.x, sup.y, sup.z );
	bounds[ 7 ] = V3< T >( sup.x, sup.y, sup.z );
}

template< typename T >
void BBox< T >::Clear()
{
	inf = sup = unify::V3< T >( T{}, T{}, T{} );
}

template< typename T >
bool BBox< T >::ContainsPoint( const V3< T > & point )
{
	if( ( point.x <= sup.x && point.x >= inf.x ) && ( point.y <= sup.y && point.y >= inf.y ) && ( point.z <= sup.z && point.z >= inf.z ) )
	{
		return true;
	}

	return false;
}

template< typename T >
BBox< T > & BBox< T >::AddBBoxWithPosition( const BBox< T > & boundingBox, const V3< T > & position )
{
	*this += boundingBox.sup + position;
	*this += boundingBox.inf + position;

	return *this;
}

template< typename T >
void BBox< T >::AddPoints( const unify::V3< T > * const points, size_t size )
{
	for( size_t i = 0; i < size; i++ )
	{
		auto & coord = points[i];
		( *this ) += coord;
	}
}

template< typename T >
const Size3< T > BBox< T >::Size() const
{
	return V3< T >( sup - inf );
}

template< typename T >
void BBox< T >::Fix()
{
	if( sup.x < inf.x )
	{
		std::swap( sup.x, inf.x );
	}
	if( sup.y < inf.y )
	{
		std::swap( sup.y, inf.y );
	}
	if( sup.z < inf.z )
	{
		std::swap( sup.z, inf.z );
	}
}

template< typename T >
bool BBox< T >::Intersects( const Ray & ray ) const
{
	V3< float > d = ( ray.direction + 6 - ray.origin ) * 0.5f;
	V3< float > e = ( sup - inf ) * 0.5f;
	V3< float > c = ray.origin + d - ( inf + sup ) * 0.5f;
	V3< float > ad = d.Absolute();

	const float EPSILON = std::numeric_limits< float >::epsilon();

	if( fabsf( c[0] ) > e[0] + ad[0] ) return false;
	if( fabsf( c[1] ) > e[1] + ad[1] ) return false;
	if( fabsf( c[2] ) > e[2] + ad[2] ) return false;

	if( fabsf( d[1] * c[2] - d[2] * c[1] ) > e[1] * ad[2] + e[2] * ad[1] + EPSILON ) return false;
	if( fabsf( d[2] * c[0] - d[0] * c[2] ) > e[2] * ad[0] + e[0] * ad[2] + EPSILON ) return false;
	if( fabsf( d[0] * c[1] - d[1] * c[0] ) > e[0] * ad[1] + e[1] * ad[0] + EPSILON ) return false;

	return true;
}

template< typename T >
bool BBox< T >::Intersects( const Ray & ray, float distanceBegin, float distanceEnd ) const
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	V3< float > invDirection = ray.InvDirection();
	V3< int > raySign = ray.Sign();

	tmin = ( (raySign.x == 0 ? inf.x : sup.x) - ray.origin.x) * invDirection.x;
	tmax = ( (raySign.x != 0 ? inf.x : sup.x) - ray.origin.x) * invDirection.x;
	tymin = ( (raySign.y == 0 ? inf.y : sup.y) - ray.origin.y) * invDirection.y;
	tymax = ( (raySign.y != 0 ? inf.y : sup.y) - ray.origin.y) * invDirection.y;
	if( (tmin > tymax) || (tymin > tmax) )
	{
		return false;
	}
	if( tymin > tmin )
	{
		tmin = tymin;
	}
	if( tymax < tmax )
	{
		tmax = tymax;
	}
	tzmin = ( (raySign.z == 0 ? inf.z : sup.z) - ray.origin.z) * invDirection.z;
	tzmax = ( (raySign.z != 0 ? inf.z : sup.z) - ray.origin.z) * invDirection.z;
	if( (tmin > tzmax) || (tzmin > tmax) )
	{
		return false;
	}
	if( tzmin > tmin )
	{
		tmin = tzmin;
	}
	if( tzmax < tmax )
	{
		tmax = tzmax;
	}
	return ((tmin < distanceEnd ) && (tmax > distanceBegin ));
}

template< typename T >
bool BBox< T >::Intersects( const Ray & ray, float & distance ) const
{
	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	auto orig = ray.origin;
	auto sign = ray.Sign();
	auto invdir = ray.InvDirection();

	unify::V3< float > bounds[] = { inf, sup };

	tmin = ( bounds[sign.x].x - orig.x ) * invdir.x;
	tmax = ( bounds[1 - sign.x].x - orig.x ) * invdir.x;
	tymin = ( bounds[sign.y].y - orig.y ) * invdir.y;
	tymax = ( bounds[1 - sign.y].y - orig.y ) * invdir.y;

	if( ( tmin > tymax ) || ( tymin > tmax ) )
	{
		return false;
	}

	if( tymin > tmin )
	{
		tmin = tymin;
	}
	if( tymax < tmax )
	{
		tmax = tymax;
	}

	tzmin = ( bounds[sign.z].z - orig.z ) * invdir.z;
	tzmax = ( bounds[1 - sign.y].z - orig.z ) * invdir.z;

	if( ( tmin > tzmax ) || ( tzmin > tmax ) )
	{
		return false;
	}

	if( tzmin > tmin )
	{
		tmin = tzmin;
	}
	if( tzmax < tmax )
	{
		tmax = tzmax;
	}

	float t = tmin;

	if( t < 0 ) 
	{
		t = tmax;
		if( t < 0 )
		{
			return false;
		}
	}

	return true;
}

template< typename T >
bool BBox< T >::Intersects( const Ray & ray, V3< float > & hitPoint ) const
{
	assert( 0 );
	// TODO:
    return false;
}

template< typename T >
V3< T > BBox< T >::ToBarrycentric( const V3< T > & point ) const
{
	V3< T > size = Size();
	V3< T > result( point - inf );
	return V3< T >( size.x != 0 ? ( result.x / size.x ) : 0, size.y != 0 ? (result.y / size.y) : 0, size.z != 0 ? (result.z / size.z) : 0 );
}

template< typename  T >
BSphere< T > BBox< T >::MakeBSphere() const
{
	BSphere< T > bsphere;
	bsphere += sup;
	bsphere += inf;
	return bsphere;
}