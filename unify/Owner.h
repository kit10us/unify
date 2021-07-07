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