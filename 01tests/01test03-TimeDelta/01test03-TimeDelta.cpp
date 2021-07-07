/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */


/// <summary>
/// Test TimeDelta.
/// </summary>

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

	return 0;
}