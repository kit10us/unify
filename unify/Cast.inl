/*
 * Unify Library
 * https://github.com/kit10us/unify
 * Copyright (c) 2002, Kit10 Studios LLC
 *
 * This file is part of Unify Library (a.k.a. Unify)
 *
 * Unify is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Unify is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Unify.  If not, see <https://www.gnu.org/licenses/>.
 */

//#include <unify/String.h>

// SAS TODO: Attempt to use constexpr and/or templates (need to take string_View)to reduce the amount of code here. This is a lot of code for something that should be simple. Also, consider using std::from_chars and std::to_chars instead of the C functions.

#pragma warning(push)
#pragma warning(disable : 4244) // 'argument' : conversion from ... to ..., possible loss of data

template<>
inline
double unify::Cast(const std::string text);

template<>
inline
unsigned int unify::Cast(const std::string text);

template < typename...>
inline constexpr bool k_always_false = false;

template< typename TTo, class TFrom >
TTo unify::Cast(const TFrom in )
{
	static_assert(sizeof(TFrom) > 16, "Cast type is larger than 16 bytes, use LargeCast.");
	static_assert(k_always_false<TTo, TFrom>, "Unsupported cast type.");
	throw std::bad_cast();
}

template<>
inline
std::string unify::Cast(const std::string in)
{
	return in;
}

template<>
inline
std::string unify::Cast(const std::wstring in)
{
	return std::string(in.begin(), in.end());
}

template<>
inline
std::string unify::Cast(const bool in)
{
	return in ? "true" : "false";
}

template<>
inline
std::string unify::Cast(const unsigned char in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const char in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const unsigned int in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const unsigned __int64 in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const int in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const float in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const double in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const unsigned short in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const short in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const unsigned long in)
{
	return std::to_string(in);
}

template<>
inline
std::string unify::Cast(const long in)
{
	return std::to_string(in);
}

template<>
inline
bool unify::Cast(std::string text)
{
	std::transform(text.begin(), text.end(), text.begin(), ::towlower);
	if (text == "false" || text == "f" || text == "0" || text == "no" || text == "off")
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<>
inline
char unify::Cast(const std::string text)
{
	return (char)(!text.empty() ? atoi(text.c_str()) : 0);
}

template<>
inline
unsigned char unify::Cast(const std::string text)
{
	return (unsigned char)Cast< unsigned int >(text);
}

template<>
inline
int unify::Cast(const std::string text)
{
	return(!text.empty() ? atoi(text.c_str()) : 0);
}

template<>
inline
unsigned int unify::Cast(const std::string text)
{
	return(!text.empty() ? strtoul(text.c_str(), 0, 0) : 0);
}

template<>
inline
unsigned __int64 unify::Cast(const std::string text)
{
	return(!text.empty() ? strtoull(text.c_str(), 0, 0) : 0);
}

template<>
inline
float unify::Cast(const std::string text)
{
	return (float)Cast< double >(text);
}

template<>
inline
double unify::Cast(const std::string text)
{
	return(!text.empty() ? atof(text.c_str()) : 0);
}

template<>
inline
wchar_t* unify::Cast(const std::string text)
{
	if (text.empty()) return NULL;

	const char* lpszIn = text.c_str();
	unsigned int uLength = 0;
	while (lpszIn[uLength++] != 0);
	wchar_t* lpszOut = new wchar_t[uLength];
	uLength = 0;
	while (lpszIn[uLength] != 0)
	{
		wchar_t c = (wchar_t)lpszIn[uLength];
		lpszOut[uLength] = c;
		uLength++;
	}
	lpszOut[uLength] = 0;
	return lpszOut;
}

template<>
inline
short unify::Cast(const std::string text)
{
	return (short)(!text.empty() ? atoi(text.c_str()) : 0);
}

template<>
inline
unsigned short unify::Cast(const std::string text)
{
	return(unsigned short)(!text.empty() ? strtoul(text.c_str(), 0, 0) : 0);
}

template<>
inline
std::wstring unify::Cast(const std::string text)
{
	return std::wstring(text.begin(), text.end());
}

template<>
inline
bool unify::Cast(const char* text)
{
	return Cast< bool, std::string >(text);
}

template<>
inline
char unify::Cast(const char* text)
{
	return Cast< char, std::string >(text);
}

template<>
inline
unsigned char unify::Cast(const char* text)
{
	return Cast< unsigned char, std::string >(text);
}

template<>
inline
int unify::Cast(const char* text)
{
	return Cast< int, std::string >(text);
}

template<>
inline
unsigned int unify::Cast(const char* text)
{
	return Cast< unsigned int, std::string >(text);
}

template<>
inline
unsigned __int64 unify::Cast(const char* text)
{
	return Cast< unsigned __int64, std::string >(text);
}

template<>
inline
float unify::Cast(const char* text)
{
	return Cast< float, std::string >(text);
}

template<>
inline
double unify::Cast(const char* text)
{
	return Cast< double, std::string >(text);
}

template<>
inline
wchar_t* unify::Cast(const char* text)
{
	return Cast< wchar_t*, std::string >(text);
}

template<>
inline
std::string unify::Cast(const char* text)
{
	return std::string(text);
}

template<>
inline
std::string unify::Cast(const wchar_t* text)
{
	return Cast< std::string >(std::wstring(text));
}

#pragma warning(pop)
