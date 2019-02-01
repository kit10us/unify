// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

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
