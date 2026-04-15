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


#pragma once

#include <unify/Unify.h>
#include <unify/V3.h>
#include <unify/Size3.h>
#include <unify/Ray.h>
#include <unify/BSphere.h>
#include <unify/LineSegment3.h>

#include <optional>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
namespace unify
{
	/// <summary>
	/// A ray hit result.
	/// </summary>
	template< typename T >
	struct RayHit
	{
		V3< T > point;
		V3< T > normal;
		float distance;
	};

	/// <summary>
	/// A Bounding box.
	/// </summary>
	template< typename T = float >
	class BBox
	{
	public:
		// Public members to reduce possible speed issues.
		V3< T > sup;
		V3< T > inf;

		/// <summary>
		/// construct an empty bounding box.
		/// </summary>
		BBox();

		/// <summary>
		/// Create a bouning box where inf is the inferior value (smallest), and sup is the superior value (largest). 
		/// </summary>
		BBox( const V3< T > & inf, const V3< T > & sup );
		
		/// <summary>
		/// Creates a cube BBox with a size totalling squareSize: -squareSize/2 to squareSize/2.
		/// </summary>
		BBox( T squareSize );

		/// <summary>
		/// Ensures our sup is superior and our inf, inferior.
		/// </summary>
		bool Fix();		

		BBox< T > operator * ( const V3< T > & multiplicand ) const;
		BBox< T > & operator *= ( const V3< T > & multiplicand );

		BBox< T > operator * ( T multiplicand ) const;
		BBox< T > & operator *= ( T multiplicand );

		BBox< T > operator + ( const V3< T > & point ) const;
		BBox< T > & operator += ( const V3< T > & point );

		BBox< T > operator + ( const BBox< T > & bbox ) const;
		BBox< T > & operator += ( const BBox< T > & bbox );

		/// <summary>
		/// Populates an array of vectors the vertices of the bounding box's corners.
		/// </summary>
		void GenerateCorners( V3< T > * bounds );

		/// <summary>
		/// This function performs a Minkowski Sum of the current bounding box and a second, translated bounding box.
		/// Purpose: Add bouding box with spatial locations (basically, just adds the corners + an offset). 
		///          This allows us to be a BB of BBs.
		/// </summary>
		BBox & Union( const BBox< T > boundingBox, const V3< T > position );  

		/// <summary>
		/// Ensure points are within the bounding box, else increase the bounding box to encompass them.
		/// </summary>
		void AddPoints( const unify::V3< T > * const points, size_t size );

		/// <summary>
		/// Test if a point is withing the bounding box.
		/// </summary>
		bool ContainsPoint( const V3< T > point );

		/// <summary>
		/// Test if a bounding box is withing the bounding box.
		/// </summary>
		bool ContainsBBox( const BBox< T > & box );
		
		/// <summary>
		/// Returns the dimensions of the bounding box.
		/// </summary>
		const Size3< T > Size() const;

		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// Sets distance to the distance from the ray to the bounding box.
		/// </summary>
		std::optional< RayHit< T > > Intersects( const Ray< T > & ray ) const;

		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// Returns the line segment of the ray that is within the bounding box.
		/// </summary>
		std::optional< LineSegment3< T > > Clip( const Ray< T > & ray ) const;

		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// </summary>
		/// <note>
		/// This is a faster version of Intersects() that only returns true or false, and does not calculate the hit point or distance.
		/// </note>
		bool Intersects( const Ray< T > & ray, T t0, T t1 ) const;

		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// Sets hitPoint to the first point of collision.
		/// </summary>
		std::optional< RayHit< T > > Intersects( const LineSegment3< T > & segment ) const;

		/// <summary>
		/// Takes a point and returns a new point relative to the bounding box's inf corner.
		/// </summary>
		V3< T > ToRelative( const V3< T > point ) const;

		/// <summary>
		/// Returns a bounding sphere that encompases the boundinh box.
		/// </summary>		
		BSphere< T > MakeBSphere() const;
	};
}

#include <unify/BBox.inl>