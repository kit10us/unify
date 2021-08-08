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
#include <unify/KeyValuePair.h>
#include <unify/String.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

namespace unify
{
	/// <summary>
	/// A mapping between values and pairs with the addition of constant time value lookups by performing searches early on.
	/// Perfers constant operations over log operations, speeding up some common operations.
	/// </summary>
	template< typename Key, typename Value >
	class Lookup
	{
		friend class iterator;

		std::vector< KeyValuePair< Key, Value > > m_values;
		std::map< Key, size_t> m_keyToIndex;
	public:

		/// <summary>
		/// Add a value.
		/// </summary>
		size_t Add( Key key, Value value );

		/// <summary>
		/// Returns the number of values.
		/// </summary>
		size_t Count() const;

		/// <summary>
		/// Returns true if the value exists.
		/// Test for existance first using Exists to prevent exception.
		/// </summary>
		bool Exists( Key key ) const;

		/// <summary>
		/// Finds the index of a value by it's key. 
		/// Throws std::out_of_bounds if not found.
		/// </summary>
		size_t Find( Key key ) const;

		/// <summary>
		/// Returns the name of a value by it's index.
		/// Throws std::out_of_bounds if not found.
		/// </summary>
		Key GetName( size_t index ) const;

		/// <summary>
		/// Returns a value by it's index.
		/// Throws std::out_of_bounds if not found.
		/// </summary>
		Value GetValue( size_t index ) const;

		/// <summary>
		/// Returns a value by it's key.
		/// Throws std::out_of_bounds if not found.
		/// </summary>
		Value GetValue( Key key ) const;

		/// <summary>
		/// Sets a value by it's index.
		/// Throws std::out_of_bounds if not found.
		/// </summary>
		void SetValue( size_t index, Value value );

		/// <summary>
		/// Set a vakue by it's key. Returns false if not able to.
		/// Throws std::out_of_bounds if not found.
		/// </summary>
		void SetValue( Key key, Value value );

		/// <summary>
		/// Remove all values.
		/// </summary>
		void Clear();

		class iterator
		{
			Lookup< Key, Value > * m_lookup;
			size_t m_index;
		public:
			iterator( Lookup< Key, Value > * lookup, size_t index );

			auto operator++();

			auto operator++( int );
			
			auto operator--();

			auto operator--( int );

			bool operator==( const iterator & itr ) const;

			bool operator!=( const iterator & itr ) const;

			KeyValuePair< Key, Value > & operator*();

			const KeyValuePair< Key, Value > & operator*() const;

			KeyValuePair< Key, Value > * operator->();

			const KeyValuePair< Key, Value > * operator->() const;
		};

		iterator begin();
		
		iterator end();
	};

	#include <unify/Lookup.inl>
}