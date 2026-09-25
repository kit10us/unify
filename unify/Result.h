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

#include <string>
#include <functional>
#include <variant>

namespace unify
{
	/// @brief A default success class for Result. It is meant only to support the duality of Result (which is able to be a Success result or Failure result).
	class Success
	{
	public:
		constexpr Success() noexcept = default;
		constexpr Success(const Success&) noexcept = default;
		constexpr Success& operator=(const Success&) noexcept = default;
		constexpr Success(Success&&) noexcept = default;
		constexpr Success& operator=(Success&&) noexcept = default;
		~Success() noexcept = default;
	};

	/// @brief A default failure class for Result. It is only meant to support the dualoity of Result (which is able to be a Success result or Failure result).
	class Failure
	{
	public:
		constexpr Failure() noexcept = default;
		constexpr Failure(const Failure&) = default;
		constexpr Failure& operator=(const Failure&) = default;
		constexpr Failure(Failure&&) noexcept = default;
		constexpr Failure& operator=(Failure&&) noexcept = default;
		~Failure() noexcept = default;

		explicit Failure(std::string message) : m_message{ std::move(message) } {}

		[[nodiscard]] const std::string& GetMessage() const noexcept { return m_message; }

	private:
		std::string m_message{};
	};

	/// @brief 
	/// A templated class meant to convey either a success or a failure via defined types.
	/// Defaults to either lite weight Success or Failure class.
	/// @note
	/// It is important to know that this result is about half (per GTest) as efficient as returning a simple POD (bool or int).
	/// It should be avoided in high performance code where special return values, or mechanisms as mention above.
	template<typename T_SuccessType = unify::Success, typename T_Failure = unify::Failure>
	class Result
	{
	public:
		using ptr = std::shared_ptr<Result<T_SuccessType, T_Failure>>;

		constexpr Result(T_SuccessType&& value) noexcept(std::is_nothrow_move_constructible_v<T_SuccessType>)
			: m_result{ std::in_place_index<0>, std::move(value) }
		{
		}

		constexpr Result(T_Failure&& failure) noexcept(std::is_nothrow_move_constructible_v<T_Failure>)
			: m_result{ std::in_place_index<1>, std::move(failure) }
		{
		}

		constexpr Result(const T_SuccessType& value)
			: m_result{ std::in_place_index<0>, value }
		{
		}

		constexpr Result(const T_Failure& failure)
			: m_result{ std::in_place_index<1>, failure }
		{
		}

		template <typename... Args>
		constexpr explicit Result(std::in_place_type_t<T_SuccessType>, Args&&... args)
			: m_result{ std::in_place_index<0>, std::forward<Args>(args)... }
		{
		}

		template <typename... Args>
		constexpr explicit Result(std::in_place_type_t<T_Failure>, Args&&... args)
			: m_result{ std::in_place_index<1>, std::forward<Args>(args)... }
		{
		}

		constexpr Result() noexcept(std::is_nothrow_default_constructible_v<T_SuccessType>)
			: m_result{ std::in_place_index<0> }
		{
		}

		[[nodiscard]] constexpr bool Success() const noexcept
		{
			return m_result.index() == 0;
		}

		[[nodiscard]] constexpr bool Failure() const noexcept
		{
			return m_result.index() == 1;
		}

		[[nodiscard]] constexpr explicit operator bool() const noexcept
		{
			return Success();
		}

		[[nodiscard]] constexpr bool operator!() const noexcept
		{
			return Failure();
		}

		[[nodiscard]] const std::string& Message() const noexcept
		{
			assert(Failure() && "Attempted to access error message on a successful Result!");
        	return std::get<1>(m_result).GetMessage();		
		}

		[[nodiscard]] constexpr const T_SuccessType& Value() const& noexcept
		{
			return std::get<0>(m_result);
		}

		[[nodiscard]] constexpr T_SuccessType& Value() & noexcept
		{
			return std::get<0>(m_result);
		}

		[[nodiscard]] constexpr T_SuccessType&& Value() && noexcept
		{
			return std::get<0>(std::move(m_result));
		}

		[[nodiscard]] constexpr const T_SuccessType& operator*() const& noexcept  { return Value(); }
		[[nodiscard]] constexpr T_SuccessType& operator*() & noexcept        { return Value(); }
		[[nodiscard]] constexpr T_SuccessType&& operator*() && noexcept      { return std::move(*this).Value(); }

		[[nodiscard]] constexpr const T_SuccessType* operator->() const noexcept { return &Value(); }
		[[nodiscard]] constexpr T_SuccessType* operator->() noexcept       { return &Value(); }

		[[nodiscard]] constexpr const T_SuccessType& operator()() const& noexcept { return Value(); }
		[[nodiscard]] constexpr T_SuccessType&& operator()() && noexcept     { return std::move(*this).Value(); }

		template <typename U>
		[[nodiscard]] constexpr T_SuccessType Or(U&& fallback) const&
		{
			if (const auto* val = std::get_if<0>(&m_result))
			{
				return *val;
			}
			return static_cast<T_SuccessType>(std::forward<U>(fallback));
		}

		template <typename U>
		[[nodiscard]] constexpr T_SuccessType Or(U&& fallback) &&
		{
			if (auto* val = std::get_if<0>(&m_result))
			{
				return std::move(*val);
			}
			return static_cast<T_SuccessType>(std::forward<U>(fallback));
		}

	private:
		std::variant<T_SuccessType, T_Failure> m_result;
	};	
}