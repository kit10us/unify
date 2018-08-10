// Copyright (c) 2002 - 2019 Evil Quail LLC
// All Rights Reserved

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

