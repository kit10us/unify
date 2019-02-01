// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved
#pragma once

#include <unify/Unify.h>
#include <string>
#include <exception>

namespace unify
{
    struct NinePoint
    {
        enum TYPE {
            TopLeft,
            Top,
            TopRight,
            Left,
            Center,
            Right,
            BottomLeft,
            Bottom,
            BottomRight
        };

        static std::string ToString( TYPE ninePoint );
        static TYPE FromString( std::string ninePointAsString );
        static bool IsTop( TYPE ninePoint );
        static bool IsLeft( TYPE ninePoint );
        static bool IsBottom( TYPE ninePoint );
        static bool IsRight( TYPE ninePoint );
    };
}

