// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/Parameters.h>
#include <unify/String.h>

using namespace unify;

Parameters::Parameters()
{
}

template< typename T >
Parameters::Parameters( std::string name, T value )
{
    m_parameters[ name ] = value;
}

Parameters::~Parameters()
{
}

Parameters & Parameters::Reset()
{
    m_parameters.clear();
    m_auditItemsUsed.clear();
    return *this;
}

Parameters & Parameters::Default( std::string name, const unify::Any & value )
{
    if( m_parameters.find( name ) == m_parameters.end() )
    {
        m_parameters[ name ] = value;
    }
    return *this;
}

bool Parameters::Exists( std::string name ) const
{
	std::vector< std::string > split = unify::Split< std::string >( name, ',' );
	for( std::vector< std::string >::iterator itr = split.begin(); itr != split.end(); ++itr )
    {
        if( m_parameters.find( *itr ) == m_parameters.end() )
        {
            return false;
        }
    }
    return true;
}

Parameters & Parameters::Set( std::string name, const char * value )
{
	m_parameters[ name ] = std::string( value );
    return *this;
}

// Unsigned int specialization to prevent issues with unsigned long int (uint32).
template<> 
unsigned int Parameters::Get< unsigned int >( std::string name ) const
{
    ParameterMap::const_iterator iterator = m_parameters.find( name );
    if ( iterator == m_parameters.end() )
    {
        throw Exception( "Failed to find Parameters: \"" + name + "\"!" );
    }
    m_auditItemsUsed.insert( name );
    
    if( iterator->second.type() == typeid( unsigned int ) )
    {
        return unify::any_cast< unsigned int >( iterator->second );
    }
    else if( iterator->second.type() == typeid( unsigned long int ) )
    {
        return unify::any_cast< unsigned long int >( iterator->second );
    }

    throw Exception( "Failed to cast \"" + name + "\" of type " + iterator->second.type().name() + "!" );
}

// Unsigned int specialization to prevent issues with unsigned long int (uint32).
template<> 
unsigned int Parameters::Get< unsigned int >( std::string name, const unsigned int & defaultValue ) const
{
    ParameterMap::const_iterator iterator = m_parameters.find( name );
    if( iterator == m_parameters.end() )
    {
        return defaultValue;
    }
    m_auditItemsUsed.insert( name );
    
    if( iterator->second.type() == typeid( unsigned int ) )
    {
        return unify::any_cast< unsigned int >( iterator->second );
    }
    else if( iterator->second.type() == typeid( unsigned long int ) )
    {
        return unify::any_cast< unsigned long int >( iterator->second );
    }

    throw Exception( "Failed to cast \"" + name + "\" of type " + iterator->second.type().name() + "!" );
}

std::string Parameters::ToString() const
{
    std::string out;
    for( ParameterMap::const_iterator iterator = m_parameters.begin(), end = m_parameters.end(); iterator != end; ++iterator )
    {
        if( ! out.empty() ) 
        {
            out += ", ";
        }
        out += "\"" + iterator->first + "\"";
    }
    return out;
}

unsigned int Parameters::AuditCount() const
{
    return ( m_parameters.size() - m_auditItemsUsed.size() );
}

std::string Parameters::Audit() const
{
    std::string out;
    if( m_auditItemsUsed.size() != m_parameters.size() )
    {
        {
            out += "Items not set but used: ";
            bool first = true;
            for( ParameterMap::const_iterator iterator = m_parameters.begin(), end = m_parameters.end(); iterator != end; ++iterator )
            {
                std::set< std::string, CaseInsensitiveLessThanTest >::const_iterator iteratorSecond = m_auditItemsUsed.find ( iterator->first );
                if( iteratorSecond == m_auditItemsUsed.end() )
                {
                    if( ! first )
                    {
                        out += ", ";
                    }
                    first = false;
                    out += iterator->first;
                }
            }
        }

        {
            out += "  Items set but not used: ";
            bool first = true;
            for( std::set< std::string, CaseInsensitiveLessThanTest >::const_iterator iterator = m_auditItemsUsed.begin(), end = m_auditItemsUsed.end(); iterator != end; ++iterator )
            {
                ParameterMap::const_iterator iteratorSecond = m_parameters.find( *iterator );
                if( iteratorSecond == m_parameters.end() )
                {
                    if( ! first )
                    {
                        out += ", ";
                    }
                    first = false;
                    out += *iterator;
                }
            }
        }
    }
    return out;
}

Parameters & Parameters::operator+=( Parameters & parameters )
{
    m_parameters.insert( parameters.m_parameters.begin(), parameters.m_parameters.end() );
    return *this;
}

Parameters Parameters::operator+( Parameters& parameters )
{
    unify::Parameters newParameters;
    newParameters += *this;
    newParameters += parameters;
    return newParameters;
}
