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
#include <unify/Path.h>
#include <unify/TimeDelta.h>
#include <string>
#include <typeinfo>
#include <cassert>

namespace unify
{
	// The default cast will throw (not a supported cast).
	template< typename TTo, typename TFrom > TTo Cast( const TFrom in );

	// Casts from one type to std::string.
	template<> std::string Cast( const std::string in );
	template<> std::string Cast( const std::wstring in );
	template<> std::string Cast( const bool in );
	template<> std::string Cast( const unsigned char in );
	template<> std::string Cast( const char in );
	template<> std::string Cast( const unsigned int in );
	template<> std::string Cast( const unsigned __int64 in );
	template<> std::string Cast( const int in );
	template<> std::string Cast( const float in );
	template<> std::string Cast( const double in );
	template<> std::string Cast( const unsigned short in );
	template<> std::string Cast( const short in );
	template<> std::string Cast( const unsigned long in );
	template<> std::string Cast( const long in );

	// Casts from std::string to another type.
	template<> bool Cast( const std::string text );
	template<> char Cast( const std::string text );
	template<> unsigned char Cast( const std::string text );
	template<> int Cast( const std::string text );
	template<> unsigned int Cast( const std::string text );
	template<> unsigned __int64 Cast( const std::string text );
	template<> float Cast( const std::string text );
	template<> double Cast( const std::string text );
	template<> wchar_t * Cast( const std::string text );
	template<> short Cast( const std::string text );
	template<> unsigned short Cast( const std::string text );
	template<> std::wstring Cast( const std::string text );
	template<> unify::Path Cast( const std::string text );

	template<> bool Cast( const char * text );
	template<> char Cast( const char * text );
	template<> unsigned char Cast( const char * text );
	template<> int Cast( const char * text );
	template<> unsigned int Cast( const char * text );
	template<> unsigned __int64 Cast( const char* text );
	template<> float Cast( const char * text );
	template<> double Cast( const char * text );
	template<> wchar_t * Cast( const char * text );
	template<> std::string Cast( const char * text );
	template<> std::string Cast( const wchar_t * text );

	template< typename Target, typename Source >
	Target polymorphic_downcast( Source source )
	{
#ifdef _DEBUG
		assert( dynamic_cast< Target >( source ) == source );
#endif
		return static_cast<Target >( source );
	}
}