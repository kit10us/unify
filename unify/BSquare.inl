/* Copyright (c) 2002 - 2019, Quentin S. Smith
 * All Rights Reserved
 */

template< typename T >
unify::BSquare::BSquare()
{
	Initialize();
}

template< typename T >
unify::BSquare::BSquare( const unify::V2< T > & inInf, const unify::V2< T > & inSup )
{
	Initialize( inInf, inSup );
}

template< typename T >
unify::BSquare< T > unify::BSquare::operator * ( const unify::V2< T > & multiplicand )
{
	return BSquare< T >( inf * multiplicand, sup * multiplicand );
}

// Generate the 4 vertices that make up the bounding square...
template< typename T >
void BSquare::GenerateCorners( unify::V2< T > * bounds )
{
	bounds[ 0 ] = unify::V2< T >( inf.x, inf.y );
	bounds[ 1 ] = unify::V2< T >( sup.x, inf.y );
	bounds[ 2 ] = unify::V2< T >( inf.x, sup.y );
	bounds[ 3 ] = unify::V2< T >( sup.x, sup.y );
}

template< typename T >
void BSquare::Initialize( const unify::V2< T > & _inf, const unify::V2< T > & _sup )
{
	inf = _inf;
	sup = _sup;
}

template< typename T >
void BSquare::AddPoint( const unify::V2< T > & point )
{
	if( point.x > sup.x ) sup.x = point.x;
	else if( point.x < inf.x ) inf.x = point.x;

	if( point.y > sup.y ) sup.y = point.y;
	else if( point.y < inf.y ) inf.y = point.y;
}

template< typename T >
bool BSquare::ContainsPoint( const unify::V2< T > & point )
{
	if( ( point.x < sup.x && point.x > inf.x ) && ( point.y < sup.y && point.y > inf.y ) )
	{
		return TRUE;
	}

	return FALSE;
}

template< typename T >
unify::BSquare< T > & unify::BSquare::AddBSquare( const unify::BSquare< T > & boundingSquare )
{
	if( boundingSquare.sup.x > sup.x ) sup.x = boundingSquare.sup.x;
	if( boundingSquare.inf.x < inf.x ) inf.x = boundingSquare.inf.x;

	if( boundingSquare.sup.y > sup.y ) sup.y = boundingSquare.sup.y;
	if( boundingSquare.inf.y < inf.y ) inf.y = boundingSquare.inf.y;

	return *this;
}

template< typename T >
const unify::V2< T > unify::BSquare::Size()
{
	return unify::V2< T >( sup - inf );
}


