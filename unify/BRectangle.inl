/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


template< typename T >
unify::BRectangle::BRectangle()
	: BRectangle({}, {})
{
}

template< typename T >
unify::BRectangle::BRectangle( const unify::V2< T > & inInf, const unify::V2< T > & inSup )
	: inf{ inInf }
	, sup{ inSup }
{
}

template< typename T >
unify::BRectangle< T > unify::BRectangle::operator * ( const unify::V2< T > & multiplicand )
{
	return BRectangle< T >( inf * multiplicand, sup * multiplicand );
}

template< typename T >
void BRectangle::GenerateCorners( unify::V2< T > * bounds )
{
	bounds[ 0 ] = unify::V2< T >( inf.x, inf.y );
	bounds[ 1 ] = unify::V2< T >( sup.x, inf.y );
	bounds[ 2 ] = unify::V2< T >( inf.x, sup.y );
	bounds[ 3 ] = unify::V2< T >( sup.x, sup.y );
}

template< typename T >
void BRectangle::Add( const unify::V2< T > & point )
{
	if( point.x > sup.x ) sup.x = point.x;
	else if( point.x < inf.x ) inf.x = point.x;

	if( point.y > sup.y ) sup.y = point.y;
	else if( point.y < inf.y ) inf.y = point.y;
}

template< typename T >
bool BRectangle::Contains( const unify::V2< T > & point )
{
	if( ( point.x < sup.x && point.x > inf.x ) && ( point.y < sup.y && point.y > inf.y ) )
	{
		return TRUE;
	}

	return FALSE;
}

template< typename T >
unify::BRectangle< T > & unify::BRectangle::Add( const unify::BRectangle< T > & boundingSquare )
{
	if( boundingSquare.sup.x > sup.x ) sup.x = boundingSquare.sup.x;
	if( boundingSquare.inf.x < inf.x ) inf.x = boundingSquare.inf.x;

	if( boundingSquare.sup.y > sup.y ) sup.y = boundingSquare.sup.y;
	if( boundingSquare.inf.y < inf.y ) inf.y = boundingSquare.inf.y;

	return *this;
}

template< typename T >
const unify::V2< T > unify::BRectangle::Size()
{
	return unify::V2< T >( sup - inf );
}


