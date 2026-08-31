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

#pragma warning(push)
#pragma warning(disable : 4244) // 'argument' : conversion from ... to ..., possible loss of data

/*
template< typename TTo, class TFrom >
std::optional<TTo> unify::Cast(const TFrom in) noexcept = delete;
*/

/*
template<>
inline
std::optional<double> unify::FromString(std::string_view text) noexcept;

template<>
inline
std::optional<unsigned int> unify::FromString(std::string_view text) noexcept;
*/

/// @brief Convert a character into a string.
/// @note As this is considering the character in as a ascii character, we need to box the char.
/// @param in Char box
/// @return string
template<>
inline
std::optional<std::string> unify::ToString(const Char in) noexcept
{
	try
	{
		return std::string(1, in.c);
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const std::string in) noexcept
{
	return in;
}

template<>
inline
std::optional<std::string> unify::ToString(const std::string_view in) noexcept
{
	try
	{
		return {{in.data(), in.data() + in.size()}};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

inline
std::optional<std::wstring> ToWString(std::string input_string)
{
    if (input_string.empty())
    {
        return std::wstring();
    }

    std::size_t size_needed = 0;
    mbstowcs_s(&size_needed, nullptr, 0, input_string.c_str(), _TRUNCATE);

    if (size_needed == 0)
    {
        return std::wstring();
    }

    std::wstring output_string(size_needed - 1, 0);
    mbstowcs_s(nullptr, output_string.data(), size_needed, input_string.c_str(), _TRUNCATE);

    return output_string;
}

template<>
inline
std::optional<std::string> unify::ToString(const std::wstring in) noexcept
{
	try
	{
		return {std::string(in.begin(), in.end())};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const bool in) noexcept
{
	try
	{
		return {in ? "true" : "false"};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const uint8_t in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const char in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const uint32_t in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const uint64_t in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const int32_t in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const int64_t in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const float in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const double in) noexcept
{
	try
	{
		return {std::to_string(in)};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const uint16_t in) noexcept
{
	try
	{
		return std::to_string(in);
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::ToString(const int16_t in) noexcept
{
	try
	{
		return std::to_string(in);
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<bool> unify::FromString(std::string_view raw_text) noexcept
{
	std::string text(raw_text.data(), raw_text.data() + raw_text.size());
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);

	if (text.empty() || text == "false" || text == "f" || text == "0" || text == "no" || text == "off")
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
std::optional<int8_t> unify::FromString(std::string_view text) noexcept
{
	int8_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<uint8_t> unify::FromString(std::string_view text) noexcept
{
	uint8_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<int32_t> unify::FromString(std::string_view text) noexcept
{
	int32_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<uint32_t> unify::FromString(std::string_view text) noexcept
{
	uint32_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::uint64_t> unify::FromString(std::string_view text) noexcept
{
	std::uint64_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<float> unify::FromString(std::string_view text) noexcept
{
	float out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<double> unify::FromString(std::string_view text) noexcept
{
	double out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}
/*
template<>
inline
std::optional<wchar_t*> unify::Cast(const std::string text) noexcept
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
*/

template<>
inline
std::optional<int16_t> unify::FromString(std::string_view text) noexcept
{
{
	int16_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}}

template<>
inline
std::optional<uint16_t> unify::FromString(std::string_view text) noexcept
{
	uint16_t out{};
	auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), out);
	if (ec == std::errc{} && ptr == text.data() + text.size())
	{
		return out;
	}
	else
	{
		return std::nullopt;
	}
}


template<>
inline
std::optional<std::wstring> unify::FromString(std::string_view text) noexcept
{
	return std::wstring(text.begin(), text.end());
}

/*
template<>
inline
std::optional<bool> unify::Cast(const char* text) noexcept
{
	return Cast< bool, std::string_view >(text);
}

template<>
inline
std::optional<char> unify::Cast(const char* text) noexcept
{
	return Cast<int8_t, std::string_view >(text);
}

template<>
inline
std::optional<unsigned char> unify::Cast(const char* text) noexcept
{
	return Cast<uint8_t, std::string_view>(text);
}

template<>
inline
std::optional<int32_t> unify::Cast(const char* text) noexcept
{
	return Cast<int32_t, std::string_view>(text);
}

template<>
inline
std::optional<unsigned int> unify::Cast(const char* text) noexcept
{
	return Cast< unsigned int, std::string_view>(text);
}

template<>
inline
std::optional<unsigned __int64> unify::Cast(const char* text) noexcept
{
	return Cast<unsigned __int64, std::string_view>(text);
}

template<>
inline
std::optional<float> unify::Cast(const char* text) noexcept
{
	return Cast<float, std::string_view>(text);
}
	
template<>
inline
std::optional<double> unify::Cast(const char* text) noexcept
{
	return Cast<double, std::string_view>(text);
}

//template<>
//inline
//wchar_t* unify::Cast(const char* text) noexcept
//{
//	return Cast< wchar_t*, std::string >(text);
//}

template<>
inline
std::optional<std::string> unify::Cast(const char* text) noexcept
{
	try
	{
		std::string(text);
	}
	catch(...)
	{
		return std::nullopt;
	}
}
*/

/*
template<>
inline
std::optional<std::string> unify::ToString(const wchar_t* text) noexcept
{
	return ToString<std::string>(std::wstring(text));
}
*/

template<>
inline
std::optional<std::string> unify::ToString(std::wstring_view in) noexcept
{
	try
	{
		return {std::string(in.begin(), in.end())};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

template<>
inline
std::optional<std::string> unify::FromString(std::string_view in) noexcept
{
	try
	{
		return {std::string(in.begin(), in.end())};
	}
	catch(...)
	{
		return std::nullopt;
	}
}

#pragma warning(pop)
