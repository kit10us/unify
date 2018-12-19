// Copyright (c) 2002 - 2019, Quentin S. Smith
// All Rights Reserved

template< typename foo, typename ... bar >
bool unify::string::StringIs( std::string a, std::string is, std::string rest... )
{
	if (_stricmp( a.c_str(), is.c_str() ) == 0)
	{
		return true;
	}
	return string::StringIs( a, rest );
}

template< typename T >
std::vector< T > unify::string::Split( std::string sourceString, const char delimitor )
{
	std::vector< T > destination;
	std::stringstream ss( sourceString );
	std::string item;
	while( std::getline( ss, item, delimitor ) ) 
	{
		destination.push_back( Cast< T >( item ) );
	}
	return destination;
}

template< typename T >
std::vector< T > unify::string::Split( std::string sourceString, const std::vector< char > & delimitors, bool includeEmpties )
{
	std::vector< T > destination;

	size_t start = 0;
	size_t end = 0;
	for( end = 0; end < sourceString.size(); ++end )
	{
		if ( std::find( delimitors.begin(), delimitors.end(), sourceString.at( end ) ) != delimitors.end() )
		{
			if ( start == end )
			{
				if ( includeEmpties )
				{
					destination.push_back( T() );
				}
			}
			else
			{
				destination.push_back( Cast< T >( sourceString.substr( start, end - start ) ) );
			}
			start = end + 1;
		}
	}

	if ( start == end )
	{
		if ( includeEmpties )
		{
			destination.push_back( T() );
		}
	}
	else
	{
		destination.push_back( Cast< T >( sourceString.substr( start, end - start ) ) );
	}

	return destination;
}

template< typename T >
std::vector< T > unify::string::SplitOnWhitespace( std::string sourceString )
{
	std::vector< char > delimitors;
	delimitors.push_back( ' ' );
	delimitors.push_back( '\t' );
	delimitors.push_back( '\n' );
	return Split< T >( sourceString, delimitors );
}
