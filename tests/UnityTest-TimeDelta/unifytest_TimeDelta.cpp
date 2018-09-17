// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test unify::TimeDelta.
//

#include <iostream>
#include <string>
#include <unify/String.h>
#include <unify/TestSuite.h>

int main( int argc, char ** argv )
{
	using namespace unify;

	TestSuite testSuite( "unify::TimeDelta", "   " );

	testSuite.BeginSuite();
	{
		testSuite.BeginCase( "Constructors" );
		{
			{
				auto zero = TimeDelta();
				auto ms = TimeDeltaInMS( 0 );
				testSuite.Assert( "Zero", zero == ms );
			} 
			{
				auto ms = TimeDeltaInMS( 1000 );
				auto seconds = TimeDeltaInSeconds( 1 );
				testSuite.Assert( "MS to seconds", ms == seconds );
			}
			{
				auto seconds = TimeDeltaInSeconds( 60 );
				auto minutes = TimeDeltaInMinutes( 1 );
				testSuite.Assert( "Seconds to minutes", seconds == minutes );
			}
			{
				auto minutes = TimeDeltaInMinutes( 60 );
				auto hours = TimeDeltaInHours( 1 );
				testSuite.Assert( "minutes to hours", minutes == hours );
			}
			{
				auto hours = TimeDeltaInHours( 24 );
				auto days = TimeDeltaInDays( 1 );
				testSuite.Assert( "hours to days", hours == days );
			}
			{
				auto days = TimeDeltaInDays( 7 );
				auto weeks = TimeDeltaInWeeks( 1 );
				testSuite.Assert( "days to weeks", days == weeks );
			}
			{
				auto days = TimeDeltaInDays( 365 );
				auto years = TimeDeltaInYears( 1 );
				testSuite.Assert( "days to years", days == years );
			}
			{
				auto days = TimeDeltaInDays( 365 );
				auto years = TimeDeltaInYears( 1 );
				testSuite.Assert( "days to years", days == years );
			}
		}
		testSuite.EndCase();
	}
	testSuite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	std::cin.ignore();

	return 0;
}