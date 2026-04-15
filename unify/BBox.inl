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

namespace unify
{
	template< typename T >
	BBox< T >::BBox()
		: BBox(V3< T >::V3Zero(), V3< T >::V3Zero())
	{
	}


	template< typename T >
	BBox< T >::BBox( const V3< T > & inf, const V3< T > & sup )
		: inf{ inf }
		, sup{ sup }
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
	bool BBox< T >::Fix()
	{
		bool fixed {};
		if(sup.x < inf.x )
		{
			fixed = true;
			std::swap( sup.x, inf.x );
		}
		if(sup.y < inf.y )
		{
			fixed = true;
			std::swap( sup.y, inf.y );
		}
		if(sup.z < inf.z )
		{
			fixed = true;
			std::swap( sup.z, inf.z );
		}
		return fixed;
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

	template< typename T >
	void BBox< T >::GenerateCorners( V3< T > * bounds )
	{
		bounds[ 0 ] = { inf.x, inf.y, inf.z };
		bounds[ 1 ] = { sup.x, inf.y, inf.z };
		bounds[ 2 ] = { inf.x, sup.y, inf.z };
		bounds[ 3 ] = { sup.x, sup.y, inf.z };
		bounds[ 4 ] = { inf.x, inf.y, sup.z };
		bounds[ 5 ] = { sup.x, inf.y, sup.z };
		bounds[ 6 ] = { inf.x, sup.y, sup.z };
		bounds[ 7 ] = { sup.x, sup.y, sup.z };
	}

	template< typename T >
	bool BBox< T >::ContainsPoint( const V3< T > point )
	{
		if( ( point.x <= sup.x && point.x >= inf.x ) && ( point.y <= sup.y && point.y >= inf.y ) && ( point.z <= sup.z && point.z >= inf.z ) )
		{
			return true;
		}

		return false;
	}

	template< typename T >
	bool BBox< T >::ContainsBBox( const BBox< T > & box )
	{
		if( ContainsPoint( box.inf ) && ContainsPoint( box.sup ) )
		{
			return true;
		}
		return false;
	}

	template< typename T >
	BBox< T > & BBox< T >::Union( const BBox< T > boundingBox, const V3< T > position )
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
		V3< T > sizeV3( sup - inf );
		return Size3< T >( sizeV3.x, sizeV3.y, sizeV3.z );
	}

	template< typename T >
	std::optional< RayHit< T > > BBox< T >::Intersects( const Ray< T > & ray ) const
	{
		T t_min = -std::numeric_limits< T >::max();
		T t_max =  std::numeric_limits< T >::max();
		int hit_axis = -1;
		T hit_side = ( T )1;

		for ( int i = 0; i < 3; ++i ) 
		{
			if ( fabsf( ray.direction[i] ) < std::numeric_limits< T >::epsilon() ) 
			{
				if ( ray.origin[i] < inf[i] || ray.origin[i] > sup[i] ) return std::nullopt;
			} 
			else 
			{
				T ood = ( T )1 / ray.direction[i];
				T t1 = ( inf[i] - ray.origin[i] ) * ood;
				T t2 = ( sup[i] - ray.origin[i] ) * ood;

				T side = ( T )-1; 
				if ( t1 > t2 ) 
				{
					std::swap( t1, t2 );
					side = ( T )1; 
				}

				if ( t1 > t_min ) 
				{
					t_min = t1;
					hit_axis = i;
					hit_side = side;
				}
				
				if ( t2 < t_max ) t_max = t2;

				if ( t_min > t_max ) return std::nullopt;
			}
		}

		if ( t_max < ( T )0 ) return std::nullopt;

		RayHit< T > hit;
		hit.distance = ( t_min < ( T )0 ) ? ( T )0 : t_min;
		hit.point = ray.origin + ( ray.direction * hit.distance );
		
		hit.normal = V3< T >( ( T )0, ( T )0, ( T )0 );
		if ( hit_axis != -1 ) 
		{
			hit.normal[hit_axis] = hit_side;
		}

		return hit;
	}
	
	template< typename T >
	std::optional< LineSegment3< T > > BBox< T >::Clip( const Ray< T > & ray ) const
	{
		T t_min = -std::numeric_limits< T >::max();
		T t_max =  std::numeric_limits< T >::max();

		for ( int i = 0; i < 3; ++i ) 
		{
			if ( fabsf( ray.direction[i] ) < std::numeric_limits< T >::epsilon() ) 
			{
				if ( ray.origin[i] < inf[i] || ray.origin[i] > sup[i] ) return std::nullopt;
			} 
			else 
			{
				T ood = ( T )1 / ray.direction[i];
				T t1 = ( inf[i] - ray.origin[i] ) * ood;
				T t2 = ( sup[i] - ray.origin[i] ) * ood;

				if ( t1 > t2 ) std::swap( t1, t2 );

				if ( t1 > t_min ) t_min = t1;
				if ( t2 < t_max ) t_max = t2;

				if ( t_min > t_max ) return std::nullopt;
			}
		}

		// If t_max is negative, the entire box is behind the ray origin.
		if ( t_max < ( T )0 ) 
		{
			return std::nullopt;
		}

		// Clamp t_min to 0 if the ray origin is inside the box.
		T start_t = ( t_min < ( T )0 ) ? ( T )0 : t_min;

		return LineSegment3< T >( 
			ray.origin + ( ray.direction * start_t ), 
			ray.origin + ( ray.direction * t_max ) 
		);
	}

	template< typename T >
	bool BBox< T >::Intersects( const Ray< T > & ray, T t0, T t1 ) const
	{
		T t_min = t0;
		T t_max = t1;

		for ( int i = 0; i < 3; ++i ) 
		{
			if ( fabsf( ray.direction[i] ) < std::numeric_limits< T >::epsilon() ) 
			{
				// Ray is parallel to slab; if origin is outside, no intersection possible
				if ( ray.origin[i] < inf[i] || ray.origin[i] > sup[i] ) return false;
			} 
			else 
			{
				T ood = ( T )1 / ray.direction[i];
				T t_near = ( inf[i] - ray.origin[i] ) * ood;
				T t_far  = ( sup[i] - ray.origin[i] ) * ood;

				if ( t_near > t_far ) std::swap( t_near, t_far );

				// Constrain the interval to the overlapping region
				if ( t_near > t_min ) t_min = t_near;
				if ( t_far  < t_max ) t_max = t_far;

				// If the interval becomes invalid, the ray misses the box
				if ( t_min > t_max ) return false;
			}
		}

		return true; 
	}

	template< typename T >
	std::optional< RayHit< T > > BBox< T >::Intersects( const LineSegment3< T > & segment ) const
	{
		V3< T > direction = segment.b - segment.a;
		T t_min = ( T )0;
		T t_max = ( T )1;
		int hit_axis = -1;
		T hit_side = ( T )1;

		for ( int i = 0; i < 3; ++i ) 
		{
			if ( fabsf( direction[i] ) < std::numeric_limits< T >::epsilon() ) 
			{
				if ( segment.a[i] < inf[i] || segment.a[i] > sup[i] ) return std::nullopt;
			} 
			else 
			{
				T ood = ( T )1 / direction[i];
				T t1 = ( inf[i] - segment.a[i] ) * ood;
				T t2 = ( sup[i] - segment.a[i] ) * ood;

				T side = ( T )-1; 
				if ( t1 > t2 ) 
				{
					std::swap( t1, t2 );
					side = ( T )1; 
				}

				if ( t1 > t_min ) 
				{
					t_min = t1;
					hit_axis = i;
					hit_side = side;
				}
				
				if ( t2 < t_max ) t_max = t2;

				if ( t_min > t_max ) return std::nullopt;
			}
		}

		RayHit< T > hit;
		hit.distance = t_min; // This is a normalized distance [0, 1]
		hit.point = segment.a + ( direction * t_min );
		
		hit.normal = V3< T >( ( T )0, ( T )0, ( T )0 );
		if ( hit_axis != -1 ) 
		{
			hit.normal[hit_axis] = hit_side;
		}

		return hit;
	}	

	template< typename T >
	V3< T > BBox< T >::ToRelative( const V3< T > point ) const
	{
		V3< T > size = sup - inf;
		
		// Safety check for zero-volume boxes to avoid division by zero
		return V3< T >(
			( size[0] > std::numeric_limits< T >::epsilon() ) ? ( point[0] - inf[0] ) / size[0] : ( T )0,
			( size[1] > std::numeric_limits< T >::epsilon() ) ? ( point[1] - inf[1] ) / size[1] : ( T )0,
			( size[2] > std::numeric_limits< T >::epsilon() ) ? ( point[2] - inf[2] ) / size[2] : ( T )0
		);
	}

	template< typename T >
	BSphere< T > BBox< T >::MakeBSphere() const
	{
		// The center of the sphere is the center of the box
		V3< T > center = ( inf + sup ) * ( T )0.5;
		
		// The radius is the distance from the center to one of the corners (like sup)
		T radius = ( sup - center ).Length();

		return BSphere< T >( center, radius );
	}
}