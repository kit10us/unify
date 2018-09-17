// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <iostream>
#include <string>
#include <fstream>
#include <unify/Path.h>
#include <unify/TestSuite.h>

//
// Purpose of test...
//    Test unify::Path.
//

int main( int argc, char ** argv )
{
	using namespace std;
	using namespace unify;

	TestSuite testSuite( "Path", "   " );

	testSuite.BeginSuite();

	{
		string tempString;
		Path tempPath;
		bool testBool;

		testSuite.BeginCase( "Convert to string" );
		const Path path( "c:\\directory\\sub_directory\\file_name.ext" );
		testSuite.Assert( "Forward", path.ToString( Slash::Foward ) == "c:\\directory\\sub_directory\\file_name.ext" );
		testSuite.Assert( "Backward", path.ToString( Slash::Backward ) == "c:/directory/sub_directory/file_name.ext" );
		testSuite.EndCase();

		testSuite.BeginCase( "ostream operator<<" );
		cout << "result: \"" << path << "\"." << endl << endl;
		testSuite.EndCase();

		testSuite.BeginCase( "ExtensionOnly" );
		tempString = path.ExtensionOnly();
		testSuite.Assert( "Extenion only", tempString == ".ext" );
		testSuite.EndCase();

		testSuite.BeginCase( "ExtensionOnly with no extension on path" );
		tempString = Path( "c:\\directory\\sub_directory\\" ).ExtensionOnly();
		testSuite.Assert( "ExtionOnly with no extention on path", tempString == "" );
		testSuite.EndCase();

		testSuite.BeginCase( "DirectoryOnly" );
		tempPath = path.DirectoryOnly();
		testSuite.Assert( "DirectoryOnly", tempPath == Path( "c:\\directory\\sub_directory\\" ) );
		testSuite.EndCase();

		testSuite.BeginCase( "Filename" );
		tempPath = Path( path.Filename() );
		testSuite.Assert( "Filename", tempPath == Path( "file_name.ext" ) );
		testSuite.EndCase();

		testSuite.BeginCase( "FilenameNoExtension - 1. Full path." );
		tempPath = Path(  path.FilenameNoExtension() );
		testSuite.Assert( "FilenameNoExt", tempPath.ToString() == "file_name" );
		testSuite.EndCase();

		testSuite.BeginCase( "Path slashs equivalency" );
		testSuite.Assert( "\"\\file\" == \"/file\"", Path( "\\file" ) == Path( "/file" ) );
		testSuite.EndCase();

		testSuite.BeginCase( "Combine" );
		{
			tempPath.Combine( Path( "c:\\directory\\subdirectory" ) , unify::Path( "/file_name.ext" ) );
			testSuite.Assert( "Complete L (without ending slash) and R (with leading slash)", tempPath == Path( "c:\\directory\\subdirectory\\file_name.ext" ) );
		
			tempPath.Combine( Path( "c:\\directory\\subdirectory\\" ) , unify::Path( "/file_name.ext" ) );
			testSuite.Assert( "Complete L (with ending slash) and R (with leading slash)", tempPath == Path( "c:\\directory\\subdirectory\\file_name.ext" ) );

			tempPath.Combine( Path( "c:\\directory\\subdirectory" ), unify::Path( "file_name.ext" ) );
			testSuite.Assert( "Complete L( without ending slash ) and R( without leading slash )", tempPath == Path( "c:\\directory\\subdirectory\\file_name.ext" ) );
		}
		testSuite.EndCase();

		testSuite.BeginCase( "Split" );
		const Path pathInputA( "c:\\directory\\subdirectory/..\\test\\file_name.ext" );
		vector< string > partsOutput = pathInputA.Split();
		cout << "results: ";
		//for ( const auto itr = partsOutput.begin(), end = partsOutput.end(); itr != end; ++itr )
		for( const auto i : pathInputA.Split() )
		{
			cout << "[" << i << "]";
		}
		testSuite.EndCase();

		testSuite.BeginCase( "Join()" );
		cout << "result: \"" << Path( partsOutput ) << endl << endl;
		testSuite.EndCase();

		testSuite.BeginCase( "Normalize" );
		cout << "result: \"" << Path( pathInputA ).Normalize() << endl << endl;
		testSuite.EndCase();

		testSuite.BeginCase( "Combine" );
		tempPath.Combine( Path( "c:\\directory\\subdirectory" ) , Path( "..\\test\\file_name.ext" ) );
		cout << "result: \"" << tempPath << "\"." << endl << endl;
		testSuite.EndCase();

		testSuite.BeginCase( "IsExtension - 1. Path has extension, ext has no dot (.)." );
		testBool = path.IsExtension( "ext" );
		cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;
		testSuite.EndCase();

		testSuite.BeginCase( "IsExtension - 2. Path has extension, ext has dot(.)." );
		testBool = path.IsExtension( ".ext" );
		cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;
		testSuite.EndCase();

		testSuite.BeginCase( "IsExtension - 1. Not match." );
		testBool = path.IsExtension( "etx" );
		cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;
		testSuite.EndCase();

		{
			testSuite.BeginCase( "Exists" );
			Path file( "test.txt" );
			ofstream stream;
			stream.open( file.ToString() );
			stream << "Hello, world!";
			stream.close();
			cout << "result: " << ( file.Exists() ? "pass" : "failed" ) << endl;
			testSuite.EndCase();

			testSuite.BeginCase( "Rename" );
			Path fileTo( "test_renamed.txt" );
			if( ! Path::Rename( file, fileTo ) || ! fileTo.Exists() )
			{
				cout << "  result: fail" << endl;
			}
			else
			{
				cout << "  result: pass" << endl;
			}
			testSuite.EndCase();

			testSuite.BeginCase( "Delete" );
			if( !Path::Delete( fileTo ) || fileTo.Exists() )
			{
				cout << "  result: fail" << endl;
			}
			else
			{
				cout << "  result: pass" << endl;
			}
			testSuite.EndCase();
		}
	}
	testSuite.EndSuite();

	cout << "Press any Enter to finish...\n";
	cin.ignore();

	return 0;
}