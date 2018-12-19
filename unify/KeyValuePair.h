// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <conio.h>

namespace unify
{
	/// <summary>
	/// A generic key value pair.
	/// </summary>
	template< typename Key, typename Value >
	struct KeyValuePair
	{
		const Key key;
		Value value;
	};
}