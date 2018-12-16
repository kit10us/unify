// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <conio.h>

namespace unify
{

	/// <summary>
	/// A mapping between values and pairs with the addition of constant time value lookups by performing searches early one.
	/// Perfers constant operations over log operations, speeding up some common operations.
	/// </summary>
	template< typename Key, typename Value >
	class FastMap
	{
		std::vector< Value > m_values;
		std::vector< Key > m_keys;
		std::map< Key, size_t > m_keyToIndex;
	public:

		/// <summary>
		/// Add a value.
		/// </summary>
		size_t Add( Key key, Value value = Value{} );

		/// <summary>
		/// Returns the number of values.
		/// </summary>
		size_t Count() const;

		/// <summary>
		/// Returns true if the value exists.
		/// Test for existance first using Exists to prevent exception.
		/// </summary>
		bool Exists( std::string key ) const;

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
	};

	#include <unify/FastMap.inl>
}