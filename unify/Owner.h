// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <string>
#include <memory>
#include <list>

namespace unify
{
	/// <summary>
	/// Provides ownership symantics, where two or more objects can observer ownership of memory or events.
	/// </summary>
	class Owner
	{
		Owner( std::string name );
	public:
		typedef std::shared_ptr< Owner > ptr;
		typedef std::weak_ptr< Owner > weak_ptr;

		static ptr Create( std::string name );

		std::string GetName() const;

	private:
		std::string m_name;		
	};

	class OwnerProperty
	{
		OwnerProperty( std::string name );
	public:
		typedef std::shared_ptr< OwnerProperty > ptr;

		static ptr Create( std::string name = std::string() );

		std::string GetName() const;

		void SetName( std::string name );

		void AddOwner( Owner::ptr owner );

		size_t Owners() const;

	private:
		std::string m_name;
		mutable std::list< Owner::weak_ptr > m_owners;
	};
}