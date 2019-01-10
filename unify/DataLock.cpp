/* Copyright (c) 2002 - 2019, Evil Quail LLC
 * All Rights Reserved
 */

#include <unify/DataLock.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/String.h>
#include <cassert>

using namespace unify;

DataLock::TYPE DataLock::FromString( std::string type )
{
	using unify::string::StringIs;

	if ( StringIs( type, "None" ) )
	{
		return DataLock::None;
	}
	else if ( StringIs( type, "Readonly" ) )
	{
		return DataLock::Readonly;
	}
	else if ( StringIs( type, "Writeonly" ) )
	{
		return DataLock::Writeonly;
	}
	else if ( StringIs( type, "ReadWrite" ) )
	{
		return DataLock::ReadWrite;
	}

	throw unify::Exception( "Invalid DataLock type \"" + type + "\"!" );
}
std::string DataLock::ToString( TYPE type )
{
	switch( type )
	{
	case DataLock::None:
		return "None";
	case DataLock::Readonly:
		return "Readonly";
	case DataLock::Writeonly:
		return "Writeonly";
	case DataLock::ReadWrite:
		return "ReadWrite";
	}

	throw unify::Exception( "Invalid DataLock type!" );
}

DataLock::DataLock()
: m_data( 0 )
, m_stride( 0 )
, m_count( 0 )
, m_sizeInBytes( 0 )
, m_slot( 0 )
{
}

DataLock::DataLock( void * data, unsigned int stride, unsigned int count, TYPE type, size_t slot )
{
	SetLock( data, stride, count, type, slot );
}

DataLock::DataLock( void * data, unsigned int sizeInBytes, TYPE type, size_t slot )
{
	SetLock( data, sizeInBytes, type, slot );
}

DataLock::~DataLock()
{
}

void DataLock::SetLock( void * data, unsigned int stride, unsigned int count, TYPE type, size_t slot )
{
	m_data = data;
	m_stride = stride;
	m_count = count;
	m_sizeInBytes = stride * count;
	m_type = type;
	m_slot = slot;
}

void DataLock::SetLock( void * data, unsigned int sizeInBytes, TYPE type, size_t slot )
{
	m_data = data;
	m_stride = sizeInBytes;
	m_count = 1;
	m_sizeInBytes = sizeInBytes;
	m_type = type;
	m_slot = slot;
}

DataLock::TYPE DataLock::GetType() const
{
	return m_type;
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
