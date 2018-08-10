// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/AssetPaths.h>
#include <unify/Exception.h>
#include <string>
#include <cassert>

using namespace unify;

AssetPaths::AssetPaths()
{
}

void AssetPaths::AddSource( unify::Path source )
{
	m_paths.push_back( source );
}
		
unify::Path AssetPaths::FindAsset( unify::Path path, unify::Path firstPlace )
{
	if ( ! firstPlace.Empty() && unify::Path( firstPlace, path ).Exists() ) return unify::Path( firstPlace, path );
	if ( path.Exists() ) return path;

	for( auto && post : m_paths )
	{
		unify::Path complete( post + path );
		if ( complete.Exists() )
		{
			return complete;
		}
	}

	const bool checked = true;

	if( checked )
	{
		throw unify::Exception( "Asset \"" + path.ToString() + "\" not found!" );
	}
	else
	{
		return unify::Path();
	}
}

std::string AssetPaths::GetPaths( Path root ) const
{
	std::string paths;
	for ( auto path : m_paths )
	{
		std::string p;
		if ( paths.empty() )
		{		  

			p = (root.DirectoryOnly() + path).Normalize().ToString();
		}
		else
		{
			p = ";" + (root.DirectoryOnly() + path).Normalize().ToString();
		}
		paths += p;
	}
	return paths;
}
