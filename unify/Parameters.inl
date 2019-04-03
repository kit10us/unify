// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

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
