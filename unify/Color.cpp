// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/ColorUnit.h>
#include <unify/Color.h>
#include <unify/String.h>
#include <algorithm>

using namespace unify;
using namespace string;

Color unify::ColorRGBA( Color::Component r, Color::Component g, Color::Component b, Color::Component a )
{
	return Color( r, g, b, a );
}

Color unify::ColorRGBA( unsigned int rgba )
{
	int r = (rgba >> 24) & 0x000000FF;
	int g = (rgba >> 16) & 0x000000FF;
	int b = (rgba >> 8) & 0x000000FF;
	int a = (rgba >> 0) & 0x000000FF;
	return ColorRGBA( (Color::Component)r, (Color::Component)g, (Color::Component)b, (Color::Component)a );
}

Color unify::ColorARGB( Color::Component a, Color::Component r, Color::Component g, Color::Component b )
{
	return ColorRGBA( r, g, b, a );
}

Color unify::ColorARGB( unsigned int argb )
{
	int a = (argb >> 24) & 0x000000FF;
	int r = (argb >> 16) & 0x000000FF;
	int g = (argb >> 8) & 0x000000FF;
	int b = (argb >> 0) & 0x000000FF;
	return ColorARGB( (Color::Component)a, (Color::Component)r, (Color::Component)g, (Color::Component)b );
}

Color unify::ColorRGB( Color::Component r, Color::Component g, Color::Component b )
{
	return ColorRGBA( r, g, b, 255 );
}

Color unify::ColorWhite( Color::Component a )
{
	return ColorRGBA( 255, 255, 255, a );
}

Color unify::ColorRed( Color::Component r, Color::Component a )
{
	return ColorRGBA( r, 0, 0, a );
}

Color unify::ColorGreen( Color::Component g, Color::Component a )
{
	return ColorRGBA( 0, g, 0, a );
}

Color unify::ColorBlue( Color::Component b, Color::Component a )
{
	return ColorRGBA( 0, 0, b, a );
}

Color unify::ColorYellow( Color::Component y, Color::Component a )
{
	return ColorRGBA( y, y, 0, a );
}

Color unify::ColorCyan( Color::Component c, Color::Component a )
{
	return ColorRGBA( 0, c, c, a );
}

Color unify::ColorMagenta( Color::Component m, Color::Component a )
{
	return ColorRGBA( m, 0, m, a );
}

Color unify::ColorGrey( Color::Component grey, Color::Component a )
{
	return ColorRGBA( grey, grey, grey, a );
}

Color unify::ColorBlack( Color::Component a )
{
	return ColorRGBA( 0, 0, 0, a );
}

Color unify::ColorZero()
{
	return ColorRGBA( 0, 0, 0, 0 );
}

Color::Color()
{
	// empty
}

Color::Color( Color::Component r, Color::Component g, Color::Component b, Color::Component a )
{
	SetRGBA( r, g, b, a );
}

Color::Color( const Color & color )
: c( color.c )
{
}

Color::Color( const ColorUnit & colorUnit )
{
	SetRGBA( 
		static_cast< Component >( colorUnit.component.r * 255.f ),
		static_cast< Component >( colorUnit.component.g * 255.f ),
		static_cast< Component >( colorUnit.component.b * 255.f ),
		static_cast< Component >( colorUnit.component.a * 255.f )
		);
}

Color::Color( std::string text, Order order, Color::Component defaultAlpha )
{
	component.r = 0;
	component.g = 0;
	component.b = 0;
	component.a = defaultAlpha;

	// Named colors.
	if ( StringIs( text, "red" ) )
	{
		component.r = 255;
	}
	else if ( StringIs( text, "green" ) )
	{
		component.g = 255;
	}
	else if ( StringIs( text, "blue" ) )
	{
		component.b = 255;
	}
	else if ( StringIs( text, "white" ) )
	{
		component.r = 255;
		component.g = 255;
		component.b = 255;
	}
	else if ( StringIs( text, "black" ) )
	{
		component.r = 0;
		component.g = 0;
		component.b = 0;
	}
	else if ( StringIs( text, "clear" ) )
	{
		component.r = 0;
		component.g = 0;
		component.b = 0;
		component.a = 0;
	}
	else
	{
		std::vector< unsigned char > split = Split< unsigned char >( text, ',' );
		if ( split.size() == 3 )
		{
			component.r = split[ 0 ];
			component.g = split[ 1 ];
			component.b = split[ 2 ];
		}
		else if ( split.size() == 4 )
		{
			switch( order )
			{
			case RGBA:
				component.r = split[ 0 ];
				component.g = split[ 1 ];
				component.b = split[ 2 ];
				component.a = split[ 3 ];
				break;
			case ARGB:
				component.a = split[ 0 ];
				component.r = split[ 1 ];
				component.g = split[ 2 ];
				component.b = split[ 3 ];
				break;
			case BGRA:
				component.b = split[ 0 ];
				component.g = split[ 1 ];
				component.r = split[ 2 ];
				component.a = split[ 3 ];
				break;
			case ABGR:
				component.a = split[ 0 ];
				component.b = split[ 1 ];
				component.g = split[ 2 ];
				component.r = split[ 3 ];
				break;
			}
		}
	}
}

Color::operator ColorUnit () const
{
	float r = static_cast< float >( GetRed() ) / 255.0f;
	float g = static_cast< float >( GetGreen() ) / 255.0f;
	float b = static_cast< float >( GetBlue() ) / 255.0f;
	float a = static_cast< float >( GetAlpha() ) / 255.0f;
	return ColorUnitRGBA( r, g, b, a );
}

Color::operator unsigned int () const
{
	return c;
}

Color & Color::operator += ( const Color & col )
{
    int r = GetRed();
    r += col.GetRed();
    int g = GetGreen();
    g += col.GetGreen();
    int b = GetBlue();
    b += col.GetBlue();
    int a = GetAlpha();
    a += col.GetAlpha();

    using std::min;
    r = min<>( r, 255 );
    g = min<>( g, 255 );
    b = min<>( b, 255 );
    a = min<>( a, 255 );
    SetRGBA( static_cast< Component >( r ), static_cast< Component >( g ), static_cast< Component >( b ), static_cast< Component >( a ) );
    return *this;
}

Color & Color::operator -= ( const Color & col )
{
    int r = GetRed();
    r -= col.GetRed();
    int g = GetGreen();
    g -= col.GetGreen();
    int b = GetBlue();
    b -= col.GetBlue();
    int a = GetAlpha();
    a -= col.GetAlpha();

    using std::max;
    r = max<>( r, 0 );
    g = max<>( g, 0 );
    b = max<>( b, 0 );
    a = max<>( a, 0 );
    SetRGBA( static_cast< Component >( r ), static_cast< Component >( g ), static_cast< Component >( b ), static_cast< Component >( a ) );
    return *this;
}

Color & Color::operator *= ( const Color & col )
{
    int r = GetRed();
    r *= col.GetRed();
    int g = GetGreen();
    g *= col.GetGreen();
    int b = GetBlue();
    b *= col.GetBlue();
    int a = GetAlpha();
    a *= col.GetAlpha();

    using std::max;
    using std::min;
    r = min<>( max<>( r, 0 ), 255 );
    g = min<>( max<>( g, 0 ), 255 );
    b = min<>( max<>( b, 0 ), 255 );
    a = min<>( max<>( a, 0 ), 255 );
    SetRGBA( static_cast< Component >( r ), static_cast< Component >( g ), static_cast< Component >( b ), static_cast< Component >( a ) );
    return *this;
}

Color & Color::operator /= ( const Color & col )
{
    int r = GetRed();
    r /= col.GetRed();
    int g = GetGreen();
    g /= col.GetGreen();
    int b = GetBlue();
    b /= col.GetBlue();
    int a = GetAlpha();
    a /= col.GetAlpha();

    using std::max;
    using std::min;
    r = min<>( max<>( r, 0 ), 255 );
    g = min<>( max<>( g, 0 ), 255 );
    b = min<>( max<>( b, 0 ), 255 );
    a = min<>( max<>( a, 0 ), 255 );
    SetRGBA( static_cast< Component >( r ), static_cast< Component >( g ), static_cast< Component >( b ), static_cast< Component >( a ) );
    return *this;
}

Color & Color::operator *= ( float val )
{
    float r = GetRed();
    r *= val;
    float g = GetGreen();
    g *= val;
    float b = GetBlue();
    b *= val;
    float a = GetAlpha();
    a *= val;

    using std::max;
    using std::min;
    r = min< float >( max< float >( r, 0.0f ), 255.0f );
    g = min< float >( max< float >( g, 0.0f ), 255.0f );
    b = min< float >( max< float >( b, 0.0f ), 255.0f );
    a = min< float >( max< float >( a, 0.0f ), 255.0f );
    SetRGBA( static_cast< Component >( r ), static_cast< Component >( g ), static_cast< Component >( b ), static_cast< Component >( a ) );
    return *this;
}

Color & Color::operator /= ( float val )
{
    float r = GetRed();
    r /= val;
    float g = GetGreen();
    g /= val;
    float b = GetBlue();
    b /= val;
    float a = GetAlpha();
    a /= val;

    using std::max;
    using std::min;
    r = min<>( max<>( r, 0.0f ), 255.0f );
    g = min<>( max<>( g, 0.0f ), 255.0f );
    b = min<>( max<>( b, 0.0f ), 255.0f );
    a = min<>( max<>( a, 0.0f ), 255.0f );
    SetRGBA( static_cast< Component >( r ), static_cast< Component >( g ), static_cast< Component >( b ), static_cast< Component >( a ) );
    return *this;
}

Color Color::operator + ( const Color & col ) const
{
    Color newColor = *this;
    newColor += col;
    return newColor;
}

Color Color::operator - ( const Color & col ) const
{
    Color newColor = *this;
    newColor -= col;
    return newColor;
}

Color Color::operator * ( const Color & col ) const
{
    Color newColor = *this;
    newColor *= col;
    return newColor;
}

Color Color::operator / ( const Color & col ) const
{
    Color newColor = *this;
    newColor /= col;
    return newColor;
}

Color Color::operator * ( float val ) const
{
    Color newColor = *this;
    newColor *= val;
    return newColor;
}

Color Color::operator / ( float val ) const
{
    Color newColor = *this;
    newColor /= val;
    return newColor;
}

bool Color::operator == ( const Color & col ) const
{
    return GetRed() == col.GetRed() && GetBlue() == col.GetBlue() && GetGreen() == col.GetGreen() && GetAlpha() == col.GetAlpha();
}

bool Color::operator != ( const Color & col ) const
{
    return !(*this == col);
}

void Color::SetRGBA( Color::Component r, Color::Component g, Color::Component b, Color::Component a )
{
	component.r = r;
	component.g = g;
	component.b = b;
	component.a = a;
}

Color::Component Color::GetAlpha() const
{
	return component.a;
}

Color::Component Color::GetRed() const
{
	return component.r;
}

Color::Component Color::GetGreen() const
{
	return component.g;
}

Color::Component Color::GetBlue() const
{
	return component.b;
}

void Color::SetAlpha( Color::Component a)
{
	((Color::Component*)&c)[3] = a;
}

void Color::SetRed( Color::Component r )
{
	((Color::Component*)&c)[2] = r;
}

void Color::SetGreen( Color::Component g )
{
	((Color::Component*)&c)[1] = g;
}

void Color::SetBlue( Color::Component b )
{
	((Color::Component*)&c)[0] = b;
}

void Color::Interpulate( const Color colorA, const Color colorB, const float ratio )
{
	float a, r, g, b;
	a = (colorA.GetAlpha() * (1.0f - ratio))	+ (colorB.GetAlpha() * ratio);
	r = (colorA.GetRed() * (1.0f - ratio))	+ (colorB.GetRed() * ratio);
	g = (colorA.GetGreen() * (1.0f - ratio))	+ (colorB.GetGreen() * ratio);
	b = (colorA.GetBlue() * (1.0f - ratio))	+ (colorB.GetBlue() * ratio);
	SetRGBA( (char)r, (char)g, (char)b, (char)a );
}

std::string Color::ToString( Order order ) const
{
	switch( order )
	{
	case RGBA:
	default:
		return Cast< std::string >( component.r ) + ", " + Cast< std::string >( component.g ) + ", " + Cast< std::string >( component.b ) + ", " + Cast< std::string >( component.a );
	case ARGB:
		return Cast< std::string >( component.a ) + ", " + Cast< std::string >( component.r ) + ", " + Cast< std::string >( component.g ) + ", " + Cast< std::string >( component.b );
	case BGRA:
		return Cast< std::string >( component.b ) + ", " + Cast< std::string >( component.g ) + ", " + Cast< std::string >( component.r ) + ", " + Cast< std::string >( component.a );
	case ABGR:
		return Cast< std::string >( component.a ) + ", " + Cast< std::string >( component.b ) + ", " + Cast< std::string >( component.g ) + ", " + Cast< std::string >( component.r );
	}
}
