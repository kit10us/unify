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


#include <unify/FrameSet.h>
#include <unify/Exception.h>
#include <stack>
#include <cassert>

using namespace unify;

FrameSet::FrameSet()
{
}

FrameSet::~FrameSet()
{
}

size_t FrameSet::Add( Matrix model, size_t parent, std::string name )
{
	// Assert valid connectivity.
	size_t index = m_parentIndex.size();
	assert( parent <= index );

	m_models.push_back( model );
	m_parentIndex.push_back( parent );
	if( ! name.empty() )
	{
		m_nameToIndex[ name ] = index;
		m_indexToName[ index ] = name;
	}

	// Build local matrix.
	if( parent == index ) // No parent.
	{
		m_locals.push_back( model );
	}
	else
	{
		m_locals.push_back( m_locals[ parent ] * model );
	}

	return index;
}

bool FrameSet::Exists( std::string name ) const
{
	std::map< std::string, size_t >::const_iterator itr = m_nameToIndex.find( name );
	bool found( itr == m_nameToIndex.end() );
	return found;
}

size_t FrameSet::Find( std::string name ) const
{
	std::map< std::string, size_t >::const_iterator itr = m_nameToIndex.find( name );
	if( itr == m_nameToIndex.end() )
	{
		throw unify::Exception( "Frame not found! (" + name + ")" );
	}
	else
	{
		return itr->second;
	}
}

size_t FrameSet::Count() const
{
	return m_parentIndex.size();
}

std::string FrameSet::Name( size_t index ) const
{
	std::map< size_t, std::string >::const_iterator itr = m_indexToName.find( index );
	if( itr == m_indexToName.end() )
	{
		return "";
	}

	return itr->second;
}

const Matrix & FrameSet::Local( size_t index ) const
{
	assert( index < Count() );
	return m_locals[ index ];
}

const Matrix & FrameSet::Model( size_t index ) const
{
	assert( index < Count() );
	return m_models[ index ];
}

void FrameSet::ForEach( ForEachFunctor & functor ) const
{
	std::stack< size_t > depth;
	for( size_t index = 0, end = m_parentIndex.size(); index != end; ++index )
	{
		// If our parent isn't immediately before us, then we need to regress.
		if( ! depth.empty() && m_parentIndex[ index ] != index - 1 )
		{
			// Reduce our depth until our parent is on the top of the stack or we hit the bottom.
			while( ! depth.empty() && depth.top() != m_parentIndex[ index ] )
			{
				depth.pop();
			}
		}

		functor( depth.size(), index );
		depth.push( index );
	}
}
