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
#include <memory>

namespace unify
{
	/// <summary>
	/// Used to track the result of any operation or functionality.
	/// </summary>
	class Result
	{
	public:
		typedef std::shared_ptr<Result> ptr;

		static Result::ptr FAILED(std::string message);

		Result();

		Result(bool success, std::string message = {});

		bool operator()() const;

		std::string Message() const;

		bool Success() const;

		bool Fail() const;

	private:
		std::string m_message;
		bool m_success;
	};
}
