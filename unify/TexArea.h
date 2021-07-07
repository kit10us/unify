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
#include <unify/Size.h>
#include <unify/TexCoords.h>

namespace unify
{
	class TexArea
	{
	public:
		TexCoords ul;
		TexCoords dr;

		TexArea();
		TexArea( float ul_u, float ul_v, float dr_u, float dr_v );
		TexArea( const TexCoords&, const TexCoords& );
        explicit TexArea( const std::string text );

		bool operator==( const TexArea & area ) const;
		bool operator!=( const TexArea & area ) const;

		float Width() const;
		float Height() const;

		unify::Size< float > Size() const;

		TexCoords UL() const;
		TexCoords UR() const;
		TexCoords DL() const;
		TexCoords DR() const;

		bool IsZero() const;

		std::string ToString() const;
	};

	TexArea TexAreaOne();
	TexArea TexAreaZero();
	TexArea TexAreaFull();
	TexArea TexAreaDouble();
}
