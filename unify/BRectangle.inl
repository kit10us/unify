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


template<typename T>
unify::BRectangle< T >::BRectangle()
	: BRectangle({}, {})
{
}

template<typename T>
unify::BRectangle< T >::BRectangle( const unify::V2<T>& inUL, const unify::V2<T>& inDR )
	: ul{ inUL }
	, dr{ inDR }
{
}

template<typename T>
unify::BRectangle<T> unify::BRectangle< T >::operator * ( const unify::V2<T>& multiplicand )
{
	return BRectangle< T >( ul * multiplicand, dr * multiplicand );
}

template<typename T>
bool unify::BRectangle< T >::operator == (const BRectangle& other) const
{
	return ul == other.ul && dr == other.dr;
}

template<typename T>
bool unify::BRectangle< T >::Normalize()
{
	bool changed = false;

	if( ul.x > dr.x )
	{
		std::swap( ul.x, dr.x );
		changed = true;
	}

	if( ul.y > dr.y )
	{
		std::swap( ul.y, dr.y );
		changed = true;
	}

	return changed;
}

template<typename T>
unify::BRectangle< T > unify::BRectangle< T >::Normalized() const
{
	unify::BRectangle< T > normalized = *this;
	normalized.Normalize();
	return normalized;
}

template<typename T>
void unify::BRectangle< T >::GenerateCorners( unify::V2<T>* bounds )
{
	bounds[ 0 ] = unify::V2< T >( ul.x, ul.y );
	bounds[ 1 ] = unify::V2< T >( dr.x, ul.y );
	bounds[ 2 ] = unify::V2< T >( ul.x, dr.y );
	bounds[ 3 ] = unify::V2< T >( dr.x, dr.y );
}

template<typename T>
void unify::BRectangle<T>::Add( const unify::V2<T>& point )
{
	if( point.x > dr.x ) dr.x = point.x;
	else if( point.x < ul.x ) ul.x = point.x;

	if( point.y > dr.y ) dr.y = point.y;
	else if( point.y < ul.y ) ul.y = point.y;
}

template<typename T>
bool unify::BRectangle<T>::Contains( const unify::V2<T>& point )
{
	if( ( point.x < dr.x && point.x > ul.x ) && ( point.y < dr.y && point.y > ul.y ) )
	{
		return true;
	}

	return false;
}

template<typename T>
bool unify::BRectangle<T>::Contains( const unify::BRectangle<T>& brect )
{
	if( ( brect.ul.x >= ul.x && brect.dr.x <= dr.x ) && ( brect.ul.y >= ul.y && brect.dr.y <= dr.y ) )
	{
		return true;
	}

	return false;
}

template<typename T>
const unify::V2<T>unify::BRectangle<T>::Size()
{
	return unify::V2< T >( dr - ul );
}
