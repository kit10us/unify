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

namespace unify 
{
	class Tree
	{
	public:
		Tree();
		Tree( std::string sName );
		Tree( const Tree & tree );
		virtual ~Tree();
		virtual Tree & operator=( const Tree & tree );
		virtual void Detach();
		virtual void AttachTo( Tree * pTo );
		virtual void SetName( std::string name );
		virtual std::string GetName() const;
		virtual Tree * GetTopSibling();
		virtual Tree * GetBottomSibling();
		virtual Tree * GetRoot();
		virtual Tree * GetParent();
		virtual Tree * GetChild();
		virtual Tree * GetPrev();
		virtual Tree * GetNext();
		virtual Tree * SetParent( Tree * parent );
		virtual Tree * SetChild( Tree * child );
		virtual Tree * SetPrev( Tree * prev );
		virtual Tree * SetNext( Tree * next);

	protected:
		Tree * m_child;	// A child would have us as Parent
		Tree * m_prevSib; // Sibling we are Next to
		Tree * m_nextSib;	// Next sibling to our parent (child of our parent)
		Tree * m_parent;

		std::string m_name;	// Frames name
	};
} // namespace unify
#include <unify/Tree.inl>
