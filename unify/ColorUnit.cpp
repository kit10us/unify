// Copyright (c) 2002 - 2019, Kit10 Studios LLC
// All Rights Reserved

#include <unify/String.h>
#include <unify/Color.h>
#include <unify/ColorUnit.h>
#include <algorithm>

using namespace unify;
using namespace string;

ColorUnit unify::ColorUnitRGBA( float r, float g, float b, float a )
{
	return ColorUnit( r, g, b, a );
}

ColorUnit unify::ColorUnitARGB( float a, float r, float g, float b )
{
	return ColorUnitRGBA( r, g, b, a );
}

ColorUnit unify::ColorUnitRGB( float r, float g, float b )
{
	return ColorUnitRGBA( r, g, b, 1.0f );
}

ColorUnit unify::ColorUnitWhite( float a )
{
	return ColorUnitRGBA( 1.0f, 1.0f, 1.0f, a );
}

ColorUnit unify::ColorUnitRed( float r, float a )
{
	return ColorUnitRGBA( r, 0.0f, 0.0f, a );
}

ColorUnit unify::ColorUnitGreen( float g, float a )
{
	return ColorUnitRGBA( 0.0f, g, 0.0f, a );
}

ColorUnit unify::ColorUnitBlue( float b, float a )
{
	return ColorUnitRGBA( 0.0f, 0.0f, b, a );
}

ColorUnit unify::ColorUnitYellow( float b, float a )
{
	return ColorUnitRGBA( b, b, 0.0f, a );
}

ColorUnit unify::ColorUnitCyan( float b, float a )
{
	return ColorUnitRGBA( b, b, 0.0f, a );
}

ColorUnit unify::ColorUnitMagenta( float b, float a )
{
	return ColorUnitRGBA( b, 0.0f, b, a );
}

ColorUnit unify::ColorUnitGrey( float grey, float a )
{
	return ColorUnitRGBA( grey, grey, grey, a );
}

ColorUnit unify::ColorUnitBlack( float a )
{
	return ColorUnitRGBA( 0, 0, 0, a );
}

ColorUnit unify::ColorUnitZero()
{
	return ColorUnitRGBA( 0, 0, 0, 0 );
}

ColorUnit unify::ColorUnitLerp( ColorUnit l, ColorUnit r, float ratio )
{
	return l * (1.0f - ratio) + r * ratio;
}																  

ColorUnit::ColorUnit()
{
}

ColorUnit::ColorUnit( float r, float g, float b, float a )
{
	component.a = a;
	component.r = r;
	component.g = g;
	component.b = b;
}


ColorUnit::ColorUnit( const ColorUnit & color )
{
	component.a = color.component.a;
	component.r = color.component.r;
	component.g = color.component.g;
	component.b = color.component.b;
}

ColorUnit::ColorUnit( std::string text, Order order, float defaultAlpha )
{
	component.r = 0;
	component.g = 0;
	component.b = 0;
	component.a = defaultAlpha;

	if( StringIs( text, "white" ) )
	{
		component.r = 1.0f;
		component.g = 1.0f;
		component.b = 1.0f;
	}
	else if( StringIs( text, "black" ) )
	{
		// Nothing (use the above defaults).
	}
	else if( StringIs( text, "red" ) )
	{
		component.r = 1.0f;
	}
	else if( StringIs( text, "green" ) )
	{
		component.g = 1.0f;
	}
	else if( StringIs( text, "blue" ) )
	{
		component.b = 1.0f;
	}
	else if( StringIs( text, "clear" ) )
	{
		component.a = 0.0f;
	}
	else
	{
		std::vector< float > split = Split< float >( text, ',' );
		if ( split.size() == 1 )
		{
			split = SplitOnWhitespace< float >( text );
		}

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

ColorUnit::operator Color()
{
	return ColorRGBA( (unsigned char)(component.r * 255.0f), (unsigned char)(component.g * 255.0f), (unsigned char)(component.b * 255.0f), (unsigned char)(component.a * 255.0f) );
}

float ColorUnit::SumComponents()
{
	return component.a + component.r + component.g + component.b;
}

ColorUnit & ColorUnit::operator += ( const ColorUnit & col )
{
	component.a += col.component.a;
	component.r += col.component.r;
	component.g += col.component.g;
	component.b += col.component.b;
	return *this;
}


ColorUnit & ColorUnit::operator -= ( const  ColorUnit & col )
{
	component.a -= col.component.a;
	component.r -= col.component.r;
	component.g -= col.component.g;
	component.b -= col.component.b;
	return *this;
}


ColorUnit & ColorUnit::operator *= ( float val )
{
	component.a *= val;
	component.r *= val;
	component.g *= val;
	component.b *= val;
	return *this;
}


ColorUnit & ColorUnit::operator /= ( float val )
{
	component.a /= val;
	component.r /= val;
	component.g /= val;
	component.b /= val;
	return *this;
}

ColorUnit ColorUnit::operator + ( const ColorUnit & col ) const
{
	return ColorUnitARGB( component.a + col.component.a, component.r + col.component.r, component.g + col.component.g, component.b + col.component.b );
}


ColorUnit ColorUnit::operator - ( const ColorUnit & col ) const
{
	return ColorUnitARGB( component.a - col.component.a, component.r - col.component.r, component.g - col.component.g, component.b - col.component.b );
}

ColorUnit ColorUnit::operator * ( const ColorUnit & col ) const
{
	return ColorUnitARGB( component.a * col.component.a, component.r * col.component.r, component.g * col.component.g, component.b * col.component.b );
}

ColorUnit ColorUnit::operator / ( const ColorUnit & col ) const
{
	return ColorUnitARGB( component.a / col.component.a, component.r / col.component.r, component.g / col.component.g, component.b / col.component.b );
}

ColorUnit ColorUnit::operator * ( float val ) const
{
	return ColorUnitARGB( component.a * val, component.r * val, component.g * val, component.b * val );
}


ColorUnit ColorUnit::operator / ( float val ) const
{
	return ColorUnitARGB( component.a / val, component.r / val, component.g / val, component.b / val );
}

bool ColorUnit::operator == ( const ColorUnit & col ) const
{
	return( component.a == col.component.a && component.r == col.component.r && component.g == col.component.g && component.b == col.component.b );
}

bool ColorUnit::operator != ( const ColorUnit & col ) const
{
	return( component.a != col.component.a || component.r != col.component.r || component.g != col.component.g || component.b != col.component.b );
}

void ColorUnit::SetRed( float pr )
{
	component.r = pr;
}

void ColorUnit::SetGreen( float pg )
{
	component.g = pg;
}

void ColorUnit::SetBlue( float pb )
{
	component.b = pb;
}

void ColorUnit::SetAlpha( float pa )
{
	component.a = pa;
}

void ColorUnit::SetRGBA( float ri, float gi, float bi, float ai )
{
	component.r = ri;
	component.g = gi;
	component.b = bi;
	component.a = ai;
}

std::string ColorUnit::ToString( ColorUnit::Order order ) const
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
