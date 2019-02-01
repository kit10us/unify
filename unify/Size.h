// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <string>

namespace unify
{
	template < class T > class V2;

	template < class T >
	class Size
	{
	public:
		T width, height;

		Size();
		Size( T width, T height );
		Size( const Size< T > & size );
		explicit Size( std::string text );
				
		void Zero();

		// Conversion operators...
		Size< T > & operator = ( const V2< T > & vec );

		// binary operators...
		Size< T > & operator = ( const Size< T > & size );

		Size< T > & operator += ( const Size< T > & size );
		Size< T > & operator -= ( const Size< T > & size );
		Size< T > & operator *= ( const Size< T > & size );
		Size< T > & operator /= ( const Size< T > & size );
		Size< T > & operator *= ( T val );
		Size< T > & operator /= ( T val );

		Size< T > operator + ( const Size< T > & size) const;
		Size< T > operator - ( const Size< T > & size ) const;
		Size< T > operator * ( const Size< T > & size ) const;
		Size< T > operator / ( const Size< T > & size ) const;
		Size< T > operator * ( T val ) const;
		Size< T > operator / ( T val ) const;

		bool operator == ( const Size< T > & size ) const;
		bool operator != ( const Size< T > & size ) const;

        template< typename T2 >
        operator Size< T2 >()
        {
            return Size< T2 >( static_cast< T2 >( width ), static_cast< T2 >( height ) );
        }

		std::string ToString() const;

		T Width() const;
		T Height() const;

        T Units() const;

        // Returns a linear index assuming horizontal major. 
        T LinearIndex( T h, T v ) const;

        /// Returns an interum point based on the linear index assuming horizontal major.
        V2< T > LinearToV2( T index ) const;

		float AspectRatioHW() const;
		float AspectRatioWH() const;

		unify::V2< T > Center() const;
	};
	#include <unify/Size.inl>
}
