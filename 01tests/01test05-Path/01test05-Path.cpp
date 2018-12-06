// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
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
		Path tempPath;
		const Path pathA{ "c:/directory/sub_directory/file_name.ext" };

		suite.BeginCase( "IsXPath" );
		{
			suite.Assert( "True", Path::IsXPath( Path::XPathPrefix + "passes.ext"  ) );
			suite.Assert( "False", ! Path::IsXPath( "fails.ext" ) );
		}
		suite.EndCase();

		suite.BeginCase( "XPath and string conversion" );
		{
			suite.Assert( "ToString", pathA.ToString() == "c:/directory/sub_directory/file_name.ext" );
			suite.Assert( "ToString Forward", pathA.ToString( Slash::Foward ) == "c:\\directory\\sub_directory\\file_name.ext" );
			suite.Assert( "ToString Backward", pathA.ToString( Slash::Backward ) == "c:/directory/sub_directory/file_name.ext" );
			suite.Assert( "ToXPath", pathA.ToXPath() == Path::XPathPrefix + "c:/directory/sub_directory/file_name.ext" );
		}
		suite.EndCase();

		suite.BeginCase( "ostream operator<<" );
		{
			cout << "result: \"" << pathA << "\"." << endl << endl;
		}
		suite.EndCase();

		suite.BeginCase( "ExtensionOnly" );
		{
			std::string tempString = pathA.ExtensionOnly();
			suite.Assert( "Extenion only", tempString == ".ext" );
		}
		suite.EndCase();

		suite.BeginCase( "ExtensionOnly with no extension on path" );
		{
			std::string tempString = Path( "c:/directory/sub_directory/" ).ExtensionOnly();
			suite.Assert( "ExtionOnly with no extention on path", tempString == "" );
		}
		suite.EndCase();

		{
			suite.BeginCase( "DirectoryOnly" );
			Path tempPath = pathA.DirectoryOnly();
			suite.Assert( pathA.ToXPath(), pathA.DirectoryOnly() == Path( "c:/directory/sub_directory/" ) );
			suite.Assert( "DirectoryOnly", Path( "file://" ).DirectoryOnly().ToString() == "");
			suite.EndCase();
		}

		suite.BeginCase( "Filename" );
		tempPath = Path( pathA.Filename() );
		suite.Assert( "Filename", tempPath == Path( "file_name.ext" ) );
		suite.EndCase();

		suite.BeginCase( "FilenameNoExtension - 1. Full path." );
		tempPath = Path( pathA.FilenameNoExtension() );
		suite.Assert( "FilenameNoExt", tempPath.ToString() == "file_name" );
		suite.EndCase();

		suite.BeginCase( "Path slashs equivalency" );
		suite.Assert( "\"\\file\" == \"/file\"", Path( "\\file" ) == Path( "/file" ) );
		suite.EndCase();

		suite.BeginCase( "Combine" );
		{
			tempPath.Combine( Path( "c:/directory/subdirectory" ) , unify::Path( "/file_name.ext" ) );
			suite.Assert( "Complete L (without ending slash) and R (with leading slash)", tempPath == Path( "c:/directory/subdirectory/file_name.ext" ) );
		
			tempPath.Combine( Path( "c:/directory/subdirectory/" ) , unify::Path( "/file_name.ext" ) );
			suite.Assert( "Complete L (with ending slash) and R (with leading slash)", tempPath == Path( "c:/directory/subdirectory/file_name.ext" ) );

			tempPath.Combine( Path( "c:/directory/subdirectory" ), unify::Path( "file_name.ext" ) );
			suite.Assert( "Complete L( without ending slash ) and R( without leading slash )", tempPath == Path( "c:/directory/subdirectory/file_name.ext" ) );
		}
		suite.EndCase();

		suite.BeginCase( "Split" );
		const Path pathInputA( "c:\\directory\\subdirectory/..\\test\\file_name.ext" );
		vector< string > partsExpected{ "c:/", "directory/", "subdirectory/", "../", "test/", "file_name.ext" };

		vector< string > partsOutput = pathInputA.Split();
		bool isMatch = true;
		for ( size_t i = 0; i < partsExpected.size() && isMatch; ++i )
		{
			if ( partsExpected[ i ] != partsOutput[ i ] )
			{
				isMatch = false;
			}
		}
		suite.Assert( "Is match", isMatch );
		suite.EndCase();

		suite.BeginCase( "Join" );
		suite.Assert( "Join", Path( partsOutput ) == pathInputA );
		suite.EndCase();

		suite.BeginCase( "Normalize" );
		suite.Assert( "Normalize", Path( pathInputA ).Normalize().ToString() == "c:/directory/test/file_name.ext" );
		suite.EndCase();

		suite.BeginCase( "Combine" );
		tempPath.Combine( Path( "c:\\directory\\subdirectory" ), Path( "..\\test\\file_name.ext" ) );
		suite.Assert( "Combine", tempPath.ToString() == pathInputA.ToString() );
		suite.EndCase();

		{
			suite.BeginCase( "IsExtension" );
			suite.Assert( "Path has extension, ext has no dot( . )", pathA.IsExtension( "ext" ) );
			suite.Assert( "Path has extension, ext has dot(.)", pathA.IsExtension( ".ext" ) );
			suite.Assert( "Not match.", ! pathA.IsExtension( "etx" ) );
			suite.EndCase();
		}

		{
			suite.BeginCase( "Exists" );
			Path file( "test.txt" );
			ofstream stream;
			stream.open( file.ToString() );
			stream << "Hello, world!";
			stream.close();
			suite.Assert( "File exists", file.Exists() );
			suite.Assert( "File doesn't exist", "doesnt_exist.ext" );
			suite.EndCase();

			suite.BeginCase( "Rename" );
			Path fileTo( "test_renamed.txt" );
			suite.Assert( "Rename file", file.Rename( fileTo ) && fileTo.Exists() );
			suite.EndCase();

			suite.BeginCase( "Delete" );
			suite.Assert( "Delete file", fileTo.Delete() && !fileTo.Exists() );
			suite.EndCase();
		}

		suite.BeginCase( "Operators" );
		{
			suite.Assert( "equality (==)", Path( "c:/file_name.ext" ) == Path( "c:/file_name.ext" ) );
			suite.Assert( "\"c:/\" + \"file_name.ext\"", Path( "c:" ) + Path( "file_name.ext" ) == Path( "c:/file_name.ext" ) );
			suite.Assert( "\"file://\" + \"file://file_name.ext\"", Path( "file://" ) + Path( "file_name.ext" ) == Path( "file://file_name.ext" ) );
		}
		suite.EndCase();
	}
	suite.EndSuite();

	cout << "Press any Enter to finish...\n";
	while( ! _getch() );

	return 0;
}