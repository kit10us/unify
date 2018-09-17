/* Copyright (c) 2002 - 2019, Quentin S. Smith
 * All Rights Reserved
 */

template< typename T >
BSphere< T >::BSphere()
	: center{ T(), T(), T() }
	, radius{ T() }
{
}

template< typename T >
BSphere< T >::BSphere( V3< T > center )
	: center{ center }
	, radius{ T() }
{
}

template< typename T >
BSphere< T >::BSphere( V3< T > center, T radius )
	: center{ center }
	, radius{ radius }
{
}

template< typename T >
BSphere< T > & BSphere< T >::operator+=( const BSphere< T > & sphere )
{
	// Handle empty BSpheres...
	if( sphere.GetRadius() < std::numeric_limits< T >::epsilon() )
	{
		return;
	}

	if( GetRadius() < std::numeric_limits< T >::epsilon() )
	{
		radius = sphere.GetRadius();
	}

	// Create extents and add them...

	unify::V3< T > a{ GetCenter() - sphere.GetCenter() };
	a.Normalize();
	a = GetCenter() += a * GetRadius();
	
	unify::V3< T > b{ sphere.GetCenter() - GetCenter() };
	b.Normalize();
	b = sphere.GetCenter() += b * sphere.GetRadius();

	( *this ) += b;
	( *this ) += a;


	return *this;
}

template< typename T >
BSphere< T > & BSphere< T >::operator+=( V3< T > point )
{
	T distanceFromCenter = center.DistanceTo( point );
	if( distanceFromCenter > radius )
	{
		radius = distanceFromCenter;
	}
	return *this;
}

template< typename T >
V3< T > BSphere< T >::GetCenter() const
{
	return center;
}

template< typename T >
T BSphere< T >::GetRadius() const
{
	return radius;
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
	return distanceFromCenter <= radius;
}

template< typename T >
bool BSphere< T >::Collides( BSphere< T > sphere ) const
{
	float d = GetCenter().DistanceTo( sphere.GetCenter() );
	float rt = radius + sphere.radius;
	bool collides = d < rt;
	return collides;
}
