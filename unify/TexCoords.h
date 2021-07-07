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
