// Copyright (c) 2002 - 2019 Kit10 Studios LLC
// All Rights Reserved

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

