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
#include <unify/TimeDelta.h>
#include <string>
#include <typeinfo>
#include <cassert>
#include <algorithm>

namespace unify
{
	/// <summary> 
	/// Casts small types (<= 16 bytes) using register-optimized pass-by-value.
	/// </summary>
	template< typename TTo, typename TFrom > TTo Cast(const TFrom in );

	/// <summary>
	/// Polymorphic downcast. In debug builds, this will assert if the cast is invalid. In release builds, this will perform a static_cast without checking.
	/// </summary>
	template< typename Target, typename Source >
	Target polymorphic_downcast( Source source )
	{
#ifdef _DEBUG
		assert( dynamic_cast< Target >( source ) == source );
#endif
		return static_cast<Target >( source );
	}

	#include <unify/Cast.inl>
}