// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

/// <summary>
/// Test Path.
/// </summary>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unify/Path.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "Path" );

	{
		Path tempPath;
		const Path pathA{ "c:/directory/sub_directory/file_name.ext" };

		suite.BeginCase( "Constructors" );
		{
			{
				suite.TryCatchAssert( "empty constructor",
					[] () -> bool {
						Path path;
						return path.Empty();
					}
				);
			}
			{
				suite.TryCatchAssert( "string constructor",
					[]() -> bool {
					Path path( "c:/file.ext" );
					return !path.Empty() && path == Path( "c:/file.ext" );
				}
				);
			}
			{
				suite.TryCatchAssert( "path concatentation",
					[]() -> bool {
					Path path( Path( "c:/directory" ), Path( "filename.ext" ) );
					return ! path.Empty() & path == Path( "c:/directory/filename.ext" );
				}
				);
			}
			{
				suite.TryCatchAssert( "path of vector parts",
					[]() -> bool {
					Path path( std::vector< std::string >{ "c:/directory", "another", "filename.ext" } );
					return !path.Empty() & path == Path( "c:/directory/another/filename.ext" );
				}
				);
			}
		}

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
			std::cout << "result: \"" << pathA << "\"." << std::endl << std::endl;
		}
		suite.EndCase();

		suite.BeginCase( "Extensions" );
		{
			suite.Assert( "FilenameNoExt", Path( "file_name.ext" ).FilenameNoExtension() == "file_name" );
			suite.Assert( "has extension", pathA.HasExtension() );
			suite.Assert( "has no extension", !Path( "c:/pete/name" ).HasExtension() );
			suite.Assert( "is extension", pathA.IsExtension( ".ext" ) );
			suite.Assert( "not is extension", !pathA.IsExtension( ".txt" ) );
			suite.Assert( "ExtionOnly with no extention on path", Path( "c:/directory/sub_directory/" ).ExtensionOnly() == "" );
			{
				Path changedExtension{ "c:/pete/name.is" };
				changedExtension.ChangeExtension( "txt" );
				suite.Assert( "change extension member", changedExtension.IsExtension( "txt" ) );
			}
			{
				Path changedExtension{ "c:/pete/name" };
				changedExtension.ChangeExtension( "txt" );
				suite.Assert( "change extension (a, b)", changedExtension.IsExtension( "txt" ) );
			}
			suite.Assert( "change extension non member", ChangeExtension( Path( "c:/pete/name.xxx" ), "xtx" ).IsExtension( "xtx" ) );
			suite.Assert( "Extenion only", Path( "c:/pete/name.ext" ).ExtensionOnly() == ".ext" );
		}
		suite.EndCase();

		suite.BeginCase( "ExtensionOnly with no extension on path" );
		{
		}
		suite.EndCase();

		suite.BeginCase( "DirectoryOnly" );
		{
			suite.Assert( pathA.ToXPath(), Path( "c:/directory/sub_directory/filename.ext" ).DirectoryOnly() == Path( "c:/directory/sub_directory/" ) );
			suite.Assert( "DirectoryOnly", Path( Path::XPathPrefix ).DirectoryOnly().ToString() == "");
		}
		suite.EndCase();

		suite.BeginCase( "Filename" );
		tempPath = Path( pathA.Filename() );
		suite.Assert( "Filename", tempPath == Path( "file_name.ext" ) );
		suite.EndCase();

		suite.BeginCase( "Path slashs equivalency" );
		suite.Assert( "\"\\file\" == \"/file\"", Path( "\\file" ) == Path( "/file" ) );
		suite.EndCase();

		suite.BeginCase( "Combine" );
		{
			tempPath.Combine( Path( "c:/directory/subdirectory" ) , Path( "/file_name.ext" ) );
			suite.Assert( "Complete L (without ending slash) and R (with leading slash)", tempPath == Path( "c:/directory/subdirectory/file_name.ext" ) );
		
			tempPath.Combine( Path( "c:/directory/subdirectory/" ) , Path( "/file_name.ext" ) );
			suite.Assert( "Complete L (with ending slash) and R (with leading slash)", tempPath == Path( "c:/directory/subdirectory/file_name.ext" ) );

			tempPath.Combine( Path( "c:/directory/subdirectory" ), Path( "file_name.ext" ) );
			suite.Assert( "Complete L( without ending slash ) and R( without leading slash )", tempPath == Path( "c:/directory/subdirectory/file_name.ext" ) );
		}
		suite.EndCase();

		suite.BeginCase( "Split" );
		const Path pathInputA( "c:\\directory\\subdirectory/..\\test\\file_name.ext" );
		std::vector< std::string > partsExpected{ "c:/", "directory/", "subdirectory/", "../", "test/", "file_name.ext" };

		std::vector< std::string > partsOutput = pathInputA.Split();
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
			std::ofstream stream;
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
			suite.Assert( Path::XPathPrefix + "\" + \"" + Path::XPathPrefix + "file_name.ext", Path( Path::XPathPrefix ) + Path( "file_name.ext" ) == Path( "file_name.ext" ) );
		}
		suite.EndCase();
	}
	suite.EndSuite();

	return 0;
}