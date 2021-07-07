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

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif
namespace unify
{
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
		/// Reduces the bounding box to empty/zeros.
		/// </summary>
		void Clear();

		/// <summary>
		/// Add bouding box with spatial locations (basically, just adds the corners + an offset). This allows us to be a BB of BBs.
		/// </summary>
		BBox & AddBBoxWithPosition( const BBox< T > & boundingBox, const V3< T > & position );  

		/// <summary>
		/// Ensure points are within the bounding box, else increase the bounding box to encompass them.
		/// </summary>
		void AddPoints( const unify::V3< T > * const points, size_t size );

		/// <summary>
		/// Test if a point is withing the bounding box.
		/// </summary>
		bool ContainsPoint( const V3< T > & point );
		
		/// <summary>
		/// Returns the dimensions of the bounding box.
		/// </summary>
		const Size3< T > Size() const;

		/// <summary>
        /// Tests if a ray intersects with the bounding box.
		/// </summary>
        bool Intersects( const Ray & ray, float t0, float t1 ) const;
        
		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// Sets hitPoint to the first point of collision.
		/// </summary>
        bool Intersects( const Ray & ray, V3< float > & hitPoint ) const;

		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// Sets distance to the distance from the ray to the bounding box.
		/// </summary>		
		bool Intersects( const Ray & ray, float & distance ) const;

		/// <summary>
		/// Tests if a ray intersects with the bounding box.
		/// </summary>		
		bool Intersects( const Ray & ray ) const;

		/// <summary>
		/// Takes a point and returns a new point barrycentric to the bounding box.
		/// </summary>
		V3< T > ToBarrycentric( const V3< T > & point ) const;

		/// <summary>
		/// Returns a bounding sphere that encompases the boundinh box.
		/// </summary>		
		BSphere< T > MakeBSphere() const;

	private:

		/// <summary>
		/// Ensures our sup is superior and our inf, inferior.
		/// </summary>
		void Fix();
	};

	#include <unify/BBox.inl>
}
