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


#pragma once

#include <unify/Unify.h>
#include <unify/Cast.h>

namespace unify
{
    class TimeDelta
    {
	public:
		friend TimeDelta TimeDeltaInMicros( float micros );
		friend TimeDelta TimeDeltaInMS( float ms );
		friend TimeDelta TimeDeltaInSeconds( float seconds );
		friend TimeDelta TimeDeltaInMinutes( float seconds );
		friend TimeDelta TimeDeltaInHours( float hours );
		friend TimeDelta TimeDeltaInWeeks( float weeks );
		friend TimeDelta TimeDeltaInDays( float days );
		friend TimeDelta TimeDeltaInYears( float years );

    public:
		TimeDelta(float ms);
		TimeDelta();

		float GetMicros() const;
        float GetMS() const;
        float GetSeconds() const;
		float GetMinutes() const;
		float GetHours() const;
		float GetWeeks() const;
		float GetDays() const;
		float GetYears() const;

		TimeDelta operator+( TimeDelta delta ) const;
		TimeDelta operator-( TimeDelta delta ) const;
		float operator/( TimeDelta delta ) const;
		TimeDelta & operator+=( TimeDelta delta );
		TimeDelta & operator-=( TimeDelta delta );

		TimeDelta operator * ( float times ) const;
		TimeDelta operator / ( float times ) const;
		TimeDelta & operator *= ( float times );
		TimeDelta & operator /= ( float times );

		bool operator == ( TimeDelta delta ) const;
		bool operator != ( TimeDelta delta ) const;
		bool operator > ( TimeDelta delta ) const;
		bool operator < ( TimeDelta delta ) const;
		bool operator >= ( TimeDelta delta ) const;
		bool operator <= ( TimeDelta delta ) const;

	private:
		float m_ms;
    };

	TimeDelta TimeDeltaInMicros(float micros);
	TimeDelta TimeDeltaInMS( float ms );
	TimeDelta TimeDeltaInSeconds( float seconds );
	TimeDelta TimeDeltaInMinutes( float minutes );
	TimeDelta TimeDeltaInHours( float hours );
	TimeDelta TimeDeltaInWeeks( float weeks );
	TimeDelta TimeDeltaInDays( float days );
	TimeDelta TimeDeltaInYears( float years );

	template< typename TTo, typename TFrom > TTo Cast(const TFrom in);
	template<> std::string unify::Cast(const TimeDelta in);
	template<> TimeDelta Cast(const std::string text);
	template<> TimeDelta Cast(const char* text);
}