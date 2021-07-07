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

#include <memory>
#include <unify/Unify.h>
#include <unify/String.h>
#include <unify/Exception.h>
#include <unify/test/IOutputHandler.h>

namespace unify
{
	namespace test
	{
		class DefaultOutputHandler : public IOutputHandler
		{
		public:
			virtual ~DefaultOutputHandler();

			/// <summary>
			/// Called for output of message.
			/// </summary>
			/// <param name="message">
			/// Message for the assert.
			/// </param>
			/// <param name="type">
			/// Type of the assert.
			/// </param>
			virtual void Output( std::string message, OutputType type );
		};
	}
}