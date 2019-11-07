// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

template< typename T >
Rect< T >::Rect()
: left( 0 )
, top( 0 )
, right( 0 )
, bottom( 0 )
{
}

template< typename T >
Rect< T >::Rect( T l, T t, T r, T b )
: left( l )
, top( t )
, right( r )
, bottom( b )
{
}

template< typename T >
Rect< T >::Rect( const V2< T > & vUL, const V2< T > & vDR )
: left( vUL.x )
, top( vUL.y )
, right( vDR.x )
, bottom( vDR.y )
{
}

template< typename T >
Rect< T >::Rect( const V2< T > &vUL, const unify::Size< T > &size )
: left( vUL.x )
, top( vUL.y )
, right( vUL.x + size.width )
, bottom( vUL.y + size.height )
{
}

template< typename T >
T Rect< T >::Width() const
{
	return right - left;
}

template< typename T >
T Rect< T >::Height() const
{
	return bottom - top;
}

template< typename T >
V2< T > Rect< T >::UL() const
{
	return V2< T >( left, top );
}

template< typename T >
V2< T > Rect< T >::UR() const
{
	return V2< T >( right, top );
}

template< typename T >
V2< T > Rect< T >::DL() const
{
	return V2< T >( left, bottom );
}

template< typename T >
V2< T > Rect< T >::DR() const
{	
	return V2< T >( right, bottom );
}

template< typename T >
Size< T > Rect< T >::Size() const
{
	return{ right - left, bottom - top };
}

template< typename T >
void Rect< T >::And( const Rect< T > & rect )
{
	if( rect.left > left ) left = rect.left;
	if( rect.right < right ) right = rect.right;
	if( rect.top > top ) top = rect.top;
	if( rect.bottom < bottom ) bottom = rect.bottom;
}

template< typename T >
Rect< T > & Rect< T >::operator += ( const Rect< T > & rect )
{
	left += rect.left;
	top += rect.top;
	right += rect.right;
	bottom += rect.bottom;
	return *this;
}

template< typename T >
Rect< T > & Rect< T >::operator -= ( const Rect< T > & rect )
{
	left -= rect.left;
	top -= rect.top;
	right -= rect.right;
	bottom -= rect.bottom;
	return *this;
}

template< typename T >
Rect< T > Rect< T >::operator + ( const Rect< T > & rect ) const
{
	return Rect< T >( 
		left + rect.left, right + rect.right,
		top + rect.top, bottom + rect.bottom 
		);		
}

template< typename T >
Rect< T > Rect< T >::operator - ( const Rect< T > & rect ) const
{
	return Rect< T >( 
		left - rect.left, right - rect.right,
		top - rect.top, bottom - rect.bottom );		
}

template< typename T >
const Rect< T > & Rect< T >::operator = ( const Rect< T > & rect )
{
	left = rect.left;
	right = rect.right;
	top = rect.top;
	bottom = rect.bottom;
	return *this;
}

template< typename T >
void Rect< T >::SizeTo( T lWidth, T lHeight )
{
	right = left + lWidth;
	bottom = top + lHeight;
}

template< typename T >
bool Rect< T >::IsIn( T x, T y ) const 
{
	if( x >= left && x <= right && y >= top && y <= bottom )
	{
		return true;
	}
	return false;
}

template< typename T >
bool Rect< T >::IsIn( const V2< T > & point ) const 
{
	if( point.x >= left && point.x <= right && point.y >= top && point.y <= bottom )
	{
		return true;
	}
	return false;
}

template< typename T >
void Rect< T >::MoveTo( T x, T y )
{
	right += x - left;
	bottom += y - top;
	left = x;
	top = y;
}

template< typename T >
void Rect< T >::MoveBy( T x, T y )
{
	left += x;
	top += y;
	right += x;
	bottom += y;
}

template< typename T >
void Rect< T >::MoveTo( const V2< T > & vTo )
{
	MoveTo( vTo.x, vTo.y );
}

template< typename T >
void Rect< T >::MoveBy( const V2< T > & vBy )
{
	MoveBy( vBy.x, vBy.y );
}

template< typename T >
void Rect< T >::AddToRegion( const V2< T > & v2 )
{
	if( v2.x < left ) left = v2.x;
	if( v2.x > right ) right = v2.x;
	if( v2.y < top ) top = v2.y;
	if( v2.y > bottom ) bottom = v2.y;
}
