/* Copyright (c) 2002 - 2019, Evil Quail LLC
 * All Rights Reserved
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
