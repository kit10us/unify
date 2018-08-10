#include <unify/Any.h>

#include <iostream>
#include <conio.h>
#include <string>

int main( const int argc, const char ** argv )
{
	unify::Any anyInt12 = 12;

	std::cout << "Begin Unify Any Tests:" << std::endl;
	std::cout << "Is NOT empty: " << (anyInt12.empty() ? "FAIL" : "PASS") << std::endl;

	std::cout << "Int match: " << (unify::any_cast< int >(anyInt12) == 12 ? "PASS" : "FAIL" ) << std::endl;

	while( ! _getch() );

	return 0;
}