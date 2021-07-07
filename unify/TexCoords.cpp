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


#include <unify/TexCoords.h>
#include <unify/String.h>
#include <unify/Cast.h>
#include <unify/Exception.h>

using namespace unify;
using namespace string;

TexCoords::TexCoords()
{
}

TexCoords::TexCoords( float u, float v )
: u( u )
, v( v )
{
}

TexCoords::TexCoords( std::string text )
{
	std::vector< float > split = Split< float >( text, ',' );
    u = split[ 0 ];
    v = split[ 1 ];
}

TexCoords & TexCoords::operator += ( const TexCoords& coords )
{
	u += coords.u;
	v += coords.v;
	return *this;
}

TexCoords & TexCoords::operator -= ( const  TexCoords& coords )
{
	u -= coords.u;
	v -= coords.v;
	return *this;
}

TexCoords & TexCoords::operator *= ( float val )
{
	u *= val;
	v *= val;
	return *this;
}

TexCoords & TexCoords::operator /= ( float val )
{
	u /= val;
	v /= val;
	return *this;
}

TexCoords TexCoords::operator + ( const TexCoords & coords) const
{
	return TexCoords( u + coords.u, v + coords.v );
}

TexCoords TexCoords::operator - ( const TexCoords & coords ) const
{
	return TexCoords( u - coords.u, v - coords.v );
}

TexCoords TexCoords::operator * ( const TexCoords & coords ) const
{
	return TexCoords( u * coords.u, v * coords.v );
}

TexCoords TexCoords::operator / ( const TexCoords & coords ) const
{
	return TexCoords( u / coords.u, v / coords.v );
}

TexCoords TexCoords::operator * ( float val ) const
{
	return TexCoords( u * val, v * val );
}

TexCoords TexCoords::operator / ( float val ) const
{
	return TexCoords( u / val, v / val );
}

bool TexCoords::operator == ( const TexCoords& coords ) const
{
	return( u == coords.u && v == coords.v );
}

bool TexCoords::operator != ( const TexCoords& coords ) const
{
	return( u != coords.u || v != coords.v );
}

float & TexCoords::operator[]( size_t i )
{
    switch( i )
    {
    case 0:
        return u;
    case 1:
        return v;
    default:
        throw unify::Exception( "Out of range!" );
    }
}

const float & TexCoords::operator[]( size_t i ) const
{
    switch( i )
    {
    case 0:
        return u;
    case 1:
        return v;
    default:
        throw unify::Exception( "Out of range!" );
    }
}

std::string TexCoords::ToString() const
{
    return Cast< std::string >( u ) + ", " + Cast< std::string >( v );
}
