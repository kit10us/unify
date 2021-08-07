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


#pragma once

#include <unify/Unify.h>
#include <unify/BadCast.h>
#include <unify/String.h>
#include <unify/Any.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>

namespace unify
{
	struct Parameter
	{
		Parameter() = default;

		template< typename T >
		Parameter( std::string name, T value )
			: name{ name }
			, value{ value }
		{
		}

		/*
		template< >
		Parameter( std::string name, const char * value )
			: name{ name }
			, value{ std::string( value ) }
		{
		}
		*/
	
		std::string name;
		unify::Any value;
	};

    class Parameters
    {
    public:
        Parameters();
 
        template< typename T >
        Parameters( std::string name, T value );

		Parameters( std::initializer_list< Parameter > parameters );

        virtual ~Parameters();

        virtual Parameters & Reset();

		/// <summary>
		/// Returns the number of parameters.
		/// </summary>
		size_t Count() const;

        // Default only sets a value if it hasn't already been set. 
		Parameters & Default( std::string name, const unify::Any & value );
        
        // Default only sets a value if it hasn't already been set. 
		template< typename T > 
		Parameters & Default( std::string name, const T & value );

        template< typename T > 
		Parameters & Set( std::string name, const T & value );
        
		Parameters & Set( std::string name, const char * value );

		Parameters & Set( Parameter parameter );
	
        bool Exists( std::string name ) const;

		template< typename T > T Get( std::string name ) const;
        template< typename T > T Get( std::string name, const T & defaultValue ) const;

		/// <description>
		/// Specialization of unsigned int for similar type conversion.
		/// </description>
		template< typename T > T Cast( std::string name ) const;

		/// <description>
		/// Specialization of unsigned int for similar type conversion, with a default value.
		/// </description>
		//template< typename T > T Cast( std::string name, const T & defaultValue ) const;

		std::string ToString() const;


        size_t AuditCount() const;
        
		/// <summary>
		/// Perform an audit of all parameters, if they are used, not used, etc., returning the results as a string.
		/// </summary>
		std::string Audit() const;

        Parameters & operator+=( Parameters & parameters );
        Parameters operator+( Parameters & parameters );

    private:
        typedef std::map< std::string, Parameter, string::CaseInsensitiveLessThanTest > ParameterMap;
        ParameterMap m_parameters;
        mutable std::set< std::string, string::CaseInsensitiveLessThanTest > m_auditItemsUsed; // This helps reduce typos by ensuring every explicitly get and set value are paired. It is naturally ignored for defaults.
    };

	template<> bool Parameters::Cast< bool >( std::string name ) const;
	template<> char Parameters::Cast< char >( std::string name ) const;
	template<> unsigned char Parameters::Cast< unsigned char >( std::string name ) const;
	template<> int Parameters::Cast< int >( std::string name ) const;
	template<> unsigned int Parameters::Cast< unsigned int >( std::string name ) const;
	template<> float Parameters::Cast< float >( std::string name ) const;
	template<> double Parameters::Cast< double >( std::string name ) const;

	#include <unify/Parameters.inl>
}