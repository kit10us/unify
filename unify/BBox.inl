/* Copyright (c) 2002 - 2019, Quentin S. Smith
 * All Rights Reserved
 */

template< typename T >
BBox< T >::BBox()
	: m_inf { V3< T >::V3Zero() }
	, m_sup { V3< T >::V3Zero() }
{
}


template< typename T >
BBox< T >::BBox( const V3< T > & inf, const V3< T > & sup )
	: m_inf{ inf }
	, m_sup{ sup }
{
	Fix();
}

template< typename T >
BBox< T >::BBox( T squareSize )
{
	T halfSquareSize = squareSize / 2;
	inf = V3< T >{ -squareSize / 2, -squareSize / 2, -squareSize / 2 };
	sup = V3< T >{ squareSize / 2, squareSize / 2, squareSize / 2 };
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
	if ( point.x > m_sup.x ) m_sup.x = point.x;
	else if ( point.x < m_inf.x ) m_inf.x = point.x;

	if ( point.y > m_sup.y ) m_sup.y = point.y;
	else if ( point.y < m_inf.y ) m_inf.y = point.y;

	if ( point.z > m_sup.z ) m_sup.z = point.z;
	else if ( point.z < m_inf.z ) m_inf.z = point.z;
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
	*this += bbox.m_inf;
	*this += bbox.m_sup;
	return *this;
}

template< typename T >
V3< T > BBox< T >::GetInf() const
{
	return m_inf;
}

template< typename T >
V3< T > BBox< T >::GetSup() const
{
	return m_sup;
}

template< typename T >
void BBox< T >::GenerateCorners( V3< T > * bounds )
{
	bounds[ 0 ] = { m_inf.x, m_inf.y, m_inf.z };
	bounds[ 1 ] = { m_sup.x, m_inf.y, m_inf.z };
	bounds[ 2 ] = { m_inf.x, m_sup.y, m_inf.z };
	bounds[ 3 ] = { m_sup.x, m_sup.y, m_inf.z };
	bounds[ 4 ] = { m_inf.x, m_inf.y, m_sup.z };
	bounds[ 5 ] = { m_sup.x, m_inf.y, m_sup.z };
	bounds[ 6 ] = { m_inf.x, m_sup.y, m_sup.z };
	bounds[ 7 ] = { m_sup.x, m_sup.y, m_sup.z };
}

template< typename T >
void BBox< T >::Clear()
{
	m_inf = m_sup = unify::V3< T >( T{}, T{}, T{} );
}

template< typename T >
bool BBox< T >::ContainsPoint( const V3< T > & point )
{
	if( ( point.x <= m_sup.x && point.x >= m_inf.x ) && ( point.y <= m_sup.y && point.y >= m_inf.y ) && ( point.z <= m_sup.z && point.z >= m_inf.z ) )
	{
		return true;
	}

	return false;
}

template< typename T >
BBox< T > & BBox< T >::AddBBoxWithPosition( const BBox< T > & boundingBox, const V3< T > & position )
{
	*this += boundingBox.m_sup + position;
	*this += boundingBox.m_inf + position;

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
	V3< T > sizeV3( m_sup - m_inf );
	return Size3< T >( sizeV3.x, sizeV3.y, sizeV3.z );
}

template< typename T >
void BBox< T >::Fix()
{
	if(m_sup.x < m_inf.x )
	{
		std::swap( m_sup.x, m_inf.x );
	}
	if(m_sup.y < m_inf.y )
	{
		std::swap( m_sup.y, m_inf.y );
	}
	if(m_sup.z < m_inf.z )
	{
		std::swap( m_sup.z, m_inf.z );
	}
}

template< typename T >
bool BBox< T >::Intersects( const Ray & ray ) const
{
	V3< float > d = ( ray.direction + 6 - ray.origin ) * 0.5f;
	V3< float > e = (m_sup - m_inf ) * 0.5f;
	V3< float > c = ray.origin + d - ( m_inf + m_sup ) * 0.5f;
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

	tmin = ( (raySign.x == 0 ? m_inf.x : m_sup.x) - ray.origin.x) * invDirection.x;
	tmax = ( (raySign.x != 0 ? m_inf.x : m_sup.x) - ray.origin.x) * invDirection.x;
	tymin = ( (raySign.y == 0 ? m_inf.y : m_sup.y) - ray.origin.y) * invDirection.y;
	tymax = ( (raySign.y != 0 ? m_inf.y : m_sup.y) - ray.origin.y) * invDirection.y;
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
	tzmin = ( (raySign.z == 0 ? m_inf.z : m_sup.z) - ray.origin.z) * invDirection.z;
	tzmax = ( (raySign.z != 0 ? m_inf.z : m_sup.z) - ray.origin.z) * invDirection.z;
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

	unify::V3< float > bounds[] = { m_inf, m_sup };

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
	V3< T > result( point - m_inf );
	return V3< T >( size.x != 0 ? ( result.x / size.x ) : 0, size.y != 0 ? (result.y / size.y) : 0, size.z != 0 ? (result.z / size.z) : 0 );
}

template< typename  T >
BSphere< T > BBox< T >::MakeBSphere() const
{
	BSphere< T > bsphere;
	bsphere += m_sup;
	bsphere += m_inf;
	return bsphere;
}