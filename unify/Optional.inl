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
Optional< T >::Optional()
{
}

template< typename T >
Optional< T >::Optional( const T & value )
	: m_thing( new Keeper( value ) )
{
}

template< typename T >
Optional< T >::~Optional()
{
	m_thing.reset();
}

template< typename T >
const T & Optional< T >::operator()() const
{
	if ( m_thing.empty() )
	{
		throw new unify::Exception( "Optional referenced when empty!" );
	}
	return m_thing.value;
}