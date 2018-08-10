// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/TimeDelta.h>

using namespace unify;

TimeDelta::TimeDelta( float ms )
: m_ms( ms )
{
}

TimeDelta TimeDelta::TimeDeltaInMS( float ms )
{
    return TimeDelta( ms );
}

TimeDelta TimeDelta::TimeDeltaInSeconds( float seconds )
{
    return TimeDelta( seconds * 1000.0f );
}

float TimeDelta::GetMS() const
{
    return m_ms;
}

float TimeDelta::GetSeconds() const
{
    return m_ms * 0.001f;
}
