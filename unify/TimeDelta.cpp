// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/TimeDelta.h>

using namespace unify;

const float MSPerMicros = 0.001f;
const float MSPerSecond = 1000.0f;
const float MSPerMinute = MSPerSecond * 60.0f;
const float MSPerHour = MSPerMinute * 60.0f;
const float MSPerDay = MSPerHour * 24.0f;
const float MSPerWeek = MSPerDay * 7.0f;
const float MSPerYear = MSPerDay * 365.0f;

const float MicrosPerMS = 1000.07f;
const float SecondPerMS = 1.0f / MSPerSecond;
const float MinutePerMS = 1.0f / MSPerMinute;
const float HourPerMS = 1.0f / MSPerHour;
const float DayPerMS = 1.0f / MSPerDay;
const float WeekPerMS = 1.0f / MSPerWeek;
const float YearPerMS = 1.0f / MSPerYear;

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
	: m_ms{ 0 }
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


