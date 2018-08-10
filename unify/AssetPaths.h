// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Path.h>
#include <list>

namespace unify
{
	class AssetPaths
	{
	public:
		AssetPaths();

		void AddSource( Path source );
		
		Path FindAsset( Path path, Path firstPlace = Path() );

		std::string GetPaths( Path root = Path() ) const;

	private:
		std::list< Path > m_paths;
	};
}
