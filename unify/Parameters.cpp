// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/Parameters.h>
#include <unify/String.h>

using namespace unify;
using namespace string;

Parameters::Parameters()
{
}

template< typename T >
Parameters::Parameters( std::string name, T value )
{
    m_parameters[ name ] = value;
}

Parameters::Parameters( std::initializer_list< Parameter > parameters )
{
	for( auto parameter : parameters )
	{
		m_parameters[ parameter.name ] = parameter;
	}
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

size_t Parameters::Count() const
{
	return m_parameters.size();
}

Parameters & Parameters::Default( std::string name, const Any & value )
{
    if( m_parameters.find( name ) == m_parameters.end() )
    {
        m_parameters[ name ].value = value;
    }
    return *this;
}

bool Parameters::Exists( std::string name ) const
{
	std::vector< std::string > split = Split< std::string >( name, ',' );
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
	m_parameters[ name ].value = std::string( value );
    return *this;
}

Parameters & Parameters::Set( Parameter parameter )
{
	m_parameters[parameter.name] = parameter;
	return *this;
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
	std::string allItems;
	std::string setButNotUsed;
	std::string notSetButUsed;
    if( m_auditItemsUsed.size() != m_parameters.size() )
    {
        {
            for( auto parameter : m_parameters )
            {
				if ( !allItems.empty() )
				{
					allItems += ", ";
				}
				allItems += parameter.first;

                auto itr = m_auditItemsUsed.find( parameter.first );
                if( itr == m_auditItemsUsed.end() )
                {
                    if( !setButNotUsed.empty() )
                    {
						setButNotUsed += ", ";
                    }
					setButNotUsed += parameter.first;
                }
            }
        }

        {
            for( auto item : m_auditItemsUsed )
            {
                auto itr = m_parameters.find( item );
                if( itr == m_parameters.end() )
                {
                    if( !notSetButUsed.empty())
                    {
						notSetButUsed += ", ";
                    }
					notSetButUsed += item;
                }
            }
		}
    }
    return 
		"All items: " + ( allItems.empty() ? "<none>" : allItems ) + 
		"\nItems set but not used: " + (setButNotUsed.empty() ? "<none>" : setButNotUsed) +
		"\nItems not set but used: " + (notSetButUsed .empty() ? "<none>" : notSetButUsed);
}

Parameters & Parameters::operator+=( Parameters & parameters )
{
    m_parameters.insert( parameters.m_parameters.begin(), parameters.m_parameters.end() );
    return *this;
}

Parameters Parameters::operator+( Parameters& parameters )
{
    Parameters newParameters;
    newParameters += *this;
    newParameters += parameters;
    return newParameters;
}

template<> 
bool Parameters::Cast< bool >( std::string name ) const
{
	try
	{
		return Get< bool >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	try
	{
		return Get< char >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	try
	{
		return Get< unsigned char >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	try
	{
		return Get< int >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	try
	{
		return Get< unsigned int >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	try
	{
		return Get< float >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	try
	{
		return Get< double >( name ) ? true : false;
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"bool\"." );
}

template<>
char Parameters::Cast< char >( std::string name ) const
{
	try
	{
		return (char)Get< bool >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (char)Get< char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (char)Get< unsigned char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (char)Get< int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (char)Get< unsigned int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (char)Get< float >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (char)Get< double >( name );
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"char\"." );
}

template<>
unsigned char Parameters::Cast< unsigned char >( std::string name ) const
{
	try
	{
		return (unsigned char)Get< bool >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned char)Get< char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned char)Get< unsigned char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned char)Get< int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned char)Get< unsigned int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned char)Get< float >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned char)Get< double >( name );
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"unsigned char\"." );
}

template<>
int Parameters::Cast< int >( std::string name ) const
{
	try
	{
		return (int)Get< bool >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (int)Get< char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (int)Get< unsigned char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (int)Get< int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (int)Get< unsigned int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (int)Get< float >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (int)Get< double >( name );
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"int\"." );
}

template<>
unsigned int Parameters::Cast< unsigned int >( std::string name ) const
{
	try
	{
		return (unsigned int)Get< bool >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned int)Get< char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned int)Get< unsigned char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned int)Get< int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned int)Get< unsigned int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned int)Get< float >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (unsigned int)Get< double >( name );
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"unsigned int\"." );
}

template<>
float Parameters::Cast< float >( std::string name ) const
{
	try
	{
		return (float)Get< bool >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (float)Get< char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (float)Get< unsigned char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (float)Get< int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (float)Get< unsigned int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (float)Get< float >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (float)Get< double >( name );
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"float\"." );
}


template<>
double Parameters::Cast< double >( std::string name ) const
{
	try
	{
		return (double)Get< bool >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (double)Get< char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (double)Get< unsigned char >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (double)Get< int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (double)Get< unsigned int >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (double)Get< float >( name );
	}
	catch( ... )
	{
	}

	try
	{
		return (double)Get< double >( name );
	}
	catch( ... )
	{
	}

	throw Exception( "Failed to cast \"" + name + "\" to specific type \"unsigned int\"." );
}
