// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/V3.h>
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
		V3< T > sup;
		V3< T > inf;

		BBox();
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

		void GenerateCorners( V3< T > * bounds );
		void Clear();

		/// <summary>
		/// Add bouding box with spatial locations (basically, just adds the corners + an offset). This allows us to be a BB of BBs.
		/// </summary>
		BBox & AddBBoxWithPosition( const BBox< T > & boundingBox, const V3< T > & position );  

		void AddPoints( const unify::V3< T > * const points, size_t size );

		bool ContainsPoint( const V3< T > & point );
		const V3< T > Size() const;

        // Perform a hit test, return true if hit...
        bool Intersects( const Ray & ray, float t0, float t1 ) const;
        
		// ... this version sets hitPoint to the first point of collision.
        bool Intersects( const Ray & ray, V3< float > & hitPoint ) const;

		bool Intersects( const Ray & ray, float & distance ) const;

		bool Intersects( const Ray & ray ) const;

		/// <description>
		/// Takes a point and returns a new point barrycentric to the bounding box.
		/// </description>
		V3< T > ToBarrycentric( const V3< T > & point ) const;

		BSphere< T > MakeBSphere() const;

	private:
		void Fix(); // Ensures our sup is superior and our inf, inferior.
	};
	#include <unify/BBox.inl>
}
