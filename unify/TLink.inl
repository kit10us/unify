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


/////
// TLink
/////

template< typename T >
TLink< T >::TLink()
	: m_item{ nullptr }
	, m_previous{ nullptr }
	, m_next{ nullptr }
{
}

template< typename T >
TLink< T >::TLink( T * item, std::string name )
	: m_item{ item }
	, m_name{ name }
	, m_previous{ nullptr }
	, m_next{ nullptr }
{
}

template< typename T >
TLink< T >::~TLink()
{
	m_item = nullptr;
	m_previous = nullptr;
	m_next = nullptr;
}

template< typename T >
std::string TLink< T >::Name() const
{
	return m_name;
}

template< typename T >
T * TLink< T >::Item() const
{
	return m_item.get();
}

template< typename T >
TLink< T > * TLink< T >::Previous()
{
	return m_previous;
}

template< typename T >
const TLink< T > * TLink< T >::Previous() const
{
	return m_previous;
}

template< typename T >
TLink< T > * TLink< T >::Next()
{
	return m_next;
}

template< typename T >
const TLink< T > * TLink< T >::Next() const
{
	return m_next;
}
