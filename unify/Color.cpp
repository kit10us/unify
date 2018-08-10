// Copyright (c) 2002 - 2019, Evil Quail LLC
// All Rights Reserved

#include <unify/ColorUnit.h>
#include <unify/Color.h>
#include <unify/String.h>
#include <algorithm>

using namespace unify;

Color Color::ColorRGBA( Color::Component r, Color::Component g, Color::Component b, Color::Component a )
{
	return Color( r, g, b, a );
}

Color Color::ColorRGBA( unsigned int rgba )
{
	int r = (rgba >> 24) & 0x000000FF;
	int g = (rgba >> 16) & 0x000000FF;
	int b = (rgba >> 8) & 0x000000FF;
	int a = (rgba >> 0) & 0x000000FF;
	return Color::ColorRGBA( (Component)r, (Component)g, (Component)b, (Component)a );
}

Color Color::ColorARGB( Color::Component a, Color::Component r, Color::Component g, Color::Component b )
{
	return Color::ColorRGBA( r, g, b, a );
}

Color Color::ColorARGB( unsigned int argb )
{
	int a = (argb >> 24) & 0x000000FF;
	int r = (argb >> 16) & 0x000000FF;
	int g = (argb >> 8) & 0x000000FF;
	int b = (argb >> 0) & 0x000000FF;
	return Color::ColorARGB( (Component)a, (Component)r, (Component)g, (Component)b );
}

Color Color::ColorRGB( Color::Component r, Color::Component g, Color::Component b )
{
	return Color::ColorRGBA( r, g, b, 255 );
}

Color Color::ColorWhite( Component a )
{
	return Color::ColorRGBA( 255, 255, 255, a );
}


Color Color::ColorRed( Color::Component r, Color::Component a )
{
	return Color::ColorRGBA( r, 0, 0, a );
}

Color Color::ColorGreen( Color::Component g, Color::Component a )
{
	return Color::ColorRGBA( 0, g, 0, a );
}

Color Color::ColorBlue( Color::Component b, Color::Component a )
{
	return Color::ColorRGBA( 0, 0, b, a );
}

Color Color::ColorYellow( Color::Component y, Color::Component a )
{
	return Color::ColorRGBA( y, y, 0, a );
}

Color Color::ColorCyan( Color::Component c, Color::Component a )
{
	return Color::ColorRGBA( 0, c, c, a );
}

Color Color::ColorMagenta( Color::Component m, Color::Component a )
{
	return Color::ColorRGBA( m, 0, m, a );
}

Color Color::ColorGrey( Color::Component grey, Color::Component a )
{
	return Color::ColorRGBA( grey, grey, grey, a );
}

Color Color::ColorBlack( Color::Component a )
{
	return Color::ColorRGBA( 0, 0, 0, a );
}

Color Color::ColorZero()
{
	return Color::ColorRGBA( 0, 0, 0, 0 );
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

Color::Color( std::string text, Color::Order order, Color::Component defaultAlpha )
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
		std::vector< unsigned char > split = unify::Split< unsigned char >( text, ',' );
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
	return ColorUnit::ColorUnitRGBA( r, g, b, a );
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

void Color::Modulate( const Color in1, const Color in2 )
{
	Color::Component a, r, g, b;
	a = (Color::Component)((in1.GetAlpha())	+ in2.GetAlpha())	/ 2;
	r = (Color::Component)((in1.GetRed())	+ in2.GetRed())	/ 2;
	g = (Color::Component)((in1.GetGreen())	+ in2.GetGreen())	/ 2;
	b = (Color::Component)((in1.GetBlue())	+ in2.GetBlue())	/ 2;
	SetRGBA( r, g, b, a );
}

// modulates (1.0 - ratio) of the first color with (ratio) of the second color

void Color::ModulateByRatio( const Color in1, const Color in2, const float ratio )
{
	float a, r, g, b;
	a = (in1.GetAlpha() * (1.0f - ratio))	+ ( in2.GetAlpha() * ratio );
	r = (in1.GetRed() * (1.0f - ratio))	+ ( in2.GetRed() * ratio );
	g = (in1.GetGreen() * (1.0f - ratio))	+ ( in2.GetGreen() * ratio );
	b = (in1.GetBlue() * (1.0f - ratio))	+ ( in2.GetBlue() * ratio );
	SetRGBA( (char)r, (char)g, (char)b, (char)a );
}

void Color::Modulate4( const Color in1, const Color in2, const Color in3, const Color in4 )
{
	Color col1, col2;
	col1.Modulate( in1, in2 );
	col2.Modulate( in3, in4 );
	Modulate( col1, col2 );
}

std::string Color::ToString( Color::Order order ) const
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
