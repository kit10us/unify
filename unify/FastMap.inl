// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <conio.h>

template< typename Key, typename Value >
size_t FastMap< Key, Value >::Add( Key key, Value value = Value{} )
	{
		size_t index = m_values.size();
		m_values.push_back( value );
		m_keys.push_back( key );
		m_keyToIndex[key] = index;
		return index;
	}

template< typename Key, typename Value >
size_t FastMap< Key, Value >::Count() const
{
	return m_values.size();
}

template< typename Key, typename Value >
bool FastMap< Key, Value >::Exists( std::string key ) const
{
	auto itr = m_keyToIndex.find( key );
	if (itr == m_keyToIndex.end())
	{
		return false;
	}
	return true;
}

template< typename Key, typename Value >
size_t FastMap< Key, Value >::Find( Key key ) const
{
	auto itr = m_keyToIndex.find( key );
	if (itr == m_keyToIndex.end())
	{
		throw std::out_of_range( "Key \"" + key + "\" not found!" );
	}

	return itr->second;
}

template< typename Key, typename Value >
Key FastMap< Key, Value >::GetName( size_t index ) const
{
	if (index >= Count())
	{
		throw std::out_of_range( "Index \"" + std::to_string( index ) + "\" is out of range (" + std::to_string( Count() ) + ")" );
	}

	return m_keys[index];
}

template< typename Key, typename Value >
Value FastMap< Key, Value >::GetValue( size_t index ) const
{
	if (index >= Count())
	{
		throw std::out_of_range( std::string( "Index \"" ) + std::to_string( index ) + "\" is out of range (" + std::to_string( Count() ) + ")" );
	}
	return m_values[index];
}

template< typename Key, typename Value >
Value FastMap< Key, Value >::GetValue( Key key ) const
{
	size_t index = Find( key );
	return GetValue( index );
}

template< typename Key, typename Value >
void FastMap< Key, Value >::SetValue( size_t index, Value value )
{
	if (index >= Count())
	{
		throw std::out_of_range( "Index " + std::to_string( index ) + " not found!" );
	}
	m_values[index] = value;
}

template< typename Key, typename Value >
void FastMap< Key, Value >::SetValue( Key key, Value value )
{
	auto itr = m_keyToIndex.find( key );
	if (itr == m_keyToIndex.end())
	{
		throw std::out_of_range( "Key \"" + key + "\" not found!" );
	}

	m_values[itr->second] = value;
}