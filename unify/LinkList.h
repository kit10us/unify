// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

/*	LinkList allows the creation of a dynamically sized list.
 *		LinkList--->QList
 *
 *	Dynamically sizable link list. It uses Query objects to traverse the list.
 *
 */
#pragma once

#include <unify/TLink.h>
#include <unify/Unify.h>
#include <unify/Flags.h>
#include <unify/List.h>


namespace unify 
{
	#define LINKLIST_SORT			FLAG01
	#define LINKLIST_SORTREVERSE	(FLAG01|FLAG02)
	#define LINKLIST_SORT_BYVALUE	FLAG03
	#define LINKLIST_SORT_BYNAME	FLAG04
	#define LINKLIST_FORCENAMES		FLAG05	// Forces list to use names


	template< typename T >
	class LinkList : public QList< T >
	{
	public:
		LinkList();
		~LinkList();

		unsigned int Count();

		void Clear();
		T * AddItem( T * item, std::string sName = "" );
		T * AddItem( T * item, unsigned int uFlags, std::string sName = "" );
		T * AddItem( T * item, float fSortValue, std::string sName = "" );
		T * AddItem( T * item, unsigned int uFlags, float fSortValue, std::string sName = "" );

		bool DeleteItem( std::string sName );
		bool DeleteItem( TLink< T > * &pLink );
		bool DeleteItem( T * pItem );

		void SetLisFlags( unsigned int uFlags );
		unsigned int GetLisFlags();

		const std::string Name( const T * pItem );
		const std::string Name( unsigned int uIndex );

		T * Find( std::string sName );
		T * Find( Query< T > * pQuery, std::string sName );

		T * GotoFirst( Query< T > * pQuery );
		T * GotoLast( Query< T > * pQuery );
		T * GotoPrevious( Query< T > * pQuery );
		T * GotoNext( Query< T > * pQuery );

		T * Current();

		T * Item( unsigned int uIndex );

	protected:
		TLink< T > * m_pFirst;
		TLink< T > * m_pLast;

		unsigned int m_uCount;
		unsigned int m_uLisFlags;
	};

	#include <unify/LinkList.inl>
}
