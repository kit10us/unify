// Copyright (c) 2002 - 2018, Evil Quail LLC
// All Rights Reserved

//
// Purpose of test...
//    Test TimeDelta.
//

#include <conio.h>
#include <string>
#include <unify/String.h>
#include <unify/test/Suite.h>

int main( int argc, char ** argv )
{
	using namespace unify;
	using namespace test;

	Suite suite;

	suite.BeginSuite( "TimeDelta" );
	{
		suite.BeginCase( "Constructors" );
		{
			{
				auto zero = TimeDelta();
				auto ms = TimeDeltaInMS( 0 );
				suite.Assert( "Zero", zero == ms );
			} 
			{
				auto ms = TimeDeltaInMS( 1000 );
				auto seconds = TimeDeltaInSeconds( 1 );
				suite.Assert( "MS to seconds", ms == seconds );
			}
			{
				auto seconds = TimeDeltaInSeconds( 60 );
				auto minutes = TimeDeltaInMinutes( 1 );
				suite.Assert( "Seconds to minutes", seconds == minutes );
			}
			{
				auto minutes = TimeDeltaInMinutes( 60 );
				auto hours = TimeDeltaInHours( 1 );
				suite.Assert( "minutes to hours", minutes == hours );
			}
			{
				auto hours = TimeDeltaInHours( 24 );
				auto days = TimeDeltaInDays( 1 );
				suite.Assert( "hours to days", hours == days );
			}
			{
				auto days = TimeDeltaInDays( 7 );
				auto weeks = TimeDeltaInWeeks( 1 );
				suite.Assert( "days to weeks", days == weeks );
			}
			{
				auto days = TimeDeltaInDays( 365 );
				auto years = TimeDeltaInYears( 1 );
				suite.Assert( "days to years", days == years );
			}
			{
				auto days = TimeDeltaInDays( 365 );
				auto years = TimeDeltaInYears( 1 );
				suite.Assert( "days to years", days == years );
			}
		}
		suite.EndCase();
	}
	suite.EndSuite();

	std::cout << "Press any Enter to finish...\n";
	while( !_getch() );

	return 0;
}