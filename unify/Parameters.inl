// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

template< typename T_Type > 
T_Type Parameters::Get( std::string name ) const
{
    ParameterMap::const_iterator itr = m_parameters.find( name );
    if ( itr == m_parameters.end() )
    {
        throw Exception( "Failed to find Parameters: \"" + name + "\"!" );
    }
    m_auditItemsUsed.insert( name );
    if( itr->second.type() != typeid( T_Type ) )
    {
        throw Exception( "Failed to cast \"" + name + "\" of type " + itr->second.type().name() + "!" );
    }
    return unify::any_cast< T_Type >( itr->second );
}

template< typename T_Type > 
T_Type Parameters::Get( std::string name, const T_Type & defaultValue ) const
{
    ParameterMap::const_iterator itr = m_parameters.find( name );
    if( itr == m_parameters.end() )
    {
        return defaultValue;
    }
    m_auditItemsUsed.insert( name );
    if( itr->second.type() != typeid( T_Type ) )
    {
        throw Exception( "Failed to cast \"" + name + "\" of type " + itr->second.type().name() + "!" );
    }
    return unify::any_cast< T_Type >( itr->second );
}

template< typename T_Type > 
Parameters & Parameters::Default( std::string name, const T_Type & value )
{
    if( m_parameters.find( name ) == m_parameters.end() )
    {
        m_parameters[ name ] = static_cast<T_Type>(value);
    }
    return *this;
}

template< typename T_Type > 
Parameters & Parameters::Set( std::string name, const T_Type & value )
{
    m_parameters[ name ] = static_cast<T_Type>(value);
    return *this;
}