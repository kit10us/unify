// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>

namespace unify
{
	template< typename T >
	class BSquare
	{
	public:
		V2< T > sup;
		V2< T > inf;

		BSquare();
		BSquare( const V2< T > & inf, const V2< T > & sup );

		BSquare< T > operator * ( const V2< T > & muliplcand );
		
		void GenerateCorners( V2< T > * bounds );
		void Initialize( const V2< T > & inf = V2< T >::Zero(), const V2< T > & sup = V2< T >::Zero() );
		void AddPoint( const V2< T > & point );
		BSquare & AddBSquare( const BSquare< T > & boundingSquare );
		bool ContainsPoint( const V2< T > & point );
		const V2< T > Size();
	};
	#include <unify/BSquare.inl>
}

