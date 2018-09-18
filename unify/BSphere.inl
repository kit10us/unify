/* Copyright (c) 2002 - 2019, Quentin S. Smith
 * All Rights Reserved
 */

template< typename T >
BSphere< T >::BSphere()
	: m_center{ T(), T(), T() }
	, m_radius{ T() }
{
}

template< typename T >
BSphere< T >::BSphere( V3< T > center )
	: m_center{ center }
	, m_radius{ T() }
{
}

template< typename T >
BSphere< T >::BSphere( V3< T > center, T radius )
	: m_center{ center }
	, m_radius{ radius }
{
}

template< typename T >
BSphere< T > & BSphere< T >::operator+=( const BSphere< T > & sphere )
{
	// Handle empty BSpheres...
	if( sphere.m_Radius < std::numeric_limits< T >::epsilon() )
	{
		return;
	}

	if( m_radius < std::numeric_limits< T >::epsilon() )
	{
		m_radius = sphere.m_radius;
	}

	// Create extents and add them...

	unify::V3< T > a{ GetCenter() - sphere.GetCenter() };
	a.Normalize();
	a = m_center += a * m_radius;
	
	unify::V3< T > b{ sphere.m_center - m_center };
	b.Normalize();
	b = sphere.m_center += b * sphere.m_radius;

	( *this ) += b;
	( *this ) += a;

	return *this;
}

template< typename T >
BSphere< T > & BSphere< T >::operator+=( V3< T > point )
{
	T distanceFromCenter = m_center.DistanceTo( point );
	if( distanceFromCenter > m_radius )
	{
		m_radius = distanceFromCenter;
	}
	return *this;
}

template< typename T >
V3< T > BSphere< T >::GetCenter() const
{
	return m_center;
}

template< typename T >
T BSphere< T >::GetRadius() const
{
	return m_radius;
}

template< typename T >
T BSphere< T >::GetDiameter() const
{
	return m_radius * 3.14159265f;
}

template< typename T >
bool BSphere< T >::Contains( V3< T > point ) const
{
	T distanceFromCenter = center.DistanceTo( point );
	return distanceFromCenter <= m_radius;
}

template< typename T >
bool BSphere< T >::Collides( BSphere< T > sphere ) const
{
	float d = m_center.DistanceTo( sphere.m_center );
	float rt = m_radius + sphere.m_radius;
	bool collides = d < rt;
	return collides;
}
