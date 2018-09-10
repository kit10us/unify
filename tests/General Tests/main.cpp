// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <unify/Color.h>
#include <unify/ColorUnit.h>
#include <unify/V2.h>
#include <unify/Parameters.h>
#include <unify/Optional.h>
#include <iostream>
#include <conio.h>

int main( int argc, char ** argv )
{
	using namespace std;

	cout << "String unit tests:" << endl;
	cout << "CleanWhitespace text: expected \"no whitespace\", is \"" << unify::CleanWhitespace( " \t \t \n  no \t  \t whitespace \t \t \n \n  " ) << "\"" << endl;
	cout << "float conversion: expected 12.21, is \"" << unify::Cast< string >( unify::Cast< float >( "   12.21  " ) ) << "\"" << endl;
	cout << "unsigned char conversion: expected 12, is \"" << unify::Cast< string >( unify::Cast< unsigned char >( "   12  " ) ) << "\"" << endl;
	cout << "int conversion: expected 12, is \"" << unify::Cast< string >( unify::Cast< int >( "   12  " ) ) << "\"" << endl;
	cout << "bool conversion: expected true, is \"" << unify::Cast< string >( unify::Cast< bool >( "   true  " ) ) << "\"" << endl;
	cout << "bool conversion: expected false, is \"" << unify::Cast< string >( unify::Cast< bool >( "   false  " ) ) << "\"" << endl;
	cout << "Begins with: expected \"true\", is \"" << unify::Cast< string >( unify::BeginsWith( "a new town", "a ne" ) ) << "\"" << endl;
	cout << "Begins with: expected \"false\", is \"" << unify::Cast< string >( unify::BeginsWith( "a new town", "new " ) ) << "\"" << endl;
	cout << "Ends with: expected \"true\", is \"" << unify::Cast< string >( unify::EndsWith( "a new town", " town" ) ) << "\"" << endl;
	cout << "Ends with: expected \"false\", is \"" << unify::Cast< string >( unify::EndsWith( "a new town", "new " ) ) << "\"" << endl;
	cout << "ToLower: excected \"all lower case, zero upper!\", is \"" << unify::ToLower( "All Lower Case, Zero UPPER!" ) << "\"" << endl;

	cout << endl << endl;

	cout << "Color unit tests:" << endl;
	cout << "Color from text: expected \"255, 127, 63, 31\", is \"" << unify::Color( "255, 127, 63, 31" ).ToString() << "\"" << endl; 

	cout << endl << endl;

	cout << "ColorUnit unit tests:" << endl;
	cout << "ColorUnit from text: expected \"1.0, 0.5, 0.25, 0.125\", is \"" << unify::ColorUnit( "1, 0.5, 0.25, 0.125" ).ToString() << "\"" << endl; 

	cout << endl << endl;

	cout << "Parameters unit tests:" << endl;
	unify::Parameters parameters;
	parameters.Set( "first", 1234567 );
	parameters.Set( "second", "second" );
	parameters.Set( "third", 3.33f );

	cout << "Value of \"first\" should be \"1234567\"... \"" << unify::Cast< string >( parameters.Get< int >( "first" ) ) << "\"" << endl;
	cout << "\"second\" should exists... " << unify::Cast< string >( parameters.Exists( "second" ) ) << endl;

	// Optional test...
	{
		/*
		TODO: When used, so we know what we need to test.
		unify::Optional< int > optionalInt12 = 12;
		unify::Optional< int > optionalInt;
		cout << "Optional< int >( ) == Not Set : " << (optionalInt.IsSet() ? "FAIL" : "PASS") << endl;
		cout << "Optional< int >( 12 ) == 12 : " << (optionalInt12 == 12 ? "PASS" : "FAIL") << endl;
		*/
	}

	cin.ignore();

    return 0;
}