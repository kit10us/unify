// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <conio.h>

template< typename Key, typename Value >
size_t Lookup< Key, Value >::Add( Key key, Value value = Value{} )
	{
		size_t index = m_values.size();
		m_values.push_back( { key, value } );
		m_keyToIndex[key] = index;
		return index;
	}

template< typename Key, typename Value >
size_t Lookup< Key, Value >::Count() const
{
	return m_values.size();
}

template< typename Key, typename Value >
bool Lookup< Key, Value >::Exists( Key key ) const
{
	auto itr = m_keyToIndex.find( key );
	if (itr == m_keyToIndex.end())
	{
		return false;
	}
	return true;
}

template< typename Key, typename Value >
size_t Lookup< Key, Value >::Find( Key key ) const
{
	auto itr = m_keyToIndex.find( key );
	if (itr == m_keyToIndex.end())
	{
		throw std::out_of_range( "Key \"" + key + "\" not found!" );
	}

	return itr->second;
}

template< typename Key, typename Value >
Key Lookup< Key, Value >::GetName( size_t index ) const
{
	if (index >= Count())
	{
		throw std::out_of_range( "Index \"" + std::to_string( index ) + "\" is out of range (" + std::to_string( Count() ) + ")" );
	}

	return m_values[index].key;
}

template< typename Key, typename Value >
Value Lookup< Key, Value >::GetValue( size_t index ) const
{
	if (index >= Count())
	{
		throw std::out_of_range( std::string( "Index \"" ) + std::to_string( index ) + "\" is out of range (" + std::to_string( Count() ) + ")" );
	}
	return m_values[index].value;
}

template< typename Key, typename Value >
Value Lookup< Key, Value >::GetValue( Key key ) const
{
	size_t index = Find( key );
	return GetValue( index );
}

template< typename Key, typename Value >
void Lookup< Key, Value >::SetValue( size_t index, Value value )
{
	if (index >= Count())
	{
		throw std::out_of_range( "Index " + std::to_string( index ) + " not found!" );
	}
	m_values[index].value = value;
}

template< typename Key, typename Value >
void Lookup< Key, Value >::SetValue( Key key, Value value )
{
	auto itr = m_keyToIndex.find( key );
	if (itr == m_keyToIndex.end())
	{
		throw std::out_of_range( "Key \"" + key + "\" not found!" );
	}

	m_values[itr->second].value = value;
}

template< typename Key, typename Value >
typename Lookup< Key, Value >::iterator Lookup< Key, Value >::begin()
{
	return iterator( this, 0 );
}

template< typename Key, typename Value >
typename Lookup< Key, Value >::iterator Lookup< Key, Value >::end()
{
	return iterator( this, this->Count() );
}

template< typename Key, typename Value >
Lookup< Key, Value >::iterator::iterator( Lookup< Key, Value > * lookup, size_t index )
	: m_lookup{ lookup }
	, m_index{ index }
{
}

template< typename Key, typename Value >
auto Lookup< Key, Value >::iterator::operator++()
{
	auto a = ++m_index;
	return *this;
}

template< typename Key, typename Value >
auto Lookup< Key, Value >::iterator::operator++( int )
{
	auto itr = *this;
	m_index++;
	return itr;
}


template< typename Key, typename Value >
auto Lookup< Key, Value >::iterator::operator--()
{
	--m_index;
	return *this;
}

template< typename Key, typename Value >
auto Lookup< Key, Value >::iterator::operator--( int )
{
	auto itr = *this;
	m_index--;
	return itr;
}


template< typename Key, typename Value >
bool Lookup< Key, Value >::iterator::operator==( const iterator & itr ) const
{
	return m_index == itr.m_index;
}

template< typename Key, typename Value >
bool Lookup< Key, Value >::iterator::operator!=( const iterator & itr ) const
{
	return m_index != itr.m_index;
}

template< typename Key, typename Value >
auto & Lookup< Key, Value >::iterator::operator*()
{
	return m_lookup->m_values[m_index];
}

template< typename Key, typename Value >
const auto & Lookup< Key, Value >::iterator::operator*() const
{
	return m_lookup->m_values[m_index];
}

template< typename Key, typename Value >
auto * Lookup< Key, Value >::iterator::operator->()
{
	return &m_lookup->m_values[m_index];
}

template< typename Key, typename Value >
const auto * Lookup< Key, Value >::iterator::operator->() const
{
	return &m_lookup->m_values[m_index];
}
