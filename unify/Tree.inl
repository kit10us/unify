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


unify::Tree::Tree()
: m_child( 0 )
, m_parent( 0 )
, m_nextSib( 0 )
, m_prevSib( 0 )
{
}

inline unify::Tree::Tree( std::string sName )
: m_name( sName )
, m_child( 0 )
, m_parent( 0 )
, m_nextSib( 0 )
, m_prevSib( 0 )
{
}

inline unify::Tree::Tree( const unify::Tree & tree )
: m_name( tree.m_name )
, m_child( tree.m_child )
, m_parent( tree.m_parent )
, m_nextSib( tree.m_nextSib )
, m_prevSib( tree.m_prevSib )
{
}

inline unify::Tree::~Tree()
{
}

inline unify::Tree & unify::Tree::operator=( const unify::Tree & tree )
{
	m_name = tree.m_name;
	m_child = tree.m_child;
	m_parent = tree.m_parent;
	m_nextSib = tree.m_nextSib;
	m_prevSib = tree.m_prevSib;
	return *this;
}


// Attach us to a parent
inline void unify::Tree::AttachTo( unify::Tree * pTo )
{
	if( pTo == m_parent ) return;

	// Remove us from any previous frame hierarchy...
	if( m_parent )
	{
		// Break our sibling relationship with our PrevSib
		if( m_prevSib )
		{
			// Assign our siblings to each other
			m_prevSib->m_nextSib = m_nextSib;
		}
		else	// We are the first child
		{
			// Make our next sib the first child of our parent
			m_parent->m_child = m_nextSib;
		}

		// Break our sibling relationship with our NextSib
		if( m_nextSib )
		{
			m_nextSib->m_prevSib = m_prevSib;
			m_nextSib = 0;
		}
		m_prevSib = 0;
	}

	// Attach to new frame hierarchy...
	m_parent = pTo;
	if( pTo )
	{
		// If there is already a child, take it's place
		if( pTo->m_child )
		{
			m_nextSib = pTo->m_child;
			m_nextSib->m_prevSib = this;
		}
		pTo->m_child = this;
	}
}

inline void unify::Tree::Detach()
{
	// If we have no parent then we are not attached and cannot detach.
	if( m_parent == 0 ) return;

	// If we have don't have a previous sibling than we are the first child (update the parent).
	if( m_prevSib == 0 )
	{
		// Parent:
		m_parent->m_child = m_nextSib;

		// Previous sibling:
		// NONE

		// Next sibling:
		if( m_nextSib != 0 ) m_nextSib->m_prevSib = 0;
	}
	else
	{
		// Parent:
		// NO CHANGE

		// Previous sibling:
		m_prevSib->m_nextSib = m_nextSib;

		// Next sibling:
		if( m_nextSib != 0 ) m_nextSib->m_prevSib = m_prevSib;
	}
}

inline void unify::Tree::SetName( std::string name )
{
	m_name = name;
}

inline std::string unify::Tree::GetName() const
{
	return m_name;
}

inline unify::Tree * unify::Tree::GetChild()
{
	return m_child;
}

inline unify::Tree * unify::Tree::GetParent()
{
	return m_parent;
}

inline unify::Tree * unify::Tree::GetRoot()
{
	return( m_parent ? m_parent->GetRoot() : this );
}

inline unify::Tree * unify::Tree::GetTopSibling()
{
	// Easy if we have a parent...
	if( m_parent ) return m_parent->GetChild();

	// No parent, then figure it out...
	// Check if we are NOT the top sibling...
	if( m_prevSib )
	{
		return m_prevSib->GetTopSibling();
	}

	// We ARE the top sibling
	return this;
}

inline unify::Tree * unify::Tree::GetBottomSibling()
{
	// Check if we are NOT the bottom sibling...
	if( m_nextSib )
	{
		return m_nextSib->GetBottomSibling();
	}

	// We ARE the bottom sibling
	return this;
}

inline unify::Tree * unify::Tree::GetPrev()
{
	return m_prevSib;
}

inline unify::Tree * unify::Tree::GetNext()
{
	return m_nextSib;
}

inline unify::Tree * unify::Tree::SetParent( unify::Tree * parent )
{
	return( m_parent = parent );
}

inline unify::Tree * unify::Tree::SetChild( unify::Tree * child )
{
	return( m_child = child );
}

inline unify::Tree * unify::Tree::SetPrev( unify::Tree * prev )
{
	return( m_prevSib = prev );
}

inline unify::Tree * unify::Tree::SetNext( unify::Tree * next)
{
	return( m_nextSib = next );
}
