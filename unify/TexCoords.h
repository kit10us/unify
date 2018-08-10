// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <string>

namespace unify
{
	class TexCoords
	{
	public:
		float u, v;

		TexCoords();
		TexCoords( float u, float v );
        explicit TexCoords( std::string text );

		// OPERATOR OVERLOADING MEMBER FUNCTIONS

		TexCoords & operator += ( const TexCoords & vec );
		TexCoords & operator -= ( const TexCoords & vec );
		TexCoords & operator *= ( float val );
		TexCoords & operator /= ( float val );

		// unary operators
		//TexCoords operator + () const;
		//TexCoords operator - () const;

		// binary operators
		TexCoords operator + ( const TexCoords & vec) const;
		TexCoords operator - ( const TexCoords & vec ) const;
		TexCoords operator * ( const TexCoords & vec ) const;
		TexCoords operator / ( const TexCoords & vec ) const;
		TexCoords operator * ( float val ) const;
		TexCoords operator / ( float val ) const;

		//friend V3 operator * ( float, const struct V3& );

		bool operator == ( const TexCoords & vec ) const;
		bool operator != ( const TexCoords & vec ) const;

        float & operator[]( size_t i );
        const float & operator[]( size_t i ) const;

        std::string ToString() const;
	};
}
