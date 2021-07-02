/* Copyright (c) 2002 - 2019, Kit10 Studios LLC
 * All Rights Reserved
 */

#pragma once

#include <unify/Cast.h>
#include <unify/Exception.h>

namespace unify
{
	struct DataLockAccess
	{
		enum TYPE
		{
			None,
			Readonly,
			Writeonly,
			ReadWrite
		};

		/// <summary>
		/// Returns true if the access supports read mode.
		/// </summary>
		static bool ReadAccess( TYPE access );

		/// <summary>
		/// Returns true if the access mode supports write access.
		/// </summary>
		static bool WriteAccess( TYPE access );

		/// <summary>
		/// Retruns true if access 'a' supports the access specified with 'b'.
		/// </summary>
		static bool Compatible( TYPE a, TYPE b );

		static TYPE FromString( std::string access );
		static std::string ToString( TYPE access );
	};

	template<> std::string Cast( unify::DataLockAccess::TYPE type );
	template<> unify::DataLockAccess::TYPE Cast( std::string type );

	/// <summary>
	/// A data lock construct that allows common locking of data so that we can read and write from shared the data.
	/// </summary>
	class DataLock
	{
	public:
		DataLock();
		DataLock( void * data, unsigned int stride, unsigned int count, DataLockAccess::TYPE type, size_t slot );
		DataLock( void * data, unsigned int sizeInBytes, DataLockAccess::TYPE type, size_t slot );

		virtual ~DataLock();

		/// <summary>
		/// Setup a lock.
		/// </summary>
		virtual void SetLock( void * data, unsigned int stride, unsigned int count, DataLockAccess::TYPE type, size_t slot );

		/// <summary>
		/// Setup a lock.
		/// </summary>
		virtual void SetLock( void * data, unsigned int sizeInBytes, DataLockAccess::TYPE type, size_t slot );

		/// <summary>
		/// Returns the type of lock.
		/// </summary>
		DataLockAccess::TYPE GetType() const;
		
		/// <summary>
		/// Return the head pointer to the entire data lock.
		/// </summary>
		template < typename T >
		T * GetData();

		/// <summary>
		/// Get a pointer to the data 
		/// </summary>
		template < typename T >
		const T * GetDataReadOnly() const;

		/// <summary>
		/// Return a pointer to the head of a specific 'item', and item being determined by length of stride.
		/// </summary>
		template < typename T >
		T * GetItem( unsigned int index );

		/// <summary>
		/// Return a pointer to the head of a specific 'item', and item being determined by length of stride.
		/// </summary>
		template < typename T >
		const T * GetItemReadonly( unsigned int index ) const;

		unsigned int Count() const;

		unsigned int Stride() const;

		unsigned int GetSizeInBytes() const;

		size_t Slot() const;

		virtual void Invalidate();

		virtual bool CopyBytesFrom( const void * source, unsigned int offset, unsigned int byteCount );

		virtual bool CopyItemFrom( const void * source, unsigned int indexTo ); 

		virtual bool CopyItemFromTo( unsigned int indexFrom, unsigned int indexTo );

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

		private:
			void MakeMe()
			{
				unsigned char * offset = static_cast< unsigned char*>(m_data) + m_stride * m_index;
				m_me = reinterpret_cast< T * >( offset + T_OffsetInBytes );
			}

			// From DataLock
			void * m_data;
			unsigned int m_stride; // Item stride
			unsigned int m_count;	// Number of items we can stride through
			unsigned int m_sizeInBytes;
			bool m_readonly;

			// Iterator specific
			unsigned int m_index;
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
		void * m_data;
		unsigned int m_stride; // Item stride
		unsigned int m_count;	// Number of items we can stride through
		unsigned int m_sizeInBytes;
		DataLockAccess::TYPE m_type;
		size_t m_slot;
	};

	/// <summary>
	/// Return the head pointer to the entire data lock.
	/// </summary>
	template < typename T >
	T * DataLock::GetData()
	{
		if ( !DataLockAccess::ReadAccess( m_type ) || !DataLockAccess::WriteAccess( m_type ) )
		{
			throw unify::Exception( "Attempted to access " + DataLockAccess::ToString( m_type ) + " for " + DataLockAccess::ToString( DataLockAccess::ReadWrite ) + " access!" );
		}
		return (T*)m_data;
	}

	template < typename T >
	const T * DataLock::GetDataReadOnly() const
	{
		if ( !DataLockAccess::ReadAccess( m_type ) )
		{
			throw unify::Exception( "Attempted to access " + DataLockAccess::ToString( m_type ) + " for " + DataLockAccess::ToString( DataLockAccess::ReadWrite ) + " access!" );
		}
		return (T*)m_data;
	}

	template < typename T >
	T * DataLock::GetItem( unsigned int index )
	{
		if (index >= m_count)
		{
			throw unify::Exception( "Attempted to access index out of range! (" + unify::Cast< std::string >( index ) + " to " + unify::Cast< std::string >( m_count ) + ")" );
		}

		if ( !DataLockAccess::ReadAccess( m_type ) || !DataLockAccess::WriteAccess( m_type )  )
		{
			throw unify::Exception( "Attempted to access " + DataLockAccess::ToString( m_type ) + " for " + DataLockAccess::ToString( DataLockAccess::ReadWrite ) + " access!" );
		}

		return &GetData< T >()[ index ];
	}

	template < typename T >
	const T * DataLock::GetItemReadonly( unsigned int index ) const
	{
		if (index >= m_count)
		{
			throw unify::Exception( "Attempted to access index out of range! (" + unify::Cast< std::string >( index ) + " to " + unify::Cast< std::string >( m_count ) + ")" );
		}

		if (!DataLockAccess::ReadAccess( m_type ))
		{
			throw unify::Exception( "Attempted to access READONLY data for write!" );
		}

		return &GetDataReadOnly< T >()[ index ];
	}
} // namespace unify
