// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <unify/V2.h>

namespace unify
{
	/// <summary>
	/// A rectangle.
	/// </summary>
	template< typename T = int >
	class Rect
	{
	public:
		T left;
		T top;
		T right;
		T bottom;

		Rect();
		Rect( T l, T t, T r, T b );
		Rect( const V2< T > & ul, const V2< T > & dr );
        Rect( const V2< T > & ul, const Size< T > & size );

		T Width() const;
		T Height() const;

		V2< T > UL() const;
		V2< T > UR() const;
		V2< T > DL() const;
		V2< T > DR() const;

		Size< T > Size() const;

		void And( const Rect< T > & rect );

		Rect & operator += ( const Rect< T > & rect );
		Rect & operator -= ( const Rect< T > & rect );
		Rect operator + ( const Rect< T > & rect ) const;
		Rect operator - ( const Rect< T > & rect ) const;
		const Rect & operator = ( const Rect< T > & rect );

		void SizeTo( T width, T height );
		bool IsIn( T x, T y ) const;
		bool IsIn( const V2< T > & point ) const;
		void MoveTo( T x, T y );
		void MoveBy( T x, T y );
		void MoveTo( const V2< T > & pVec );
		void MoveBy( const V2< T > & pVec );
		void AddToRegion( const V2< T > & pVec );
	};
	#include <unify/Rect.inl>
}
