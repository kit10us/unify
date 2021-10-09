// Copyright (c) 2002 - 2018, Kit10 Studios LLC
// All Rights Reserved

/// <summary>
/// Test Path.
/// </summary>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unify/Parameters.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "Parameters" );
	{
		suite.BeginCase( "Creation by 'Set'" );
		{
			Parameters parameters;
			parameters.Set< std::string >( "first", "first" );
			parameters.Set< std::string >( "second", "second" );
			parameters.Set< std::string >( "third", "third" );

			suite.Assert( "count is 3", parameters.Count() == 3 );

			auto exists = parameters.Exists("first");
			auto a = parameters.Get<std::string>("first");

			suite.Assert( "first", parameters.Get< std::string >( "first" ) == "first" );
			suite.Assert( "second", parameters.Get< std::string >( "second" ) == "second" );
			suite.Assert( "third", parameters.Get< std::string >( "third" ) == "third" );
		}
		suite.EndCase();

		suite.BeginCase( "Creation from inialization list" );
		{
			Parameters parameters {
				{ "first", (std::string)"first" },
				{ "second", (std::string)"second" },
				{ "third", (std::string)"third" }
			};

			suite.Assert( "first", parameters.Get< std::string >( "first" ) == "first" );
			suite.Assert( "second", parameters.Get< std::string >( "second" ) == "second" );
			suite.Assert( "third", parameters.Get< std::string >( "third" ) == "third" );
		}

		suite.BeginCase( "Set and get value" );
		{
			Parameters parameters {
				{ "bool", true },
				{ "char", (char)-10 },
				{ "unsigned char", (unsigned char)20 },
				{ "int", (int)-30 },
				{ "unsigned int", (unsigned int)40 },
				{ "size_t", (size_t)50 },
				{ "std::string", (std::string)"Hello, world!" }
			};

			suite.Assert( "Get bool", parameters.Get< bool >( "bool" ) == true );
			suite.Assert( "Get char", parameters.Get< char >( "char" ) == -10 );
			suite.Assert( "Get unsigned char", parameters.Get< unsigned char >( "unsigned char" ) == 20 );
			suite.Assert( "Get int", parameters.Get< int >( "int" ) == -30 );
			suite.Assert( "Get unsigned int", parameters.Get< unsigned int >( "unsigned int" ) == 40 );
			suite.Assert( "Get size_t", parameters.Get< size_t >( "size_t" ) == 50 );
			suite.Assert( "Get std::string", parameters.Get< std::string >( "std::string" ) == "Hello, world!" );
		}
		suite.EndCase();

		suite.BeginCase( "Get with default" );
		{
			Parameters parameters {
				{ "first", (std::string)"first" },
				{ "second", (std::string)"second" }
			};

			suite.Assert( "Get default bool", parameters.Get( "bool", true ) == true );
			suite.Assert( "Get default char", parameters.Get( "char", (char)-10 ) == -10 );
			suite.Assert( "Get default unsigned char", parameters.Get( "unsigned char", (unsigned char)20 ) == 20 );
			suite.Assert( "Get default int", parameters.Get( "int", (int)-30 ) == -30 );
			suite.Assert( "Get default unsigned int", parameters.Get( "unsigned int", (unsigned int)40 ) == 40 );
			suite.Assert( "Get default size_t", parameters.Get( "size_t", (size_t)50 ) == 50 );
			suite.Assert( "Get default std::string", parameters.Get( "std::string", (std::string)"Hello, world!" ) == "Hello, world!" );
		}
		suite.EndCase();

		suite.BeginCase( "Get with default" );
		{
			Parameters parameters{
				{ "bool", true },
				{ "char", (char)-10 },
				{ "unsigned char", (unsigned char)20 },
				{ "int", (int)-30 },
				{ "unsigned int", (unsigned int)40 },
				{ "size_t", (size_t)50 },
				{ "std::string", (std::string)"Hello, world!" },
				{ "float signed", (float)-60.f },
				{ "float unsigned", (float)60.f },
				{ "double", (double)70.0 }
			};

			suite.Assert( "Cast to bool from bool",				parameters.Cast< bool >( "bool" ) == true );
			suite.Assert( "Cast to bool from char",				parameters.Cast< bool >( "char" ) == true );
			suite.Assert( "Cast to bool from unsigned bool",	parameters.Cast< bool >( "unsigned char" ) == true );
			suite.Assert( "Cast to bool from int",				parameters.Cast< bool >( "int" ) == true );
			suite.Assert( "Cast to bool from unsigned int",		parameters.Cast< bool >( "unsigned int" ) == true );
			suite.Assert( "Cast to bool from size_t",			parameters.Cast< bool >( "size_t" ) == true );
			suite.Assert( "Cast to bool from float",			parameters.Cast< bool >( "float signed" ) == true );
			suite.Assert( "Cast to bool from double",			parameters.Cast< bool >( "double" ) == true );

			suite.Assert( "Cast to char from bool",				parameters.Cast< char >( "bool" ) == 1 );
			suite.Assert( "Cast to char from char",				parameters.Cast< char >( "char" ) == -10 );
			suite.Assert( "Cast to char from unsigned char",	parameters.Cast< char >( "unsigned char" ) == 20 );
			suite.Assert( "Cast to char from int",				parameters.Cast< char >( "int" ) == -30 );
			suite.Assert( "Cast to char from unsigned int",		parameters.Cast< char >( "unsigned int" ) == 40 );
			suite.Assert( "Cast to char from size_t",			parameters.Cast< char >( "size_t" ) == 50 );
			suite.Assert( "Cast to char from float",			parameters.Cast< char >( "float signed" ) == -60 );
			suite.Assert( "Cast to char from double",			parameters.Cast< char >( "double" ) == 70 );

			suite.Assert( "Cast to unsigned char from bool",			parameters.Cast< unsigned char >( "bool" ) == 1 );
			suite.Assert( "Cast to unsigned char from char",			parameters.Cast< unsigned char >( "char" ) == (unsigned char) -10 );
			suite.Assert( "Cast to unsigned char from unsigned char",	parameters.Cast< unsigned char >( "unsigned char" ) == 20 );
			suite.Assert( "Cast to unsigned char from int",				parameters.Cast< unsigned char >( "int" ) == (unsigned char) -30 );
			suite.Assert( "Cast to unsigned char from unsigned int",	parameters.Cast< unsigned char >( "unsigned int" ) == 40 );
			suite.Assert( "Cast to unsigned char from size_t",			parameters.Cast< unsigned char >( "size_t" ) == 50 );
			suite.Assert( "Cast to unsigned char from float",			parameters.Cast< unsigned char >( "float unsigned" ) == (unsigned char) 60 );
			suite.Assert( "Cast to unsigned char from double",			parameters.Cast< unsigned char >( "double" ) == 70 );
		
			suite.Assert( "Cast to int from bool",			parameters.Cast< int >( "bool" ) == 1 );
			suite.Assert( "Cast to int from char",			parameters.Cast< int >( "char" ) == -10 );
			suite.Assert( "Cast to int from unsigned char", parameters.Cast< int >( "unsigned char" ) == 20 );
			suite.Assert( "Cast to int from int",			parameters.Cast< int >( "int" ) == -30 );
			suite.Assert( "Cast to int from unsigned int",	parameters.Cast< int >( "unsigned int" ) == 40 );
			suite.Assert( "Cast to int from size_t",		parameters.Cast< int >( "size_t" ) == 50 );
			suite.Assert( "Cast to int from float",			parameters.Cast< int >( "float signed" ) == -60 );
			suite.Assert( "Cast to int from double",		parameters.Cast< int >( "double" ) == 70 );

			suite.Assert( "Cast to unsigned int from bool",				parameters.Cast< unsigned int >( "bool" ) == 1 );
			suite.Assert( "Cast to unsigned int from char",				parameters.Cast< unsigned int >( "char" ) == (unsigned int) - 10 );
			suite.Assert( "Cast to unsigned int from unsigned char",	parameters.Cast< unsigned int >( "unsigned char" ) == 20 );
			suite.Assert( "Cast to unsigned int from int",				parameters.Cast< unsigned int >( "int" ) == (unsigned int) - 30 );
			suite.Assert( "Cast to unsigned int from unsigned int",		parameters.Cast< unsigned int >( "unsigned int" ) == 40 );
			suite.Assert( "Cast to unsigned int from size_t",			parameters.Cast< unsigned int >( "size_t" ) == 50 );
			suite.Assert( "Cast to unsigned int from float",			parameters.Cast< unsigned int >( "float unsigned" ) == (unsigned int) 60 );
			suite.Assert( "Cast to unsigned int from double",			parameters.Cast< unsigned int >( "double" ) == (unsigned int) 70 );

			suite.Assert( "Cast to float from bool",			parameters.Cast< float >( "bool" ) == 1.0f );
			suite.Assert( "Cast to float from char",			parameters.Cast< float >( "char" ) == -10.0f );
			suite.Assert( "Cast to float from unsigned char",	parameters.Cast< float >( "unsigned char" ) == 20.0f );
			suite.Assert( "Cast to float from int",				parameters.Cast< float >( "int" ) == -30.0f );
			suite.Assert( "Cast to float from unsigned int",	parameters.Cast< float >( "unsigned int" ) == 40.0f );
			suite.Assert( "Cast to float from size_t",			parameters.Cast< float >( "size_t" ) == 50.0f );
			suite.Assert( "Cast to float from float",			parameters.Cast< float >( "float signed" ) == -60.0f );
			suite.Assert( "Cast to float from double",			parameters.Cast< float >( "double" ) == 70.0f );

			suite.Assert( "Cast to double from bool",			parameters.Cast< double >( "bool" ) == 1.0 );
			suite.Assert( "Cast to double from char",			parameters.Cast< double >( "char" ) == -10.0 );
			suite.Assert( "Cast to double from unsigned char",	parameters.Cast< double >( "unsigned char" ) == 20.0 );
			suite.Assert( "Cast to double from int",			parameters.Cast< double >( "int" ) == -30.0 );
			suite.Assert( "Cast to double from unsigned int",	parameters.Cast< double >( "unsigned int" ) == 40.0 );
			suite.Assert( "Cast to double from size_t",			parameters.Cast< double >( "size_t" ) == 50.0 );
			suite.Assert( "Cast to double from float",			parameters.Cast< double >( "float signed" ) == -60.0 );
			suite.Assert( "Cast to double from double",			parameters.Cast< double >( "double" ) == 70.0 );

			parameters.Set( { "new parameter", std::string("new value") } );
			suite.Assert( "Parameter created via 'Set(Parameter)'", unify::string::StringIs( parameters.Get<std::string>( "new parameter" ), "new value" ) );
		}
		suite.EndCase();

		suite.BeginCase("Case insensitive.");
		{
			Parameters parameters
			{
				{"First", true}
			};

			suite.Assert("Case insensitive compare, same", parameters.Exists("First"));
			suite.Assert("Case insensitive compare, all lower", parameters.Exists("first"));
			suite.Assert("Case insensitive compare, all capitals", parameters.Exists("FIRST"));
		}
		suite.EndCase();
	}
	suite.EndSuite();

	return 0;
}