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
	if( sphere.radius < std::numeric_limits< T >::epsilon() )
	{
		return;
	}

	if( radius < std::numeric_limits< T >::epsilon() )
	{
		radius = sphere.radius;
	}

	// Create extents and add them...

	unify::V3< T > a{ GetCenter() - sphere.GetCenter() };
	a.Normalize();
	a = center += a * radius;
	
	unify::V3< T > b{ sphere.center - center };
	b.Normalize();
	b = sphere.center += b * sphere.radius;

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
	return radius * 3.14159265f;
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
	float d = center.DistanceTo( sphere.center );
	float rt = radius + sphere.radius;
	bool collides = d < rt;
	return collides;
}
