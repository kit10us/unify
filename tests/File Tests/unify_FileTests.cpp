#include <unify/Path.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

int main( const int argc, const char ** argv )
{
	std::string tempString;
	unify::Path tempPath;
	bool testBool;

	std::cout << "Begin Unify File Tests:" << std::endl;
	
	std::cout << "Test case: file::ToString...:" << std::endl;
	const unify::Path path( "c:\\directory\\sub_directory\\file_name.ext" );
	std::cout << "result: \"" << path.ToString() << "\"." << std::endl << std::endl;

	std::cout << "Test case: ostream operator<<(Path)...:" << std::endl;
	std::cout << "result: \"" << path << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::ExtensionOnly( \"" << path << "\" )" << std::endl;
	tempString = path.ExtensionOnly();
	std::cout << "result: \"" << tempString << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::ExtensionOnly( \"c:\\directory\\sub_directory\\\" )" << std::endl;
	tempString = unify::Path( "c:\\directory\\sub_directory\\" ).ExtensionOnly();
	std::cout << "result: \"" << tempString << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::DirectoryOnly( \"" << path << "\" )" << std::endl;
	tempPath = path.DirectoryOnly();
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::Filename( \"" << path << "\" )" << std::endl;
	tempPath = unify::Path( path.Filename() );
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::FilenameNoExtension - 1. Full path." << std::endl;
	tempPath = unify::Path(  path.FilenameNoExtension() );
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::Combine - 1. Complete L (without ending slash) and R (with leading slash)." << std::endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory" ) , unify::Path( "/file_name.ext" ) );
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::Combine - 2. Complete L (with ending slash) and R (with leading slash)." << std::endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory\\" ) , unify::Path( "/file_name.ext" ) );
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::Combine - 3. Complete L (without ending slash) and R (without leading slash)." << std::endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory" ), unify::Path( "file_name.ext" ) );
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	const unify::Path pathInputA( "c:\\directory\\subdirectory/..\\test\\file_name.ext" );
	std::cout << "Test case: file::Split( \"" << pathInputA << "\" )" << std::endl;
	std::vector< std::string > partsOutput = pathInputA.Split();
	std::cout << "results: ";
	//for ( const auto itr = partsOutput.begin(), end = partsOutput.end(); itr != end; ++itr )
	for( const auto i : pathInputA.Split() )
	{
		std::cout << "[" << i << "]";
	}
	std::cout << std::endl << std::endl;

	std::cout << "Test case: file::Join( file::Split( \"" << pathInputA << "\" ) )" << std::endl;
	std::cout << "result: \"" << unify::Path( partsOutput ) << std::endl << std::endl;

	std::cout << "Test case: file::Normalize( \"" << pathInputA << "\" )" << std::endl;
	std::cout << "result: \"" << unify::Path( pathInputA ).Normalize() << std::endl << std::endl;

	std::cout << "Test case: file::Combine( \"c:\\directory\\subdirectory\", \"..\\test\\file_name.ext\" )" << std::endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory" ) , unify::Path( "..\\test\\file_name.ext" ) );
	std::cout << "result: \"" << tempPath << "\"." << std::endl << std::endl;

	std::cout << "Test case: file::IsExtension - 1. Path has extension, ext has no dot (.)." << std::endl;
	testBool = path.IsExtension( "ext" );
	std::cout << "result: " << ( testBool ? "true" : "false" ) << "." << std::endl << std::endl;

	std::cout << "Test case: file::IsExtension - 2. Path has extension, ext has dot(.)." << std::endl;
	testBool = path.IsExtension( ".ext" );
	std::cout << "result: " << ( testBool ? "true" : "false" ) << "." << std::endl << std::endl;

	std::cout << "Test case: file::IsExtension - 1. Not match." << std::endl;
	testBool = path.IsExtension( "etx" );
	std::cout << "result: " << ( testBool ? "true" : "false" ) << "." << std::endl << std::endl;

	{
		std::cout << "Test case: file::Exists." << std::endl;

		unify::Path file( "test.txt" );
		std::ofstream stream;
		stream.open( file.ToString() );
		stream << "Hello, world!";
		stream.close();
		std::cout << "result: " << ( file.Exists() ? "pass" : "failed" ) << std::endl;
		
		std::cout << "Test case: file::Rename." << std::endl;
		unify::Path fileTo( "test_renamed.txt" );
		if( ! unify::Path::Rename( file, fileTo ) || ! fileTo.Exists() )
		{
			std::cout << "  result: fail" << std::endl;
		}
		else
		{
			std::cout << "  result: pass" << std::endl;
		}

		std::cout << "Test case: file::Delete." << std::endl;
		if( !unify::Path::Delete( fileTo ) || fileTo.Exists() )
		{
			std::cout << "  result: fail" << std::endl;
		}
		else
		{
			std::cout << "  result: pass" << std::endl;
		}

	}

	while( ! _getch() );

	return 0;
}