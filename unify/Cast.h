// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

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
	template<> std::string Cast( const int in );
	template<> std::string Cast( const float in );
	template<> std::string Cast( const double in );
	template<> std::string Cast( const unsigned short in );
	template<> std::string Cast( const short in );
	template<> std::string Cast( const unsigned long in );
	template<> std::string Cast( const long in );
	template<> std::string Cast( const TimeDelta in );

	// Casts from std::string to another type.
	template<> bool Cast( const std::string text );
	template<> char Cast( const std::string text );
	template<> unsigned char Cast( const std::string text );
	template<> int Cast( const std::string text );
	template<> unsigned int Cast( const std::string text );
	template<> float Cast( const std::string text );
	template<> double Cast( const std::string text );
	template<> wchar_t * Cast( const std::string text );
	template<> short Cast( const std::string text );
	template<> unsigned short Cast( const std::string text );
	template<> std::wstring Cast( const std::string text );
	template<> const char * Cast( const std::string text );
	template<> unify::Path Cast( const std::string text );

	template<> bool Cast( const char * text );
	template<> char Cast( const char * text );
	template<> unsigned char Cast( const char * text );
	template<> int Cast( const char * text );
	template<> unsigned int Cast( const char * text );
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