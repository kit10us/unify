// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#pragma once

#pragma comment( lib, "unify" )

// MS likes to macro max. We want to use max.
#ifdef max
#undef max
#endif

// MS likes to macro min. We want to use min.
#ifdef min
#undef min
#endif

// MS likes to macro RGB. We want to use RGB.
#ifdef RGB
#undef RGB
#endif

#include <limits>
#include <string>
