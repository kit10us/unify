// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

/////
// TLink
/////

template< typename T >
TLink< T >::TLink()
	: m_item{ nullptr }
	, m_previous{ nullptr }
	, m_next{ nullptr }
{
}

template< typename T >
TLink< T >::TLink( T * item, std::string name )
	: m_item{ item }
	, m_name{ name }
	, m_previous{ nullptr }
	, m_next{ nullptr }
{
}

template< typename T >
TLink< T >::~TLink()
{
	m_item = nullptr;
	m_previous = nullptr;
	m_next = nullptr;
}

template< typename T >
std::string TLink< T >::Name() const
{
	return m_name;
}

template< typename T >
T * TLink< T >::Item() const
{
	return m_item.get();
}

template< typename T >
TLink< T > * TLink< T >::Previous()
{
	return m_previous;
}

template< typename T >
const TLink< T > * TLink< T >::Previous() const
{
	return m_previous;
}

template< typename T >
TLink< T > * TLink< T >::Next()
{
	return m_next;
}

template< typename T >
const TLink< T > * TLink< T >::Next() const
{
	return m_next;
}
