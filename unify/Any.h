// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

/// NOTICE: The contents of this header were pulled from the Boost library, modified to remove usage of Boost, and replace that usage with C++11.
///         This was done as Any is the last remaining feature from boost, not provided via C++11, that I like to use, and I do not want to have to
///         continue to pull in a substantially large library for one tiny piece. All repsect to those who created an maintain this originally.
///         I thus assume no rights, responsibility, nor credit for the contents here-in.
#pragma once

#include <algorithm>
#include <typeinfo>
#include <cassert>

namespace unify
{
	/// <summary>
	/// Any allows us to simplify our interfaces when the type a function can consume is largely variable, or more importantly, extremely late,
	/// such as with an event system. Instead of creating tens to hundreds of member functions able to consume specific type, we generalize to
	/// to take an Any (think of it as an "anything"), then let the implementation verify the actual type and act accordingly.
	/// This pretty much just encapsulates RTTI and makes it feel more natural.
	/// </summary>
	class Any
	{
	public:
		Any() noexcept
			: content {}
		{
		}

		template<typename ValueType>
		Any( const ValueType & value )
			: content( new holder< typename std::remove_cv<typename std::decay<const ValueType>::type>::type >( value ) )
		{
		}

		Any( const Any & other )
			: content( other.content ? other.content->clone() : 0 )
		{
		}

		// Move constructor
		Any( Any&& other ) noexcept
			: content( other.content )
		{
			other.content = 0;
		}

		// Perfect forwarding of ValueType
		template<typename ValueType>
		Any( ValueType&& value
			, typename std::enable_if< !std::is_same<Any&, ValueType>::value >::type* = 0 // disable if value has type `Any&`
			, typename std::enable_if< !std::is_const<ValueType>::value >::type* = 0 ) // disable if value has type `const ValueType&&`
			: content( new holder< typename std::decay<ValueType>::type >( static_cast<ValueType&&>(value) ) )
		{
		}

		~Any() noexcept
		{
			delete content;
		}

	public: // modifiers

		Any & swap( Any & rhs ) noexcept
		{
			std::swap( content, rhs.content );
			return *this;
		}

		Any & operator=( const Any& rhs )
		{
			Any( rhs ).swap( *this );
			return *this;
		}

		// move assignement
		Any & operator=( Any&& rhs ) noexcept
		{
			rhs.swap( *this );
			Any().swap( rhs );
			return *this;
		}

		// Perfect forwarding of ValueType
		template <class ValueType>
		Any & operator=( ValueType&& rhs )
		{
			Any( static_cast<ValueType&&>(rhs) ).swap( *this );
			return *this;
		}

	public: // queries

		bool empty() const noexcept
		{
			return !content;
		}

		void clear() noexcept
		{
			Any().swap( *this );
		}

		const std::type_info& type() const noexcept
		{
			return content ? content->type() : typeid(void);
		}

	private: // types

		class placeholder
		{
		public: // structors

			virtual ~placeholder()
			{
			}

		public: // queries

			virtual const std::type_info& type() const noexcept = 0;

			virtual placeholder * clone() const = 0;

		};

		template<typename ValueType>
		class holder : public placeholder
		{
		public: // structors

			holder( const ValueType & value )
				: held( value )
			{
			}

			holder( ValueType&& value )
				: held( static_cast< ValueType&& >(value) )
			{
			}

		public: // queries

			virtual const std::type_info& type() const noexcept
			{
				return typeid(ValueType);
			}

			virtual placeholder * clone() const
			{
				return new holder( held );
			}

		public: // representation

			ValueType held;

		private: // intentionally left unimplemented
			holder & operator=( const holder & );
		};

	private: // representation

		template<typename ValueType>
		friend ValueType * any_cast( Any * ) noexcept;

		template<typename ValueType>
		friend ValueType * unsafe_any_cast( Any * ) noexcept;


		placeholder * content;

	};

	inline void swap( Any & lhs, Any & rhs ) noexcept
	{
		lhs.swap( rhs );
	}

	class /*BOOST_SYMBOL_VISIBLE*/ bad_any_cast :
		public std::bad_cast
	{
	public:
		virtual const char * what() const noexcept
		{
			return "unify::bad_any_cast: "
				"failed conversion using unify::any_cast";
		}
	};

	template<typename ValueType>
	ValueType * any_cast( Any * operand ) noexcept
	{
		return operand && operand->type() == typeid(ValueType)
			? &static_cast<Any::holder<typename std::remove_cv<ValueType>::type> *>(operand->content)->held
			: 0;
	}

	template<typename ValueType>
	inline const ValueType * any_cast( const Any * operand ) noexcept
	{
		return any_cast<ValueType>(const_cast<Any *>(operand));
	}

	template<typename ValueType>
	ValueType any_cast( Any & operand )
	{
		typedef typename std::remove_reference<ValueType>::type nonref;


		nonref * result = any_cast<nonref>(&operand);
		if( !result )
			throw bad_any_cast();

		// Attempt to avoid construction of a temporary object in cases when 
		// `ValueType` is not a reference. Example:
		// `static_cast<std::string>(*result);` 
		// which is equal to `std::string(*result);`
		typedef typename std::conditional<
			std::is_reference<ValueType>::value,
			ValueType,
			ValueType &
		>::type ref_type;

		return static_cast<ref_type>(*result);
	}

	template<typename ValueType>
	inline ValueType any_cast( const Any & operand )
	{
		typedef typename std::remove_reference<ValueType>::type nonref;
		return any_cast<const nonref &>(const_cast<Any &>(operand));
	}

	template<typename ValueType>
	inline ValueType any_cast( Any&& operand )
	{
		assert(
			(std::is_rvalue_reference<ValueType&&>::value /*true if ValueType is rvalue or just a value*/
				|| std::is_const< typename std::remove_reference<ValueType>::type >::value) &&
			"unify::any_cast shall not be used for getting nonconst references to temporary objects"
			);
		return any_cast<ValueType>(operand);
	}


	// Note: The "unsafe" versions of any_cast are not part of the
	// public interface and may be removed at any time. They are
	// required where we know what type is stored in the any and can't
	// use typeid() comparison, e.g., when our types may travel across
	// different shared libraries.
	template<typename ValueType>
	inline ValueType * unsafe_any_cast( Any * operand ) noexcept
	{
		return &static_cast<Any::holder<ValueType> *>(operand->content)->held;
	}

	template<typename ValueType>
	inline const ValueType * unsafe_any_cast( const Any * operand ) noexcept
	{
		return unsafe_any_cast<ValueType>(const_cast<Any *>(operand));
	}
}
