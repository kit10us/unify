/* Copyright (c) 2002 - 2019, Evil Quail LLC
 * All Rights Reserved
 */

#include <unify/DataLock.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <string>
#include <cassert>

using namespace unify;

DataLock::DataLock()
: m_data( 0 )
, m_stride( 0 )
, m_count( 0 )
, m_sizeInBytes( 0 )
, m_slot( 0 )
{
}

DataLock::DataLock( void * data, unsigned int stride, unsigned int count, bool readonly, size_t slot )
{
	SetLock( data, stride, count, readonly, slot );
}

DataLock::DataLock( void * data, unsigned int sizeInBytes, bool readonly, size_t slot )
{
	SetLock( data, sizeInBytes, readonly, slot );
}

DataLock::~DataLock()
{
}

void DataLock::SetLock( void * data, unsigned int stride, unsigned int count, bool readonly, size_t slot )
{
	m_data = data;
	m_stride = stride;
	m_count = count;
	m_sizeInBytes = stride * count;
	m_readonly = readonly;
	m_slot = slot;
}

void DataLock::SetLock( void * data, unsigned int sizeInBytes, bool readonly, size_t slot )
{
	m_data = data;
	m_stride = sizeInBytes;
	m_count = 1;
	m_sizeInBytes = sizeInBytes;
	m_readonly = readonly;
	m_slot = slot;
}

void * DataLock::GetData()
{
	if( m_readonly )
	{
		return 0;
	}
	return m_data;
}

void * DataLock::GetItem( unsigned int index )
{
	if( index >= m_count )
	{
		assert( 0 );
		throw unify::Exception( "Attempted to access index out of range! (" + unify::Cast< std::string >( index ) + " to " + unify::Cast< std::string >( m_count ) +")" );
	}

	if ( m_readonly )
	{
		assert( 0 );
		throw unify::Exception( "Attempted to access READONLY data for write!" );
	}

	return ((unsigned char*)m_data) + m_stride * index;
}

const void * DataLock::GetDataReadOnly() const
{
	return m_data;
}

const void * DataLock::GetItemReadOnly( unsigned int index ) const
{
	if( index >= m_count )
	{
		return 0;
	}

	return ((unsigned char*)m_data) + m_stride * index;
}

unsigned int DataLock::Count() const
{
	return m_count;
}

unsigned int DataLock::Stride() const
{
	return m_stride;
}

unsigned int DataLock::GetSizeInBytes() const
{
	return m_sizeInBytes;
}

size_t DataLock::Slot() const
{
	return m_slot;
}

void DataLock::Invalidate()
{
	m_data = 0;
	m_stride = 0;
	m_count = 0;
	m_slot = 0;
}

bool DataLock::CopyBytesFrom( const void * source, unsigned int offset, unsigned int byteCount )
{
	if( offset + byteCount > m_sizeInBytes )
	{
		return false;
	}
	memcpy( ((unsigned char*)m_data) + offset, source, byteCount );
	return true;
}

bool DataLock::CopyItemFrom( const void * source, unsigned int indexTo )
{
	if( indexTo >= m_count )
	{
		return false;
	}
	void * dest = ((unsigned char*)m_data) + indexTo * m_stride;
	memcpy( dest, source, m_stride );
	return true;
}

bool DataLock::CopyItemFromTo( unsigned int indexFrom, unsigned int indexTo )
{
	if( indexFrom == indexTo )
	{
		return true;
	}
	if( indexFrom >= m_count )
	{
		return false;
	}

	void * source = ((unsigned char*)m_data) + (indexFrom * m_stride);
	return CopyItemFrom( source, indexTo );
}
