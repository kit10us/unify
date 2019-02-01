// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

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
