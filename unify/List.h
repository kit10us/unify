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
#include <unify/TLink.h>
#include <string>

namespace unify
{
	// For traversal
	template< typename T >
	class Query
	{
	public:
		Query();

		TLink< T > * m_pCurrent;
		std::string Name();
		float SortValue();		
	};


	template< typename T >
	class QList
	{
	public:
		virtual void Clear() = 0;
		virtual QTID Count() = 0;

		// Traversal...
		virtual T * GotoFirst( Query< T > * pQuery ) = 0;
		virtual T * GotoLast( Query< T > * pQuery ) = 0;
		virtual T * GotoPrevious( Query< T > * pQuery ) = 0;
		virtual T * GotoNext( Query< T > * pQuery ) = 0;
	};

	#include <unify/List.inl>
}

