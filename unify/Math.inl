// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

template< typename T >
T Lerp( T a, T b, float delta )
{
	return a + (b - a) * delta;
}
