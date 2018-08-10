#include <unify/Color.h>
#include <unify/ColorUnit.h>
#include <unify/V2.h>
#include <unify/Parameters.h>
#include <unify/Optional.h>
#include <iostream>
#include <conio.h>

int main( int argc, char ** argv )
{
	std::cout << "String unit tests:" << std::endl;
	std::cout << "CleanWhitespace text: expected \"no whitespace\", is \"" << unify::CleanWhitespace( " \t \t \n  no \t  \t whitespace \t \t \n \n  " ) << "\"" << std::endl;
	std::cout << "float conversion: expected 12.21, is \"" << unify::Cast< std::string >( unify::Cast< float >( "   12.21  " ) ) << "\"" << std::endl;
	std::cout << "unsigned char conversion: expected 12, is \"" << unify::Cast< std::string >( unify::Cast< unsigned char >( "   12  " ) ) << "\"" << std::endl;
	std::cout << "int conversion: expected 12, is \"" << unify::Cast< std::string >( unify::Cast< int >( "   12  " ) ) << "\"" << std::endl;
	std::cout << "bool conversion: expected true, is \"" << unify::Cast< std::string >( unify::Cast< bool >( "   true  " ) ) << "\"" << std::endl;
	std::cout << "bool conversion: expected false, is \"" << unify::Cast< std::string >( unify::Cast< bool >( "   false  " ) ) << "\"" << std::endl;
	std::cout << "Begins with: expected \"true\", is \"" << unify::Cast< std::string >( unify::BeginsWith( "a new town", "a ne" ) ) << "\"" << std::endl;
	std::cout << "Begins with: expected \"false\", is \"" << unify::Cast< std::string >( unify::BeginsWith( "a new town", "new " ) ) << "\"" << std::endl;
	std::cout << "Ends with: expected \"true\", is \"" << unify::Cast< std::string >( unify::EndsWith( "a new town", " town" ) ) << "\"" << std::endl;
	std::cout << "Ends with: expected \"false\", is \"" << unify::Cast< std::string >( unify::EndsWith( "a new town", "new " ) ) << "\"" << std::endl;
	std::cout << "ToLower: excected \"all lower case, zero upper!\", is \"" << unify::ToLower( "All Lower Case, Zero UPPER!" ) << "\"" << std::endl;

	std::cout << std::endl << std::endl;

	std::cout << "Color unit tests:" << std::endl;
	std::cout << "Color from text: expected \"255, 127, 63, 31\", is \"" << unify::Color( "255, 127, 63, 31" ).ToString() << "\"" << std::endl; 

	std::cout << std::endl << std::endl;

	std::cout << "ColorUnit unit tests:" << std::endl;
	std::cout << "ColorUnit from text: expected \"1.0, 0.5, 0.25, 0.125\", is \"" << unify::ColorUnit( "1, 0.5, 0.25, 0.125" ).ToString() << "\"" << std::endl; 

	std::cout << std::endl << std::endl;

	std::cout << "Parameters unit tests:" << std::endl;
	unify::Parameters parameters;
	parameters.Set( "first", 1234567 );
	parameters.Set( "second", "second" );
	parameters.Set( "third", 3.33f );

	std::cout << "Value of \"first\" should be \"1234567\"... \"" << unify::Cast< std::string >( parameters.Get< int >( "first" ) ) << "\"" << std::endl;
	std::cout << "\"second\" should exists... " << unify::Cast< std::string >( parameters.Exists( "second" ) ) << std::endl;

	// Optional test...
	{
		/*
		TODO: When used, so we know what we need to test.
		unify::Optional< int > optionalInt12 = 12;
		unify::Optional< int > optionalInt;
		std::cout << "Optional< int >( ) == Not Set : " << (optionalInt.IsSet() ? "FAIL" : "PASS") << std::endl;
		std::cout << "Optional< int >( 12 ) == 12 : " << (optionalInt12 == 12 ? "PASS" : "FAIL") << std::endl;
		*/
	}

	while( ! _getch() );

    return 0;
}