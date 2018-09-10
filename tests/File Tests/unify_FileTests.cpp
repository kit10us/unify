// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <unify/Path.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

int main( int argc, char ** argv )
{
	using namespace std;

	string tempString;
	unify::Path tempPath;
	bool testBool;

	cout << "Begin Unify File Tests:" << endl;
	
	cout << "Test case: file::ToString...:" << endl;
	const unify::Path path( "c:\\directory\\sub_directory\\file_name.ext" );
	cout << "result: \"" << path.ToString() << "\"." << endl << endl;

	cout << "Test case: ostream operator<<(Path)...:" << endl;
	cout << "result: \"" << path << "\"." << endl << endl;

	cout << "Test case: file::ExtensionOnly( \"" << path << "\" )" << endl;
	tempString = path.ExtensionOnly();
	cout << "result: \"" << tempString << "\"." << endl << endl;

	cout << "Test case: file::ExtensionOnly( \"c:\\directory\\sub_directory\\\" )" << endl;
	tempString = unify::Path( "c:\\directory\\sub_directory\\" ).ExtensionOnly();
	cout << "result: \"" << tempString << "\"." << endl << endl;

	cout << "Test case: file::DirectoryOnly( \"" << path << "\" )" << endl;
	tempPath = path.DirectoryOnly();
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	cout << "Test case: file::Filename( \"" << path << "\" )" << endl;
	tempPath = unify::Path( path.Filename() );
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	cout << "Test case: file::FilenameNoExtension - 1. Full path." << endl;
	tempPath = unify::Path(  path.FilenameNoExtension() );
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	cout << "Test case: file::Combine - 1. Complete L (without ending slash) and R (with leading slash)." << endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory" ) , unify::Path( "/file_name.ext" ) );
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	cout << "Test case: file::Combine - 2. Complete L (with ending slash) and R (with leading slash)." << endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory\\" ) , unify::Path( "/file_name.ext" ) );
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	cout << "Test case: file::Combine - 3. Complete L (without ending slash) and R (without leading slash)." << endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory" ), unify::Path( "file_name.ext" ) );
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	const unify::Path pathInputA( "c:\\directory\\subdirectory/..\\test\\file_name.ext" );
	cout << "Test case: file::Split( \"" << pathInputA << "\" )" << endl;
	vector< string > partsOutput = pathInputA.Split();
	cout << "results: ";
	//for ( const auto itr = partsOutput.begin(), end = partsOutput.end(); itr != end; ++itr )
	for( const auto i : pathInputA.Split() )
	{
		cout << "[" << i << "]";
	}
	cout << endl << endl;

	cout << "Test case: file::Join( file::Split( \"" << pathInputA << "\" ) )" << endl;
	cout << "result: \"" << unify::Path( partsOutput ) << endl << endl;

	cout << "Test case: file::Normalize( \"" << pathInputA << "\" )" << endl;
	cout << "result: \"" << unify::Path( pathInputA ).Normalize() << endl << endl;

	cout << "Test case: file::Combine( \"c:\\directory\\subdirectory\", \"..\\test\\file_name.ext\" )" << endl;
	tempPath.Combine( unify::Path( "c:\\directory\\subdirectory" ) , unify::Path( "..\\test\\file_name.ext" ) );
	cout << "result: \"" << tempPath << "\"." << endl << endl;

	cout << "Test case: file::IsExtension - 1. Path has extension, ext has no dot (.)." << endl;
	testBool = path.IsExtension( "ext" );
	cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;

	cout << "Test case: file::IsExtension - 2. Path has extension, ext has dot(.)." << endl;
	testBool = path.IsExtension( ".ext" );
	cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;

	cout << "Test case: file::IsExtension - 1. Not match." << endl;
	testBool = path.IsExtension( "etx" );
	cout << "result: " << ( testBool ? "true" : "false" ) << "." << endl << endl;

	{
		cout << "Test case: file::Exists." << endl;

		unify::Path file( "test.txt" );
		ofstream stream;
		stream.open( file.ToString() );
		stream << "Hello, world!";
		stream.close();
		cout << "result: " << ( file.Exists() ? "pass" : "failed" ) << endl;
		
		cout << "Test case: file::Rename." << endl;
		unify::Path fileTo( "test_renamed.txt" );
		if( ! unify::Path::Rename( file, fileTo ) || ! fileTo.Exists() )
		{
			cout << "  result: fail" << endl;
		}
		else
		{
			cout << "  result: pass" << endl;
		}

		cout << "Test case: file::Delete." << endl;
		if( !unify::Path::Delete( fileTo ) || fileTo.Exists() )
		{
			cout << "  result: fail" << endl;
		}
		else
		{
			cout << "  result: pass" << endl;
		}

	}

	cin.ignore();

	return 0;
}