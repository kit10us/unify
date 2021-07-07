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


template< typename T >
LinkList< T >::LinkList()
: m_pFirst( 0 )
, m_pLast( 0 )
, m_uCount( 0 )
, m_uLisFlags( FLAG00 )
{
}

template< typename T >
LinkList< T >::~LinkList()
{
	Clear();
}

template< typename T >
unsigned int LinkList< T >::Count()
{
	return m_uCount;
}

template< typename T >
void LinkList< T >::SetLisFlags( unsigned int uFlags )
{
	m_uLisFlags = uFlags;
}

template< typename T >
unsigned int LinkList< T >::GetLisFlags()
{
	return m_uLisFlags;
}

// Destroy contents.
template< typename T >
void LinkList< T >::Clear()
{
	TLink< T > * pLink = m_pFirst;
	TLink< T > * pNext = 0;
	while( pLink )
	{
		pNext = pLink->Next();
		delete pLink;
		pLink = pNext;
	}
	m_pFirst = nullptr;
	m_pLast = nullptr;
	m_uCount = 0;
}

template< typename T >
T* LinkList< T >::AddItem( T * item, std::string sName )
{
	return AddItem( item, FLAG00, 0.0f, sName );
}

template< typename T >
T * LinkList< T >::AddItem( T * item, unsigned int uFlags, std::string sName )
{
	return AddItem( item, uFlags, 0.0f, sName );
}

template< typename T >
T * LinkList< T >::AddItem( T * item, float fSortValue, std::string sName )
{
	return AddItem( item, FLAG00, fSortValue, sName );
}

template< typename T> 
T * LinkList< T >::AddItem( T * item, unsigned int uFlags, float fSortValue, std::string sName )
{
	TLink< T > * pNewLink = new TLink< T >( item, sName );
	if( ! pNewLink ) return 0;

	pNewLink->m_uFlags = uFlags;
	pNewLink->m_fSortValue = fSortValue;

	if( ! m_pFirst )
	{
		m_pFirst = pNewLink;
		m_pLast = pNewLink;
	}
	else
	{
		if( unify::CheckFlag(m_uLisFlags, LINKLIST_SORT) )
		{
			// Sort into list..
			TLink< T > * pLink = m_pFirst;

			if( unify::CheckFlag(m_uLisFlags, LINKLIST_SORTREVERSE) )
			{
				while( pLink && pLink->m_fSortValue > pNewLink->m_fSortValue )
				{
					pLink = pLink->Next();
				}
			}
			else
			{
				while( pLink && pLink->m_fSortValue < pNewLink->m_fSortValue )
				{
					pLink = pLink->Next();
				}
			}

			// Found a larger link
			if( pLink )
			{
				if( pLink == m_pFirst )
				{
					m_pFirst = pNewLink;
				}

				pNewLink->m_previous = pLink->m_previous;
				if( pNewLink->m_previous )
				{
					pNewLink->m_previous->m_next = pNewLink;
				}
				pNewLink->m_next = pLink;
				pLink->m_previous = pNewLink;
			}
			else
			{
				m_pLast->m_next = pNewLink;
				pNewLink->m_previous = m_pLast;
				m_pLast = pNewLink;
			}
		}
		
		else	// Non-sorted...
		{
			m_pLast->m_next = pNewLink;
			pNewLink->m_previous = m_pLast;
			m_pLast = pNewLink;
		}
	}

	m_uCount++;
	
	return item;
}

template< typename T >
bool LinkList< T >::DeleteItem( TLink< T > * & pLink )
{
	/////////////////////////////////////////
	// REMOVE LINK FROM THE PRIMARY LIST
	/////////////////////////////////////////

	// Check if we did not find it...
	if( ! pLink ) return false;

	// Check if is last...
	if( m_pLast == pLink ) m_pLast = m_pLast->m_pPrevious;
	// if is first link...
	if( m_pFirst == pLink ) m_pFirst = m_pFirst->m_pNext;

	
	/////////////////////////////////////////
	// REMOVE LINK FROM ITEM LIST
	/////////////////////////////////////////

	if( pLink->m_pPrevious ) pLink->m_pPrevious->m_pNext = pLink->m_pNext;
	if( pLink->m_pNext ) pLink->m_pNext->m_pPrevious = pLink->m_pPrevious;

	delete pLink;
	
	m_uCount--;

	return true;
}

template< typename T >
bool LinkList< T >::DeleteItem( std::string sName )
{
	if( !m_pFirst ) return false;
	TLink< T > * pLink = m_pFirst;

	// Find the link...
	while( pLink && !StringIs( pLink->m_sName, sName ) )
	{
		pLink = pLink->m_pNext;
	}

	return DeleteItem( pLink );
}

template< typename T >
bool LinkList< T >::DeleteItem( T * pItem )
{
	if( !m_pFirst ) return false;
	TLink< T > * pLink = m_pFirst;

	// Find the link...
	while( pLink && pLink->m_pItem != pItem )
	{
		pLink = pLink->m_pNext;
	}

	return DeleteItem( pLink );	
}

template< typename T > 
T * LinkList< T >::GotoFirst( Query< T > * pQuery )
{
	pQuery->m_pCurrent = m_pFirst;
	return( pQuery->m_pCurrent ? pQuery->m_pCurrent->Item() : 0 );
}

template< typename T >
T * LinkList< T >::GotoLast( Query< T > * pQuery )
{
	pQuery->m_pCurrent = m_pLast;
	return( pQuery->m_pCurrent ? pQuery->m_pCurrent->Item() : 0 );
}

template< typename T > 
T * LinkList< T >::GotoNext( Query< T > * pQuery )
{
	pQuery->m_pCurrent = pQuery->m_pCurrent->Next();
	return( pQuery->m_pCurrent ? pQuery->m_pCurrent->Item() : 0 );
}

template< typename T > 
T * LinkList< T >::GotoPrevious( Query< T > * pQuery )
{
	pQuery->m_pCurrent = pQuery->m_pCurrent->Previous();
	return( pQuery->m_pCurrent ? pQuery->m_pCurrent->Item() : 0 );
}

template< typename T >
T * LinkList< T >::Find( std::string sName )
{
	TLink< T > * pLink = m_pFirst;
	while( pLink )
	{
		if( unify::string::StringIs( sName, pLink->Name() ) ) return pLink->Item();
		pLink = pLink->Next();
	}
	
	return 0;
}

template< typename T >
T * LinkList< T >::Find( Query< T > * pQuery, std::string sName )
{
	pQuery->m_pCurrent = m_pFirst;
	while( pQuery->m_pCurrent )
	{
		if( unify::string::StringIs( sName, pQuery->Name() ) ) return pQuery->m_pCurrent->m_pItem;
		pQuery->m_pCurrent = pQuery->m_pCurrent->m_pNext;
	}
	
	return 0;
}

// Returns the name of the item by it's address (Since an item can be in a list twice, it will return the first instance)
template< typename T >
const std::string LinkList< T >::Name( const T * pItem )
{
	TLink< T > * pLink = m_pFirst;
	unsigned int u = 0;
	while( pLink ) { 
		if( pLink->m_pItem == pItem ) return pLink->m_sName;
		pLink = pLink->m_pNext;
		u++;
	}

	return "";
}

// Returns the name of the item by the items index...
template< typename T >
const std::string LinkList< T >::Name( unsigned int uIndex )
{
	if ( uIndex >= m_uCount ) return 0;

	TLink< T > * pLink = m_pFirst;
	unsigned int u = 0;
	while( pLink ) { 
		if ( u == uIndex ) return pLink->m_sName;
		pLink = pLink->m_pNext;
		u++;
	}
	return "";
}

// Return a specific item by index.
// Return 0 if out of range.
template< typename T >
T * LinkList< T >::Item( unsigned int uIndex )
{
	if ( uIndex >= m_uCount ) return 0;

	TLink< T > * pLink = m_pFirst;
	unsigned int u = 0;
	while( pLink ) 
	{ 
		if ( u == uIndex ) return pLink->Item();
		pLink = pLink->Next();
		u++;
	}
	return 0;
}
