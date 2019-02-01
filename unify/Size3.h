// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/V2.h>
#include <unify/V3.h>

namespace unify
{
	template < class T >
	class Size3
	{
	public:
		T width, height, depth;

		Size3();
		Size3( T width, T height, T depth );
		Size3( const Size3< T > & size );
		explicit Size3( std::string text );
				
		void Zero();

		// Conversion operators...
		Size3< T > & operator = ( const V3< T > & vec );

		// binary operators...
		Size3< T > & operator = ( const Size3< T > & size );

		Size3< T > & operator += ( const Size3< T > & size );
		Size3< T > & operator -= ( const Size3< T > & size );
		Size3< T > & operator *= ( const Size3< T > & size );
		Size3< T > & operator /= ( const Size3< T > & size );
		Size3< T > & operator *= ( T val );
		Size3< T > & operator /= ( T val );

		Size3< T > operator + ( const Size3< T > & size) const;
		Size3< T > operator - ( const Size3< T > & size ) const;
		Size3< T > operator * ( const Size3< T > & size ) const;
		Size3< T > operator / ( const Size3< T > & size ) const;
		Size3< T > operator * ( T val ) const;
		Size3< T > operator / ( T val ) const;

		bool operator == ( const Size3< T > & size ) const;
		bool operator != ( const Size3< T > & size ) const;

        template< typename T2 >
        operator Size< T2 >()
        {
            return Size< T2 >( static_cast< T2 >( width ), static_cast< T2 >( height ), static_cast< T2 >( depth ) );
        }

		std::string ToString() const;


        T Units() const;

        // Returns a linear index assuming horizontal major. 
        T LinearIndex( T h, T v, T d ) const;
    };
	#include <unify/Size3.inl>
}