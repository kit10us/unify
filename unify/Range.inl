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


template< typename T >
Range< T >::Range()
: m_isSet( false )
{
}

template< typename T >
unify::Range< T >::Range( T min, T max )
: m_isSet( true )
, m_min( min )
, m_max( min )
{
	Add( max );
}

template< typename T >
Range< T >::Range( const Range & range )
: m_isSet( range.m_isSet )
, m_min( range.m_min )
, m_max( range.m_max )
{
}

template< typename T >
Range< T >::Range( std::string text )
{
	std::vector< T > split = Split< T >( text, ',' );
    m_min = split[ 0 ];
    m_max = split[ 1 ];
}

template< typename T >
void unify::Range< T >::Clear()
{
	m_isSet = false;
}

template< typename T >
void unify::Range< T >::Add( T value )
{
	if( m_isSet )
	{
		m_min = std::min<>( m_min, value );
		m_max = std::max<>( m_max, value );
	}
	else
	{
		m_min = value;
		m_max = value;
		m_isSet = true;
	}
}

template< typename T >
bool unify::Range< T >::IsSet() const
{
	return m_isSet;
}

template< typename T >
T unify::Range< T >::Min() const
{
	assert( m_isSet );
	return m_min;
}

template< typename T >
T unify::Range< T >::Max() const
{
	assert( m_isSet );
	return m_max;
}

template< typename T >
bool Range< T >::IsWithin( const T & value ) const
{
	return value >= Min() && value <= Max();
}

template< typename T >
Range< T > & Range< T >::operator=( const Range< T > & range )
{
	m_isSet = range.m_isSet;
	m_min = range.m_min;
	m_max = range.m_max;
	return *this;
}

template< typename T >
bool unify::Range< T >::operator==( const Range< T > & range ) const
{
	return m_isSet == range.m_isSet && m_min == range.m_min && m_max == range.m_max;
}

template< typename T >
bool unify::Range< T >::operator!=( const Range< T > & range ) const
{
	return !( *this == range );
}

template< typename T >
void unify::Range< T >::operator+=( const T value )
{
	Add( value );
}
