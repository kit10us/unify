/* Copyright (c) 2002 - 2019, Evil Quail LLC
 * All Rights Reserved
 */

#include <unify/DataLock.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/String.h>
#include <cassert>

using namespace unify;

bool DataLockAccess::ReadAccess( TYPE access )
{
	return Compatible( Readonly, access );
}

bool DataLockAccess::WriteAccess( TYPE access )
{
	return Compatible( Writeonly, access );
}

bool DataLockAccess::Compatible( TYPE a, TYPE b )
{
	switch( a )
	{
	case None: // Any access supports no access.
		return true;

	case Readonly:
		return b == Readonly || b == ReadWrite;

	case DataLockAccess::Writeonly:
		return b == Writeonly || b == ReadWrite;
	
	case DataLockAccess::ReadWrite:
		return b == ReadWrite;

	default:
		throw unify::Exception( "Invalid DataLockAccess type!" );
	}
}

DataLockAccess::TYPE DataLockAccess::FromString( std::string access )
{
	using unify::string::StringIs;

	if ( StringIs( access, "None" ) )
	{
		return DataLockAccess::None;
	}
	else if ( StringIs( access, "Readonly" ) )
	{
		return DataLockAccess::Readonly;
	}
	else if ( StringIs( access, "Writeonly" ) )
	{
		return DataLockAccess::Writeonly;
	}
	else if ( StringIs( access, "ReadWrite" ) )
	{
		return DataLockAccess::ReadWrite;
	}

	throw unify::Exception( "Invalid DataLockAccess\"" + access + "\"!" );
}
std::string DataLockAccess::ToString( TYPE access )
{
	switch( access )
	{
	case DataLockAccess::None:
		return "None";
	case DataLockAccess::Readonly:
		return "Readonly";
	case DataLockAccess::Writeonly:
		return "Writeonly";
	case DataLockAccess::ReadWrite:
		return "ReadWrite";
	}

	throw unify::Exception( "Invalid DataLockAccess type!" );
}

template<> 
std::string unify::Cast( unify::DataLockAccess::TYPE type )
{
	return DataLockAccess::ToString( type );
}

template<> unify::DataLockAccess::TYPE unify::Cast( std::string type )
{
	return DataLockAccess::FromString( type );
}


DataLock::DataLock()
: m_data( 0 )
, m_stride( 0 )
, m_count( 0 )
, m_sizeInBytes( 0 )
, m_slot( 0 )
{
}

DataLock::DataLock( void * data, unsigned int stride, unsigned int count, DataLockAccess::TYPE type, size_t slot )
{
	SetLock( data, stride, count, type, slot );
}

DataLock::DataLock( void * data, unsigned int sizeInBytes, DataLockAccess::TYPE type, size_t slot )
{
	SetLock( data, sizeInBytes, type, slot );
}

DataLock::~DataLock()
{
}

void DataLock::SetLock( void * data, unsigned int stride, unsigned int count, DataLockAccess::TYPE type, size_t slot )
{
	m_data = data;
	m_stride = stride;
	m_count = count;
	m_sizeInBytes = stride * count;
	m_type = type;
	m_slot = slot;
}

void DataLock::SetLock( void * data, unsigned int sizeInBytes, DataLockAccess::TYPE type, size_t slot )
{
	m_data = data;
	m_stride = sizeInBytes;
	m_count = 1;
	m_sizeInBytes = sizeInBytes;
	m_type = type;
	m_slot = slot;
}

DataLockAccess::TYPE DataLock::GetType() const
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
