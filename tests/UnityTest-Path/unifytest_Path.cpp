// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <iostream>
#include <string>
#include <fstream>
#include <unify/Path.h>
#include <unify/test/Suite.h>

//
// Purpose of test...
//    Test unify::Path.
//

int main( int argc, char ** argv )
{
	using namespace std;
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "Path" );

	{
		string tempString;
		Path tempPath;
		bool testBool;

		suite.BeginCase( "Convert to string" );
		const Path path( "c:\\directory\\sub_directory\\file_name.ext" );
		suite.Assert( "Forward", path.ToString( Slash::Foward ) == "c:\\directory\\sub_directory\\file_name.ext" );
		suite.Assert( "Backward", path.ToString( Slash::Backward ) == "c:/directory/sub_directory/file_name.ext" );
		suite.EndCase();

		suite.BeginCase( "ostream operator<<" );
		cout << "result: \"" << path << "\"." << endl << endl;
		suite.EndCase();

		suite.BeginCase( "ExtensionOnly" );
		tempString = path.ExtensionOnly();
		suite.Assert( "Extenion only", tempString == ".ext" );
		suite.EndCase();

		suite.BeginCase( "ExtensionOnly with no extension on path" );
		tempString = Path( "c:\\directory\\sub_directory\\" ).ExtensionOnly();
		suite.Assert( "ExtionOnly with no extention on path", tempString == "" );
		suite.EndCase();

		suite.BeginCase( "DirectoryOnly" );
		tempPath = path.DirectoryOnly();
		suite.Assert( "DirectoryOnly", tempPath == Path( "c:\\directory\\sub_directory\\" ) );
		suite.EndCase();

		suite.BeginCase( "Filename" );
		tempPath = Path( path.Filename() );
		suite.Assert( "Filename", tempPath == Path( "file_name.ext" ) );
		suite.EndCase();

		suite.BeginCase( "FilenameNoExtension - 1. Full path." );
		tempPath = Path(  path.FilenameNoExtension() );
		suite.Assert( "FilenameNoExt", tempPath.ToString() == "file_name" );
		suite.EndCase();

		suite.BeginCase( "Path slashs equivalency" );
		suite.Assert( "\"\\file\" == \"/file\"", Path( "\\file" ) == Path( "/file" ) );
		suite.EndCase();

		suite.BeginCase( "Combine" );
		{
			tempPath.Combine( Path( "c:\\directory\\subdirectory" ) , unify::Path( "/file_name.ext" ) );
			suite.Assert( "Complete L (without ending slash) and R (with leading slash)", tempPath == Path( "c:\\directory\\subdirectory\\file_name.ext" ) );
		
			tempPath.Combine( Path( "c:\\directory\\subdirectory\\" ) , unify::Path( "/file_name.ext" ) );
			suite.Assert( "Complete L (with ending slash) and R (with leading slash)", tempPath == Path( "c:\\directory\\subdirectory\\file_name.ext" ) );

			tempPath.Combine( Path( "c:\\directory\\subdirectory" ), unify::Path( "file_name.ext" ) );
			suite.Assert( "Complete L( without ending slash ) and R( without leading slash )", tempPath == Path( "c:\\directory\\subdirectory\\file_name.ext" ) );
		}
		suite.EndCase();

		suite.BeginCase( "Split" );
		const Path pathInputA( "c:\\directory\\subdirectory/..\\test\\file_name.ext" );
		vector< string > partsOutput = pathInputA.Split();
		cout << "results: ";
		//for ( const auto itr = partsOutput.begin(), end = partsOutput.end(); itr != end; ++itr )
		for( const auto i : pathInputA.Split() )
		{
			cout << "[" << i << "]";
		}
		suite.EndCase();

		suite.BeginCase( "Join" );
		cout << "result: \"" << Path( partsOutput ) << endl << endl;
		suite.EndCase();

		suite.BeginCase( "Normalize" );
		cout << "result: \"" << Path( pathInputA ).Normalize() << endl << endl;
		suite.EndCase();

		suite.BeginCase( "Combine" );
		tempPath.Combine( Path( "c:\\directory\\subdirectory" ) , Path( "..\\test\\file_name.ext" ) );
		cout << "result: \"" << tempPath << "\"." << endl << endl;
		suite.EndCase();

		suite.BeginCase( "IsExtension - 1. Path has extension, ext has no dot (.)." );
		testBool = path.IsExtension( "ext" );
		cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;
		suite.EndCase();

		suite.BeginCase( "IsExtension - 2. Path has extension, ext has dot(.)." );
		testBool = path.IsExtension( ".ext" );
		cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;
		suite.EndCase();

		suite.BeginCase( "IsExtension - 1. Not match." );
		testBool = path.IsExtension( "etx" );
		cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;
		suite.EndCase();

		{
			suite.BeginCase( "Exists" );
			Path file( "test.txt" );
			ofstream stream;
			stream.open( file.ToString() );
			stream << "Hello, world!";
			stream.close();
			cout << "result: " << ( file.Exists() ? "pass" : "failed" ) << endl;
			suite.EndCase();

			suite.BeginCase( "Rename" );
			Path fileTo( "test_renamed.txt" );
			if( ! Path::Rename( file, fileTo ) || ! fileTo.Exists() )
			{
				cout << "  result: fail" << endl;
			}
			else
			{
				cout << "  result: pass" << endl;
			}
			suite.EndCase();

			suite.BeginCase( "Delete" );
			if( !Path::Delete( fileTo ) || fileTo.Exists() )
			{
				cout << "  result: fail" << endl;
			}
			else
			{
				cout << "  result: pass" << endl;
			}
			suite.EndCase();
		}
	}
	suite.EndSuite();

	cout << "Press any Enter to finish...\n";
	cin.ignore();

	return 0;
}