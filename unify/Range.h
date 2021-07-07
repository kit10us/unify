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
#include <unify/String.h>
#include <algorithm>
#include <cassert>

namespace unify
{
	template< typename T >
	class Range
	{
	public:
		Range();
		Range( T min, T max );
		Range( const Range & range );
		explicit Range( std::string text );

		void Clear();
		void Add( T value );
		bool IsSet() const;
		T Min() const;
		T Max() const;

		/// <summary>
		/// Test if a value is within the min and max range.
		/// </summary>
		bool IsWithin( const T & value ) const;

		Range & operator=( const Range & range );
		bool operator==( const Range & range ) const;
		bool operator!=( const Range & range ) const;

		void operator+=( const T value );

	private:
		bool m_isSet;
		T m_min, m_max;
	};
	#include <unify/Range.inl>
}
