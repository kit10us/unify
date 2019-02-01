/* Copyright (c) 2002 - 2019, Kit10 Studios LLC
 * All Rights Reserved
 */

#pragma once

#include <unify/Unify.h>
#include <unify/V2.h>
#include <unify/V3.h>
#include <unify/V4.h>

namespace unify
{
	/// <summary>
	/// A sphere used to track a volume, typically of an object.
	/// </summary>
	template< typename T = float >
	class BSphere
	{
	public:
		// Public members to reduce possible speed issues.
		V3< T > center;
		T radius;

		BSphere();
		BSphere( V3< T > center );
		BSphere( V3< T > center, T radius );

		BSphere & operator+=( const BSphere< T > & sphere );
		BSphere & operator+=( V3< T > point );

		/// <summary>
		/// Returns the center of the bounding sphere.
		/// </summary>
		V3< T > GetCenter() const;

		/// <summary>
		/// Retruns the radius of the sphere.
		/// </summary>
		T GetRadius() const;

		/// <summary>
		/// Retruns the diameter of the sphere.
		/// </summary>
		T GetDiameter() const;

		/// <summary>
		/// Returns true if point lies within the bounding sphere.
		/// </summary>
		bool Contains( V3< T > point ) const;

		/// <summary>
		/// Returns true if a sphere overlaps/collides with another sphere.
		/// </summary>
		bool Collides( BSphere< T > sphere ) const;
	};

	#include <unify/BSphere.inl>
}


