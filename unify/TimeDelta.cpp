// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/TimeDelta.h>

using namespace unify;

const float MSPerSecond = 1000.0f;
const float MSPerMinute = MSPerSecond * 60.0f;
const float MSPerHour = MSPerMinute * 60.0f;
const float MSPerDay = MSPerHour * 24.0f;
const float MSPerWeek = MSPerDay * 7.0f;
const float MSPerYear = MSPerDay * 365.0f;

const float SecondPerMS = 1.0f / MSPerSecond;
const float MinutePerMS = 1.0f / MSPerMinute;
const float HourPerMS = 1.0f / MSPerHour;
const float DayPerMS = 1.0f / MSPerDay;
const float WeekPerMS = 1.0f / MSPerWeek;
const float YearPerMS = 1.0f / MSPerYear;

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

TimeDelta unify::TimeDeltaInDays( float years )
{
	return TimeDelta( years * MSPerYear );
}

TimeDelta unify::TimeDeltaZero()
{
	return TimeDelta( 0.0f );
}

TimeDelta unify::TimeDeltaOne()
{
	return TimeDelta( 1.0f );
}

TimeDelta::TimeDelta( float ms )
	: m_ms( ms )
{
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

