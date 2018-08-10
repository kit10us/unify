/* Copyright (c) 2002 - 2019, Quentin S. Smith
 * All Rights Reserved
 */

template< typename T >
Optional< T >::Optional()
{
}

template< typename T >
Optional< T >::Optional( const T & value )
	: m_thing( new Keeper( value ) )
{
}

template< typename T >
Optional< T >::~Optional()
{
	m_thing.reset();
}

template< typename T >
const T & Optional< T >::operator()() const
{
	if ( m_thing.empty() )
	{
		throw new unify::Exception( "Optional referenced when empty!" );
	}
	return m_thing.value;
}