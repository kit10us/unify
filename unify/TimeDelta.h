// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#pragma once

#include <unify/Unify.h>

namespace unify
{
	typedef float Seconds; // TODO: TEMP

    class TimeDelta
    {
		friend TimeDelta TimeDeltaInMS( float ms );
		friend TimeDelta TimeDeltaInSeconds( float seconds );
		friend TimeDelta TimeDeltaInMinutes( float seconds );
		friend TimeDelta TimeDeltaInHours( float hours );
		friend TimeDelta TimeDeltaInWeeks( float weeks );
		friend TimeDelta TimeDeltaInDays( float days );
		friend TimeDelta TimeDeltaInYears( float years );
		friend TimeDelta TimeDeltaZero();
		friend TimeDelta TimeDeltaOne();

		
		TimeDelta( float ms );
    public:

        float GetMS() const;
        float GetSeconds() const;
		float GetMinutes() const;
		float GetHours() const;
		float GetWeeks() const;
		float GetDays() const;
		float GetYears() const;

		TimeDelta operator+( TimeDelta delta ) const;
		TimeDelta operator-( TimeDelta delta ) const;
		TimeDelta & operator+=( TimeDelta );
		TimeDelta & operator-=( TimeDelta );

		TimeDelta operator * ( float times ) const;
		TimeDelta operator / ( float times ) const;
		TimeDelta & operator *= ( float times );
		TimeDelta & operator /= ( float times );

	private:
		float m_ms;
    };

	TimeDelta TimeDeltaInMS( float ms );
	TimeDelta TimeDeltaInSeconds( float seconds );
	TimeDelta TimeDeltaInMinutes( float seconds );
	TimeDelta TimeDeltaInHours( float hours );
	TimeDelta TimeDeltaInWeeks( float weeks );
	TimeDelta TimeDeltaInDays( float days );
	TimeDelta TimeDeltaInYears( float years );
	TimeDelta TimeDeltaZero();
	TimeDelta TimeDeltaOne();
}