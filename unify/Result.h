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
	class Failure
	{
	public:
		Failure()
		: m_message{ "Unspecified failure." }
		{
		}

		Failure(std::string message)
			: m_message{ message }
		{
		}

		std::string GetMessage() const
		{
			return m_message;
		}

	private:
		std::string m_message;
	};

	template<typename T_SuccessType = bool, typename T_Failure = Failure>
	class Result
	{
	public:
		Result(T_SuccessType value)
			: m_result{ value }
		{
		}

		Result(Failure failure)
			: m_result{ failure }
		{
		}

		Result()
			: Result(T_SuccessType{})
		{
		}

		bool Success() const
		{
			return std::holds_alternative<Failure>(m_result) ? false : true;
		}

		[[nodiscard]] std::string Message() const
		{
			if (Success())
			{
				return {};
			}
			else
			{
				return std::get<Failure>(m_result).GetMessage();
			}
		}

		[[nodiscard]] T_SuccessType Value() const
		{
			return std::get<T_SuccessType>(m_result);
		}

		/// <summary>
		/// Get the results.
		/// Will throw if a failure. Use Failure() or Success() first to verify results.
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] T_SuccessType operator()() const
		{
			return Value();
		}

		[[nodiscard]] bool operator!() const
		{
			return !Success();
		}

		T_SuccessType Or(T_SuccessType&& value) const noexcept
		{
			try
			{
				auto result = std::get<T_SuccessType>(m_result);
				return result;
			}
			catch(...)
			{
				return value;
			}
		}

	public:
		std::variant<T_SuccessType, T_Failure> m_result;
	};
}