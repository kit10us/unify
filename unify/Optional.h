// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/Exception.h>
#include <memory>

namespace unify
{
	template< typename T >
	class Optional
	{
	public:
		Optional();
		Optional( const T & value );
		~Optional();

		const T & operator()() const;

	private:
		struct Keeper
		{
			Keeper( const T & t )
				: value( t )
			{	
			}
			T value;
		};

		std::shared_ptr< Keeper > m_thing;
	};
	#include <unify/Optional.inl>
}
