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


#include <unify/FrameSetInstance.h>
#include <unify/Exception.h>
#include <stack>
#include <cassert>

using namespace unify;

FrameSetInstance::FrameSetInstance()
	: m_frameSet{ 0 }
{
}

FrameSetInstance::FrameSetInstance( const FrameSet * frameSet )
: m_frameSet( frameSet )
, m_models( frameSet->m_models )
, m_locals( frameSet->m_locals )
, m_dirty( false )
{
}

FrameSetInstance::FrameSetInstance( const FrameSetInstance & frameSetInstance )
: m_frameSet( frameSetInstance.m_frameSet )
, m_models( frameSetInstance.m_models )
, m_locals( frameSetInstance.m_locals )
, m_dirty( frameSetInstance.m_dirty )
{
}

FrameSetInstance::~FrameSetInstance()
{
}

FrameSetInstance & FrameSetInstance::operator=( const FrameSetInstance & frameSetInstance )
{
	m_frameSet = frameSetInstance.m_frameSet;
	m_models = frameSetInstance.m_models;
	m_locals = frameSetInstance.m_locals;
	m_dirty = frameSetInstance.m_dirty;
	return *this;
}

const FrameSet * FrameSetInstance::GetFrameSet() const
{
	return m_frameSet;
}

size_t FrameSetInstance::Count() const
{
	return m_frameSet->Count();
}

void FrameSetInstance::Reset( const FrameSet * frameSet )
{
	if ( frameSet )
	{
		m_frameSet = frameSet;
	}

	m_models = m_frameSet->m_models;
	m_locals = m_frameSet->m_locals;
	m_dirty = false;
}

bool FrameSetInstance::Exists( std::string name ) const
{
	return m_frameSet->Exists( name );
}

size_t FrameSetInstance::Find( std::string name ) const
{
	return m_frameSet->Find( name );
}

const Matrix & FrameSetInstance::Model( size_t index ) const
{
	assert( index < Count() );
	return m_models[ index ];
}

const Matrix & FrameSetInstance::Local( size_t index ) const
{
	assert( index < Count() );
	assert( ! m_dirty ); // Typically it is a defect to get a dirty local.
	return m_locals[ index ];
}

const Matrix & FrameSetInstance::OriginalModel( size_t index ) const
{
	return m_frameSet->Model( index );
}

const Matrix & FrameSetInstance::OriginalLocal( size_t index ) const
{
	return m_frameSet->Local( index );
}

void FrameSetInstance::Transform( size_t index, const Matrix & transform )
{
	assert( index < Count() );
	m_models[ index ] *= transform;
	m_dirty = true;
}

void FrameSetInstance::UpdateLocals()
{
	if( m_dirty )
	{
		for( size_t i = 0, end = Count(); i != end; ++i )
		{
			const size_t & parentIndex = m_frameSet->m_parentIndex[ i ];
			if( i == parentIndex )
			{
				m_locals[ i ] = m_models[ i ];
			}
			else
			{
				const Matrix & parentLocal = m_locals[ parentIndex ];
				m_locals[ i ] = parentLocal * m_models[ i ];
			}
		}
		m_dirty = false;
	}
}

bool FrameSetInstance::IsDirty() const
{
	return m_dirty;
}
