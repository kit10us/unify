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


//	QList is a virtual list inherited by other lits. It provides a set of common methods.

#pragma once

#include <unify/Unify.h>
#include <memory>
#include <string>

namespace unify
{
	typedef unsigned int		QTID;
	#define QTID_INVALID		unsigned int_MAX

	// A link within the chain of the Link List...
	template< typename T >
	class TLink
	{
		template< typename T >
		friend class LinkList;

	public:
		TLink();
		TLink( T * item, std::string name );
		~TLink();

		std::string Name() const;
		T * Item() const;

		TLink< T > * Previous();
		const TLink< T > * Previous() const;

		TLink< T > * Next();
		const TLink< T > * Next() const;

		unsigned int m_uFlags;
		float m_fSortValue;

	public:
		std::shared_ptr< T > m_item;
		std::string m_name;		// Name in static list	(optional)

		TLink< T > * m_previous;
		TLink< T > * m_next;
	};
	#include <unify/TLink.inl>
}

