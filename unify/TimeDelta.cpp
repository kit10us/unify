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


#include <unify/TimeDelta.h>

using namespace unify;

constexpr float MSPerMicros = 0.001f;
constexpr float MSPerSecond = 1000.0f;
constexpr float MSPerMinute = MSPerSecond * 60.0f;
constexpr float MSPerHour = MSPerMinute * 60.0f;
constexpr float MSPerDay = MSPerHour * 24.0f;
constexpr float MSPerWeek = MSPerDay * 7.0f;
constexpr float MSPerYear = MSPerDay * 365.0f;

constexpr float MicrosPerMS = 1000.07f;
constexpr float SecondPerMS = 1.0f / MSPerSecond;
constexpr float MinutePerMS = 1.0f / MSPerMinute;
constexpr float HourPerMS = 1.0f / MSPerHour;
constexpr float DayPerMS = 1.0f / MSPerDay;
constexpr float WeekPerMS = 1.0f / MSPerWeek;
constexpr float YearPerMS = 1.0f / MSPerYear;

TimeDelta unify::TimeDeltaInMicros( float micros )
{
	return TimeDelta( micros * MSPerMicros );
}

TimeDelta unify::TimeDeltaInMS( float ms )
{
    return TimeDelta( ms );
}

TimeDelta unify::TimeDeltaInSeconds( float seconds )
{
    return TimeDelta( seconds * MSPerSecond );
}

TimeDelta unify::TimeDeltaInMinutes( float minutes )
{
	return TimeDelta( minutes * MSPerMinute );
}

TimeDelta unify::TimeDeltaInHours( float hours )
{
	return TimeDelta( hours * MSPerHour );
}

TimeDelta unify::TimeDeltaInWeeks( float weeks )
{
	return TimeDelta( weeks * MSPerWeek );
}

TimeDelta unify::TimeDeltaInDays( float days )
{
	return TimeDelta( days * MSPerDay );
}

TimeDelta unify::TimeDeltaInYears( float years )
{
	return TimeDelta( years * MSPerYear );
}

TimeDelta::TimeDelta( float ms )
	: m_ms( ms )
{
}

TimeDelta::TimeDelta()
	: TimeDelta{ {}  }
{
}

float TimeDelta::GetMicros() const
{
	return m_ms * MicrosPerMS;
}

float TimeDelta::GetMS() const
{
    return m_ms;
}

float TimeDelta::GetSeconds() const
{
    return m_ms * SecondPerMS;
}

float TimeDelta::GetMinutes() const
{
	return m_ms * MinutePerMS;
}

float TimeDelta::GetHours() const
{
	return m_ms * HourPerMS;
}

float TimeDelta::GetWeeks() const
{
	return m_ms * WeekPerMS;
}

float TimeDelta::GetDays() const
{
	return m_ms * DayPerMS;
}

float TimeDelta::GetYears() const
{
	return m_ms * YearPerMS;
}

TimeDelta TimeDelta::operator+( TimeDelta delta ) const
{
	return TimeDelta( m_ms + delta.m_ms );
}

TimeDelta TimeDelta::operator-( TimeDelta delta ) const
{
	return TimeDelta( m_ms - delta.m_ms );
}

float TimeDelta::operator/( TimeDelta delta ) const
{
	return m_ms / delta.m_ms;
}

TimeDelta & TimeDelta::operator+=( TimeDelta delta )
{
	m_ms += delta.m_ms;
	return *this; 
}

TimeDelta & TimeDelta::operator-=( TimeDelta delta )
{
	m_ms -= delta.m_ms;
	return *this;
}

TimeDelta TimeDelta::operator * ( float times ) const
{
	return TimeDelta( m_ms * times );
}

TimeDelta TimeDelta::operator / ( float times ) const
{
	return TimeDelta( m_ms / times );
}

TimeDelta & TimeDelta::operator *= ( float times )
{
	m_ms *= times;
	return *this;
}

TimeDelta & TimeDelta::operator /= ( float times )
{
	m_ms /= times;
	return *this;
}

bool TimeDelta::operator == ( TimeDelta delta ) const
{
	return m_ms == delta.GetMS();
}

bool TimeDelta::operator != ( TimeDelta delta ) const
{
	return m_ms != delta.GetMS();
}

bool TimeDelta::operator > ( TimeDelta delta ) const
{
	return m_ms > delta.GetMS();
}

bool TimeDelta::operator < ( TimeDelta delta ) const
{
	return m_ms < delta.GetMS();
}

bool TimeDelta::operator >= ( TimeDelta delta ) const
{
	return m_ms >= delta.GetMS();
}

bool TimeDelta::operator <= ( TimeDelta delta ) const
{
	return m_ms <= delta.GetMS();
}


