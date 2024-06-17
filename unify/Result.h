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

	template<typename T_SuccessType = bool>
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
			: Result(true)
		{
		}

		bool Success() const
		{
			return std::holds_alternative<Failure>(m_result) ? false : true;
		}

		std::string Message() const
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

		T_SuccessType Value() const
		{
			return std::get<T_SuccessType>(m_result);
		}

		/// <summary>
		/// Upon success, returns the parameter, else returns a failure.
		/// </summary>
		template<typename T_NewType>
		Result<T_NewType> As(T_NewType success) const
		{
			if (Success())
			{
				return success;
			}
			else
			{
				return Failure{ Message() };
			}
		}

		/// <summary>
		/// Get the results.
		/// Will throw if a failure. Use Failure() or Success() first to verify results.
		/// </summary>
		/// <returns></returns>
		T_SuccessType operator()() const
		{
			return Value();
		}

		/// <summary>
		/// Calls a function, passed as a parameter, upon a failure.
		/// </summary>
		void OnFailure(std::function< void(std::string message) > func) const
		{
			if (!Success())
			{
				func(Message());
			}
		}

		/// <summary>
		/// If successfull, returns the value, else calls a function upon a failure.
		/// </summary>
		T_SuccessType Else(std::function<void(std::string message)> func) const
		{
			if (!Success())
			{
				func(Message());
			}
			return (*this)();
		}

		/// <summary>
		/// If successfull, returns the value, else calls a function upon a failure.
		/// </summary>
		T_SuccessType Else(std::function<void(void)> func) const
		{
			if (!Success())
			{
				func();
			}
			return (*this)();
		}

	public:
		std::variant<T_SuccessType, Failure> m_result;
	};
}