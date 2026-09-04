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


#include <unify/DataLock.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/Cast.h>
#include <cassert>
#include <cstring>

namespace unify
{
	inline
	bool IsCompatible( DataLockAccess a, DataLockAccess b ) noexcept
	{
		switch( a )
		{
		case DataLockAccess::None: // Any access supports no access.
			return true;

		case DataLockAccess::Readonly:
			return b == DataLockAccess::Readonly || b == DataLockAccess::ReadWrite;

		case DataLockAccess::Writeonly:
			return b == DataLockAccess::Writeonly || b == DataLockAccess::ReadWrite;
		
		case DataLockAccess::ReadWrite:
			return b == DataLockAccess::ReadWrite;

		default:
			return false;
		}
	}

	inline
	bool HasReadAccess( DataLockAccess access )
	{
		return IsCompatible( DataLockAccess::Readonly, access );
	}

	inline
	bool HasWriteAccess( DataLockAccess access )
	{
		return IsCompatible( DataLockAccess::Writeonly, access );
	}

	template<typename T>
	inline std::optional<DataLockAccess> FromString( std::string_view access ) 
	{
		using unify::String::StringIs;

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
		else
		{
			return std::nullopt;
		}
	}


	template<>
	inline
	std::optional<std::string> ToString( DataLockAccess access ) noexcept
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

		return std::nullopt;
	}

	/*
	inline
	std::optional<std::string> ToString( unify::DataLockAccess type ) noexcept
	{
		return ToString( type );
	}

	template<>
	inline
	std::optional<unify::DataLockAccess> FromString( std::string type ) noexcept
	{
		return FromString<DataLockAccess>( type );
	}
	*/


	template<typename T>
	DataLock<T>::DataLock()
	: m_data( 0 )
	, m_stride( 0 )
	, m_count( 0 )
	, m_sizeInBytes( 0 )
	, m_slot( 0 )
	{
	}

	template<typename T>
	DataLock<T>::DataLock( void * data, size_t stride, size_t count, DataLockAccess type, size_t slot )
	{
		SetLock( data, stride, count, type, slot );
	}

	template<typename T>
	DataLock<T>::DataLock( void * data, size_t sizeInBytes, DataLockAccess type, size_t slot )
	{
		SetLock( data, sizeInBytes, type, slot );
	}

	template<typename T>
	DataLock<T>::~DataLock()
	{
	}

	template<typename T>
	void DataLock<T>::SetLock( void * data, size_t stride, size_t count, DataLockAccess type, size_t slot )
	{
		m_data = data;
		m_stride = stride;
		m_count = count;
		m_sizeInBytes = stride * count;
		m_type = type;
		m_slot = slot;
	} 

	template<typename T>
	void DataLock<T>::SetLock( void * data, size_t sizeInBytes, DataLockAccess type, size_t slot )
	{
		m_data = data;
		m_stride = sizeInBytes;
		m_count = 1;
		m_sizeInBytes = sizeInBytes;
		m_type = type;
		m_slot = slot;
	}

	template<typename T>
	DataLockAccess DataLock<T>::GetLockType() const
	{
		return m_type;
	}

	template<typename T>
	size_t DataLock<T>::Count() const
	{
		return m_count;
	}

	template<typename T>
	size_t DataLock<T>::Stride() const
	{
		return m_stride;
	}

	template<typename T>
	size_t DataLock<T>::GetSizeInBytes() const
	{
		return m_sizeInBytes;
	}

	template<typename T>
	size_t DataLock<T>::Slot() const
	{
		return m_slot;
	}

	template<typename T>
	void DataLock<T>::Invalidate()
	{
		m_data = 0;
		m_stride = 0;
		m_count = 0;
		m_slot = 0;
	}

	template<typename T>
	bool DataLock<T>::CopyBytesFrom( const void * source, size_t offset, size_t byteCount )
	{
		if( offset + byteCount > m_sizeInBytes )
		{
			return false;
		}
		memcpy( ((unsigned char*)m_data) + offset, source, byteCount );
		return true;
	}

	template<typename T>
	bool DataLock<T>::CopyItemFrom( const void * source, size_t indexTo )
	{
		if( indexTo >= m_count )
		{
			return false;
		}
		void * dest = ((unsigned char*)m_data) + indexTo * m_stride;
		memcpy( dest, source, m_stride );
		return true;
	}

	template<typename T>
	bool DataLock<T>::CopyItemFromTo( size_t indexFrom, size_t indexTo )
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

	
	template < typename T >
	T * DataLock<T>::GetData()
	{
		if ( !HasReadAccess( m_type ) || !HasWriteAccess( m_type ) )
		{
			throw unify::Exception( "Attempted to access " + ToString( m_type ) + " for " + ToString( DataLockAccess::ReadWrite ) + " access!" );
		}
		return m_data;
	}

	template < typename T >
	const T * DataLock<T>::GetDataReadOnly() const
	{
		if ( !HasReadAccess( m_type ) )
		{
			auto type = ToString(m_type);
			if (!type)
			{
				return nullptr;
			}

			auto access = ToString(DataLockAccess::ReadWrite);
			if (!access)
			{
				return nullptr; // SAS TODO: Needs to actually use result.
			}
			//Failed{"Attempted to access " + *ToString( m_type ) + " for " + *ToString( DataLockAccess::ReadWrite ) + " access!"};
			return nullptr;
		}
		return (T*)m_data;
	}

	template < typename T >
	T * DataLock<T>::GetItem( size_t index )
	{
		if (index >= m_count)
		{
			throw unify::Exception( "Attempted to access index out of range! (" + *unify::ToString( index ) + " to " + *unify::Cast< std::string >( m_count ) + ")" );
		}

		if ( !HasReadAccess( m_type ) || !HasWriteAccess( m_type )  )
		{
			throw unify::Exception( "Attempted to access " + DataLockAccess::ToString( m_type ) + " for " + DataLockAccess::ToString( DataLockAccess::ReadWrite ) + " access!" );
		}

		return m_data + m_stride * index;
	}

	template < typename T >
	const T * DataLock<T>::GetItemReadonly( size_t index ) const
	{
		if (index >= m_count)
		{
			throw unify::Exception( "Attempted to access index out of range! (" + ToString( index ) + " to " + unify::Cast< std::string >( m_count ) + ")" );
		}

		if (!HasReadAccess( m_type ))
		{
			throw unify::Exception( "Attempted to access READONLY data for write!" );
		}

		return m_data + m_stride * index;
	}
}