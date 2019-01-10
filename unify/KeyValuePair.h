// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

namespace unify
{
	/// <summary>
	/// A generic key value pair.
	/// </summary>
	template< typename Key, typename Value >
	struct KeyValuePair
	{
		KeyValuePair( const KeyValuePair< Key, Value > & keyValue )
			: key{ keyValue.key }
			, value{ keyValue.value }
		{
		}

		KeyValuePair( Key key, Value value )
			: key{ key }
			, value{ value }
		{
		}

		bool operator=( const KeyValuePair & keyValue )
		{
			return key == keyValue.key && value == keyValue.value;
		}

		const Key key;
		Value value;
	};
}