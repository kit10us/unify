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


#pragma once

#include <unify/Cast.h>
#include <unify/Exception.h>

namespace unify
{
	enum class DataLockAccess
	{
		None,
		Readonly,
		Writeonly,
		ReadWrite
	};

	/// @brief
	/// Returns true if the access mode supports read access.
	inline 
	bool ReadAccess( DataLockAccess access ) noexcept;

	/// @brief
	/// Returns true if the access mode supports write access.
	inline 
	bool WriteAccess( DataLockAccess access ) noexcept;

	/// @brief 
	/// Retruns true if access 'a' supports the access specified with 'b'.
	inline
	bool Compatible( DataLockAccess a, DataLockAccess b ) noexcept;

	//template<> std::string Cast( unify::DataLockAccess::TYPE type );
	//template<> unify::DataLockAccess::TYPE Cast( std::string type );

	/// <summary>
	/// A data lock construct that allows common locking of data so that we can read and write from shared the data.
	/// </summary>
	template<typename T>
	class DataLock
	{
	public:
		DataLock();
		DataLock( void * data, size_t stride, size_t count, DataLockAccess type, size_t slot );
		DataLock( void * data, size_t sizeInBytes, DataLockAccess type, size_t slot );

		virtual ~DataLock();

		/// @brief
		/// Setup a lock.
		virtual void SetLock( void * data, size_t stride, size_t count, DataLockAccess type, size_t slot );

		/// @brief
		/// Setup a lock.
		virtual void SetLock( void * data, size_t sizeInBytes, DataLockAccess type, size_t slot );

		/// @brief
		/// Returns the type of lock.
		DataLockAccess GetLockType() const;
		
		/// @brief
		/// Return the head pointer to the entire data lock.
		T * GetData();

		/// @brief
		/// Get a pointer to the data 
		const T * GetDataReadOnly() const;

		/// @brief
		/// Return a pointer to the head of a specific 'item', and item being determined by length of stride.
		T * GetItem( size_t index );

		/// @brief
		/// Return a pointer to the head of a specific 'item', and item being determined by length of stride.
		const T * GetItemReadonly( size_t index ) const;

		/// @brief
		/// Returns the number of items.
		size_t Count() const;

		/// @brief
		/// Returns the stride for each item.
		size_t Stride() const;

		/// @brief
		/// Returns the size of our data in bytes.
		size_t GetSizeInBytes() const;

		/// @brief
		/// Returns the slot our data refers to, when available.
		size_t Slot() const;

		/// @brief
		/// Invalidate our data lock.
		virtual void Invalidate();

		/// @brief
		/// Copy data from a source into our data by a specified byte count.
		bool CopyBytesFrom( const void * source, size_t offset, size_t byteCount );

		/// @brief
		/// Copy an item from a source into a specified index.
		bool CopyItemFrom( const void * source, size_t indexTo ); 

		/// @brief
		/// Copy an item from a source index into a specified index.
		bool CopyItemFromTo( size_t indexFrom, size_t indexTo );

		// SAS TODO: Replaced with CRTP class design.
		template< typename T, size_t T_OffsetInBytes = 0 >
		class iterator
		{
			friend DataLock;
		public:
			iterator()
				: m_data( 0 )
				, m_me( 0 )
			{
			}

			iterator( iterator< T > & from )
				: m_data( from.m_data )
				, m_stride( from.m_stride )
				, m_count( from.m_count )
				, m_sizeInBytes( from.m_sizeInBytes )
				, m_readonly( from.m_readonly )
				, m_index( from.m_index )
				, m_me( from.m_me )
			{
			}

			T & operator*()
			{				
				return *m_me;
			}

			bool operator==( const iterator & itr ) const
			{
				return m_data == itr.m_data && m_index == itr.m_index;
			}

			bool operator!=( const iterator & itr ) const
			{
				return ! ( operator==(itr) );
			}

			iterator< T > & operator++()
			{
				assert( m_index + 1 != 0 ); // detect rollover.
				m_index++;
				MakeMe();
				return *this;
			}

			const iterator< T > operator++( int )
			{
				iterator< T > post( this );
				assert( m_index + 1 != 0 ); // detect rollover.
				m_index++;
				MakeMe();
				return post;
			}

			iterator< T > & operator--()
			{
				assert( m_index != 0 ); // detect rollover.
				m_index--;
				MakeMe();
				return *this;
			}

			const iterator< T > operator--( int )
			{
				DataLock::iterator< T > post( this );
				assert( m_index  != 0 ); // detect rollover.
				m_index--;
				MakeMe();
				return post;
			}

			T* operator()()
			{
				return m_data;
			}

		private:
			void MakeMe()
			{
				unsigned char * offset = static_cast< unsigned char*>(m_data) + m_stride * m_index;
				m_me = reinterpret_cast< T * >( offset + T_OffsetInBytes );
			}

			// From DataLock
			T * m_data;
			size_t m_stride; // Item stride
			size_t m_count;	// Number of items we can stride through
			size_t m_sizeInBytes;
			bool m_readonly;

			// Iterator specific
			size_t m_index;
			T * m_me;
		};

		template< typename T >
		iterator< T > begin()
		{
			iterator< T > iter;
			iter.m_data = m_data;
			iter.m_stride = m_stride;
			iter.m_count = m_count;
			iter.m_sizeInBytes = m_sizeInBytes;
			iter.m_index = 0;
			iter.MakeMe();
			return iter;
		}

		template< typename T >
		iterator< T > end()
		{
			iterator< T > iter;
			iter.m_data = m_data;
			iter.m_stride = m_stride;
			iter.m_count = m_count;
			iter.m_sizeInBytes = m_sizeInBytes;
			iter.m_index = m_count;
			iter.MakeMe();
			return iter;
		}

	protected:
		T* m_data;
		size_t m_stride; // Item stride
		size_t m_count;	// Number of items we can stride through
		size_t m_sizeInBytes;
		DataLockAccess m_type;
		size_t m_slot;
	};
}

#include <unify/DataLock.inl>
