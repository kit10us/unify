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

#include <gtest/gtest.h>

#include <unify/Cast.h>

#include <string>
#include <limits>

class CastTests : public ::testing::Test
{ 
protected:
    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right before each test).
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right before the destructor).
    }  
};

using namespace unify;

TEST_F(CastTests, TestCasts)
{
    using namespace std::string_literals;
    using namespace std::string_view_literals;
    using namespace unify;

    EXPECT_STREQ( "0", ToString<Char>('0').value().c_str() );
    EXPECT_STREQ( "1", ToString<Char>('1').value().c_str() );
    EXPECT_STREQ( "a", ToString<Char>('a').value().c_str() );
    EXPECT_STREQ( "Z", ToString<Char>('Z').value().c_str() );
    EXPECT_STRNE( "a", ToString<Char>('b').value().c_str() );

    EXPECT_STREQ( "Hello, world!", ToString<std::string>("Hello, world!"s).value().c_str() );
    EXPECT_STRNE( "!dlrow ,olleH", ToString<std::string>("Hello, world!"s).value().c_str() );

    EXPECT_STREQ( "Hello, world!", ToString<std::string_view>("Hello, world!"sv).value().c_str() );
    EXPECT_STRNE( "!dlrow ,olleH", ToString<std::string_view>("Hello, world!"sv).value().c_str() );

    EXPECT_STREQ( "true", ToString<bool>(true).value().c_str() );
    EXPECT_STREQ( "false", ToString<bool>(false).value().c_str() );
    EXPECT_STRNE( "true", ToString<bool>(false).value().c_str() );
    EXPECT_STRNE( "false", ToString<bool>(true).value().c_str() );

    EXPECT_STREQ( "1", ToString<uint8_t>(1).value().c_str() );
    EXPECT_STREQ( "12", ToString<uint8_t>(12).value().c_str() );
    EXPECT_STRNE( "21", ToString<uint8_t>(12).value().c_str() );

    EXPECT_STREQ( "97", ToString<char>('a').value().c_str() );
    EXPECT_STREQ( "90", ToString<char>('Z').value().c_str() );
    EXPECT_STREQ( "49", ToString<char>('1').value().c_str() );
    EXPECT_STRNE( "12", ToString<char>('a').value().c_str() );

    EXPECT_STREQ( "1", ToString<uint32_t>(1).value().c_str() );
    EXPECT_STREQ( "1000", ToString<uint32_t>(1000).value().c_str() );
    EXPECT_STREQ( "1234567", ToString<uint32_t>(1234567).value().c_str() );
    EXPECT_STREQ( "4294967295", ToString<uint32_t>(std::numeric_limits<uint32_t>::max()).value().c_str() );
    EXPECT_STRNE( "0", ToString<uint32_t>(1).value().c_str() );

    EXPECT_STREQ( "1", ToString<uint64_t>(1).value().c_str() );
    EXPECT_STREQ( "1000", ToString<uint64_t>(1000).value().c_str() );
    EXPECT_STREQ( "1234567", ToString<uint64_t>(1234567).value().c_str() );
    EXPECT_STREQ( "18446744073709551615", ToString<uint64_t>(std::numeric_limits<uint64_t>::max()).value().c_str() );
    EXPECT_STRNE( "0", ToString<uint64_t>(1).value().c_str() );

    EXPECT_STREQ( "1", ToString<int32_t>(1).value().c_str() );
    EXPECT_STREQ( "1000", ToString<int32_t>(1000).value().c_str() );
    EXPECT_STREQ( "1234567", ToString<int32_t>(1234567).value().c_str() );
    EXPECT_STREQ( "-2147483648", ToString<int32_t>(std::numeric_limits<int32_t>::min()).value().c_str() );
    EXPECT_STREQ( "2147483647", ToString<int32_t>(std::numeric_limits<int32_t>::max()).value().c_str() );
    EXPECT_STRNE( "0", ToString<int32_t>(1).value().c_str() );

    EXPECT_STREQ( "1", ToString<int64_t>(1).value().c_str() );
    EXPECT_STREQ( "1000", ToString<int64_t>(1000).value().c_str() );
    EXPECT_STREQ( "1234567", ToString<int64_t>(1234567).value().c_str() );
    EXPECT_STREQ( "-9223372036854775808", ToString<int64_t>(std::numeric_limits<int64_t>::min()).value().c_str() );    
    EXPECT_STREQ( "9223372036854775807", ToString<int64_t>(std::numeric_limits<int64_t>::max()).value().c_str() );    
    EXPECT_STRNE( "0", ToString<int64_t>(1).value().c_str() );

    EXPECT_STREQ( "0.000000",  ToString<float>(0.0f).value().c_str() );
    EXPECT_STREQ( "1.000000",  ToString<float>(1.0f).value().c_str() );
    EXPECT_STREQ( "12.345600",  ToString<float>(12.3456f).value().c_str() );
    EXPECT_STREQ( "-12.345600", ToString<float>(-12.3456f).value().c_str() );
    EXPECT_STRNE( "0.000000",  ToString<float>(1.0f).value().c_str());

    EXPECT_STREQ( "0.000000",  ToString<double>(0.0).value().c_str() );
    EXPECT_STREQ( "1.000000",  ToString<double>(1.0).value().c_str() );
    EXPECT_STREQ( "12.345600",  ToString<double>(12.3456).value().c_str() );
    EXPECT_STREQ( "-12.345600",  ToString<double>(-12.3456).value().c_str() );
    EXPECT_STRNE( "0.000000",  ToString<double>(1.0).value().c_str() );

    EXPECT_STREQ( "1", ToString<uint16_t>(1).value().c_str() );
    EXPECT_STREQ( "1000", ToString<uint16_t>(1000).value().c_str() );
    EXPECT_STREQ( "12345", ToString<uint16_t>(12345).value().c_str() );
    EXPECT_STREQ( "0", ToString<uint16_t>(std::numeric_limits<uint16_t>::min()).value().c_str() );
    EXPECT_STREQ( "65535", ToString<uint16_t>(std::numeric_limits<uint16_t>::max()).value().c_str() );
    EXPECT_STRNE( "0", ToString<uint16_t>(1).value().c_str() );
    
    EXPECT_TRUE( std::string("1") == ToString((uint16_t)1) );
    EXPECT_TRUE( std::string("1000") == ToString((int16_t)1000) );
    EXPECT_TRUE( std::string("-1234") == ToString((int16_t)-1234) );
    EXPECT_TRUE( std::string("-32768") == ToString((int16_t)std::numeric_limits<int16_t>::min()) );
    EXPECT_TRUE( std::string("32767") == ToString((int16_t)std::numeric_limits<int16_t>::max()) );
    EXPECT_FALSE( std::string("0") == ToString((int16_t)1) );

    EXPECT_TRUE( *FromString<bool>("true") );
    EXPECT_TRUE( *FromString<bool>("on") );
    EXPECT_TRUE( *FromString<bool>("yes") );
    EXPECT_TRUE( *FromString<bool>("1") );
    EXPECT_TRUE( *FromString<bool>("123") );
    EXPECT_TRUE( *FromString<bool>("-123") );
    EXPECT_TRUE( *FromString<bool>("TrUe") );

    EXPECT_FALSE( *FromString<bool>("false") );
    EXPECT_FALSE( *FromString<bool>("off") );
    EXPECT_FALSE( *FromString<bool>("no") );
    EXPECT_FALSE( *FromString<bool>("0") );
    EXPECT_FALSE( *FromString<bool>("FaLsE") );

    EXPECT_STREQ( "from string", (*FromString<std::string>("from string")).c_str() );

    EXPECT_TRUE( (uint8_t)1 == FromString<uint8_t>(std::string("1")) );
    EXPECT_TRUE( (uint8_t)12 == FromString<uint8_t>(std::string("12")) );
    EXPECT_FALSE( (uint8_t)12 == FromString<uint8_t>(std::string("21")) );

    EXPECT_TRUE( (uint32_t)1 == FromString<uint32_t>("1") );
    EXPECT_TRUE( (uint32_t)1000 == FromString<uint32_t>("1000") );
    EXPECT_TRUE( (uint32_t)1234567 == FromString<uint32_t>("1234567") );
    EXPECT_TRUE( (uint32_t)std::numeric_limits<uint32_t>::max() == FromString<uint32_t>("4294967295") );
    EXPECT_FALSE( (uint32_t)1 == FromString<uint32_t>("0") );

    EXPECT_TRUE( (uint64_t)1 == FromString<uint64_t>("1") );
    EXPECT_TRUE( (uint64_t)1000 == FromString<uint64_t>("1000") );
    EXPECT_TRUE( (uint64_t)1234567 == FromString<uint64_t>("1234567") );
    EXPECT_TRUE( (uint64_t)std::numeric_limits<uint64_t>::max() == FromString<uint64_t>("18446744073709551615") );    
    EXPECT_FALSE( (uint64_t)1 == FromString<uint64_t>("0") );    

    EXPECT_TRUE( (int32_t)1 == FromString<int32_t>("1") );
    EXPECT_TRUE( (int32_t)1000 == FromString<int32_t>("1000") );
    EXPECT_TRUE( (int32_t)1234567 == FromString<int32_t>("1234567") );
    EXPECT_TRUE( (int32_t)std::numeric_limits<int32_t>::min() == FromString<int32_t>("-2147483648") );
    EXPECT_TRUE( (int32_t)std::numeric_limits<int32_t>::max() == FromString<int32_t>("2147483647") );
    EXPECT_FALSE( (int32_t)1 == FromString<int32_t>("0") );

    EXPECT_TRUE( (float)0.0f == FromString<float>("0.000000") );
    EXPECT_TRUE( (float)1.0f == FromString<float>("1.000000") );
    EXPECT_TRUE( (float)12.3456f == FromString<float>("12.345600") );
    EXPECT_TRUE( (float)-12.3456f == FromString<float>("-12.345600") );
    EXPECT_FALSE( (float)1.0f == FromString<float>("0.000000") );

    EXPECT_TRUE( (double)0.0 == FromString<double>("0.000000") );
    EXPECT_TRUE( (double)1.0 == FromString<double>("1.000000") );
    EXPECT_TRUE( (double)12.3456 == FromString<double>("12.345600") );
    EXPECT_TRUE( (double)-12.3456 == FromString<double>("-12.345600") );
    EXPECT_FALSE( (double)1.0 == FromString<double>("0.000000") );
}