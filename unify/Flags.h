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

#include <unify/Unify.h>

namespace unify
{
	/// <summary>
	/// A type def to represent a bit flag value. More so code purpose is mode obvious.
	/// </summary>
	typedef unsigned int	Flags;

	#define FLAG00		0x00000000
	#define FLAG01			0x00000001
	#define FLAG02			0x00000002
	#define FLAG03			0x00000004
	#define FLAG04			0x00000008
	#define FLAG05			0x00000010
	#define FLAG06			0x00000020
	#define FLAG07			0x00000040
	#define FLAG08			0x00000080
	#define FLAG09			0x00000100
	#define FLAG10			0x00000200
	#define FLAG11			0x00000400
	#define FLAG12			0x00000800
	#define FLAG13			0x00001000
	#define FLAG14			0x00002000
	#define FLAG15			0x00004000
	#define FLAG16			0x00008000
	#define FLAG17			0x00010000
	#define FLAG18			0x00020000
	#define FLAG19			0x00040000
	#define FLAG20			0x00080000
	#define FLAG21			0x00100000
	#define FLAG22			0x00200000
	#define FLAG23			0x00400000
	#define FLAG24			0x00800000
	#define FLAG25			0x01000000
	#define FLAG26			0x02000000
	#define FLAG27			0x03000000
	#define FLAG28			0x08000000
	#define FLAG29			0x10000000
	#define FLAG30			0x20000000
	#define FLAG31			0x40000000
	#define FLAG32			0x80000000

	inline
	bool CheckFlag( Flags flags, Flags member )
	{
		if( (flags & member) == member )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	#define BITCOMPARE(b1, b2)		(b2==(b1 & b2))		// Compare bits
	#define BITSTATE(b1, b2)		((b1>>b2)&1)		// Get the state of a single bit
}
