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


#include <unify/Result.h>

using namespace unify;


Result::ptr Result::FAILED(std::string message)
{
	return std::make_shared<Result>(false, message);
}

Result::Result()
	: Result{ true }
{
}

Result::Result(bool success, std::string message)
	: m_success{ success }
	, m_message{ message }
{
}

bool Result::operator()() const
{
	return Success();
}

std::string Result::Message() const
{
	return m_message;
}

bool Result::Success() const
{
	return m_success;
}

bool Result::Fail() const
{
	return !m_success;
}
