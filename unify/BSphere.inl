/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


template< typename T >
BSphere< T >::BSphere()
	: BSphere{ { {}, {}, {} } }
{
}

template< typename T >
BSphere< T >::BSphere( const V3< T > & center )
	: BSphere{ center, {} }
{
}

template< typename T >
BSphere< T >::BSphere( const V3< T > & center, const T & radius )
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
		return {};
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
