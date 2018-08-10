// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

template< typename T >
inline Query<T>::Query()
{
	m_pCurrent = 0;
}

template< typename T >
inline std::string Query<T>::Name()
{
	return m_pCurrent->m_sName;
}

template< typename T >
inline float Query<T>::SortValue()
{
	return m_pCurrent->m_fSortValue;
}
