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


#include <unify/TexArea.h>
#include <unify/Size.h>
#include <unify/String.h>

using namespace unify;
using namespace string;

TexArea::TexArea()
{
	// Do nothing
}

TexArea::TexArea( float ul_u, float ul_v, float dr_u, float dr_v )
: ul( ul_u, ul_v )
, dr( dr_u, dr_v )
{
}

TexArea::TexArea( const TexCoords & coordsUL, const TexCoords & coordsDR )
: ul( coordsUL )
, dr( coordsDR )
{
}

TexArea::TexArea( const std::string text )
{
    // Named
    if ( StringIs( text, "full" ) )
    {
        ul.u = 0.0f;
        ul.v = 0.0f;
        dr.u = 1.0f;
        dr.v = 1.0f;
    }
	else
	{
		std::vector< float > split = Split< float >( text, ',' );
		ul.u = split[ 0 ];
		ul.v = split[ 1 ];
		dr.u = split[ 2 ];
		dr.v = split[ 3 ];
	}
}

bool TexArea::operator==( const TexArea & area ) const
{
	return ul == area.ul && dr == area.dr;
}

bool TexArea::operator!=( const TexArea & area ) const
{
	return !(*this == area);
}

float TexArea::Width() const
{
	return dr.u - ul.u;
}

float TexArea::Height() const
{
	return dr.v - ul.v;
}

Size< float > TexArea::Size() const
{

    return unify::Size< float >( dr.u - ul.u, dr.v - ul.v );
}

TexCoords TexArea::UL() const
{
	return ul;
}

TexCoords TexArea::UR() const
{
	return TexCoords( dr.u, ul.v );
}

TexCoords TexArea::DL() const
{
	return TexCoords( ul.u, dr.v );
}

TexCoords TexArea::DR() const
{
	return dr;
}

bool TexArea::IsZero() const
{
	return Width() == Height() == 0.0f;
}

TexArea unify::TexAreaOne()
{
	return TexArea( 0, 0, 1, 1 );
}

TexArea unify::TexAreaZero()
{
	return TexArea( 0, 0, 0, 0 );
}

TexArea unify::TexAreaFull()
{
	return TexArea( 0, 0, 1, 1 );
}

TexArea unify::TexAreaDouble()
{
	return TexArea( 0, 0, 2, 2 );
}

std::string TexArea::ToString() const
{
	return "{ " + Cast< std::string >(ul.u) + ", " + Cast< std::string >(ul.v) + " }, { " + Cast< std::string >(dr.u) + ", " + Cast< std::string >(dr.v) + " }";
}
