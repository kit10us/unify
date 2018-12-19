// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/NinePoint.h>
#include <unify/String.h>
#include <unify/Exception.h>

using namespace unify;
using namespace string;

std::string NinePoint::ToString( TYPE ninePoint )
{
    switch( ninePoint )
    {
    case NinePoint::TopLeft: return "top left";
    case NinePoint::Top: return "top";
    case NinePoint::TopRight: return "top right";
    case NinePoint::Left: return "left";
    case NinePoint::Center: return "center";
    case NinePoint::Right: return "right";
    case NinePoint::BottomLeft: return "bottom left";
    case NinePoint::Bottom: return "bottom";
    case NinePoint::BottomRight: return "bottom right";
    default: throw unify::Exception( "Invalid converstion ToString for NinePoint!" );
    }
}

NinePoint::TYPE NinePoint::FromString( std::string fromString )
{
    if ( StringIs( fromString, "Top Left" ) )
    {
        return NinePoint::TopLeft;
    }
    else if ( StringIs( fromString, "Top" ) )
    {
        return NinePoint::Top;
    }
    if ( StringIs( fromString, "Top Right" ) )
    {
        return NinePoint::TopRight;
    }
    if ( StringIs( fromString, "Left" ) )
    {
        return NinePoint::Left;
    }
    if ( StringIs( fromString, "Center" ) )
    {
        return NinePoint::Center;
    }
    if ( StringIs( fromString, "Bottom Left" ) )
    {
        return NinePoint::BottomLeft;
    }
    if ( StringIs( fromString, "Bottom" ) )
    {
        return NinePoint::Bottom;
    }
    if ( StringIs( fromString, "Bottom Right" ) )
    {
        return NinePoint::BottomRight;
    }
    else
    {
        throw unify::Exception( "Failed to convert NinePoint FromString!" );
    }
}

bool NinePoint::IsTop( TYPE ninePoint )
{
    switch( ninePoint )
    {
    case NinePoint::Top:
    case NinePoint::TopLeft:
    case NinePoint::TopRight:
        return true;
    default:
        return false;
    }
}

bool NinePoint::IsLeft( TYPE ninePoint )
{
    switch( ninePoint )
    {
    case NinePoint::Left:
    case NinePoint::TopLeft:
    case NinePoint::BottomLeft:
        return true;
    default:
        return false;
    }
}

bool NinePoint::IsBottom( TYPE ninePoint )
{
    switch( ninePoint )
    {
    case NinePoint::Bottom:
    case NinePoint::BottomLeft:
    case NinePoint::BottomRight:
        return true;
    default:
        return false;
    }
}
bool NinePoint::IsRight( TYPE ninePoint )
{
    switch( ninePoint )
    {
    case NinePoint::Right:
    case NinePoint::TopRight:
    case NinePoint::BottomRight:
        return true;
    default:
        return false;
    }
}
