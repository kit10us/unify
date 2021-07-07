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


#include <unify/Owner.h>

using namespace unify;

Owner::Owner(std::string name)
	: m_name{ name }
{
}

Owner::ptr unify::Owner::Create(std::string name) 
{
	return ptr(new Owner{ name } ); 
}

std::string Owner::GetName() const
{
	return m_name;
}

OwnerProperty::OwnerProperty( std::string name )
	: m_name{ name }
{
}

std::string OwnerProperty::GetName() const
{
	return m_name;
}

void OwnerProperty::SetName( std::string name )
{
	m_name = name;
}

void OwnerProperty::AddOwner( Owner::ptr owner )
{
	m_owners.push_back( owner );
}

size_t OwnerProperty::Owners() const
{
	for( auto itr = m_owners.begin(); itr != m_owners.end(); )
	{
		if( itr->expired() )
		{
			itr = m_owners.erase( itr );
		}
		else
		{
			itr++;
		}
	}

	return m_owners.size();
}

OwnerProperty::ptr OwnerProperty::Create( std::string name )
{
	return OwnerProperty::ptr( new OwnerProperty( name ) );
}
