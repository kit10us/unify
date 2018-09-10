// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

#include <unify/Any.h>

#include <iostream>
#include <conio.h>
#include <string>

int main( int argc, char ** argv )
{
	using namespace std;

	unify::Any anyInt12 = 12;

	cout << "Begin Unify Any Tests:" << endl;
	cout << "Is NOT empty: " << (anyInt12.empty() ? "FAIL" : "PASS") << endl;

	cout << "Int match: " << (unify::any_cast< int >(anyInt12) == 12 ? "PASS" : "FAIL" ) << endl;

	 cin.ignore();

	return 0;
}