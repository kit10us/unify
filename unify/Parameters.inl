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
T Parameters::Get( std::string name ) const
{
    ParameterMap::const_iterator itr = m_parameters.find( name );
    if ( itr == m_parameters.end() )
    {
        throw Exception( "Failed to find Parameters: \"" + name + "\"!" );
    }
    m_auditItemsUsed.insert( name );

	T value {};
	try
	{
		value = unify::any_cast< T >(itr->second.value);
	}
	catch( ... )
	{
		throw unify::BadCast( std::string( "Failed to cast \"" ) + name + "\" of type " + itr->second.value.type().name() + "!" );
    }

    return value;
}

template< typename T > 
T Parameters::Get( std::string name, const T & defaultValue ) const
{
    ParameterMap::const_iterator itr = m_parameters.find( name );
    if( itr == m_parameters.end() )
    {
        return defaultValue;
    }
    m_auditItemsUsed.insert( name );
	
	T value;
	try
	{
		value = unify::any_cast< T >(itr->second.value);
	}
	catch( ... )
    {
        throw BadCast( "Failed to cast \"" + name + "\" of type " + itr->second.value.type().name() + "!" );
    }
    return value;
}

template< typename T > 
Parameters & Parameters::Default( std::string name, const T & value )
{
    if( m_parameters.find( name ) == m_parameters.end() )
    {
        m_parameters[ name ] = static_cast<T>(value);
    }
    return *this;
}

template< typename T > 
Parameters & Parameters::Set( std::string name, const T & value )
{
    m_parameters[ name ].value = static_cast<T>(value);
    return *this;
}
