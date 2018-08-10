// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>

namespace unify
{
	/// <summary>
	/// A Dynamic allows referencing a valu ethat can be local or dynamicly set elsewhere, depeding on inheritence.
	/// </summary>
	template< typename T >
	class Dynamic
	{
	public:
		virtual ~Dynamic() {}
	
	private:
		/// <summary>
		/// Returns the dynamic value
		/// </summary>
		virtual T Get() = 0;
	};
	#include <unify/BBox.inl>
}
