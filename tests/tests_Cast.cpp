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
    EXPECT_TRUE( std::string("0") == unify::ToString(Char{'0'}) );
    EXPECT_TRUE( std::string("1") == unify::ToString(Char{'1'}) );
    EXPECT_TRUE( std::string("a") == unify::ToString(Char{'a'}) );
    EXPECT_TRUE( std::string("Z") == unify::ToString(Char{'Z'}) );
    EXPECT_FALSE( std::string("a") == unify::ToString(Char{'b'}) );

    /*
    EXPECT_TRUE( std::string("Hello, world!") == unify::ToString("Hello, world!") );
    EXPECT_FALSE( std::string("!dlrow ,olleH") == unify::ToString("Hello, world!") );
    */

    // TODO: wstring
    
    EXPECT_TRUE( std::string("true") == unify::ToString(true) );
    EXPECT_TRUE( std::string("false") == unify::ToString(false) );

    EXPECT_TRUE( std::string("1") == unify::ToString((uint8_t)1) );
    EXPECT_TRUE( std::string("12") == unify::ToString((uint8_t)12) );
    EXPECT_FALSE( std::string("21") == unify::ToString((uint8_t)12) );

    EXPECT_TRUE( std::string("97") == unify::ToString('a') );
    EXPECT_TRUE( std::string("90") == unify::ToString('Z') );
    EXPECT_TRUE( std::string("49") == unify::ToString('1') );
    EXPECT_FALSE( std::string("12") == unify::ToString('a') );

    EXPECT_TRUE( std::string("1") == unify::ToString((uint32_t)1) );
    EXPECT_TRUE( std::string("1000") == unify::ToString((uint32_t)1000) );
    EXPECT_TRUE( std::string("1234567") == unify::ToString((uint32_t)1234567) );
    EXPECT_TRUE( std::string("4294967295") == unify::ToString((uint32_t)std::numeric_limits<uint32_t>::max()) );
    EXPECT_FALSE( std::string("0") == unify::ToString((uint32_t)1) );

    EXPECT_TRUE( std::string("1") == unify::ToString((uint64_t)1) );
    EXPECT_TRUE( std::string("1000") == unify::ToString((uint64_t)1000) );
    EXPECT_TRUE( std::string("1234567") == unify::ToString((uint64_t)1234567) );
    EXPECT_TRUE( std::string("18446744073709551615") == unify::ToString((uint64_t)std::numeric_limits<uint64_t>::max()) );    
    EXPECT_FALSE( std::string("0") == unify::ToString((uint64_t)1) );    

    EXPECT_TRUE( std::string("1") == unify::ToString((int32_t)1) );
    EXPECT_TRUE( std::string("1000") == unify::ToString((int32_t)1000) );
    EXPECT_TRUE( std::string("1234567") == unify::ToString((int32_t)1234567) );
    EXPECT_TRUE( std::string("-2147483648") == unify::ToString((int32_t)std::numeric_limits<int32_t>::min()) );
    EXPECT_TRUE( std::string("2147483647") == unify::ToString((int32_t)std::numeric_limits<int32_t>::max()) );
    EXPECT_FALSE( std::string("0") == unify::ToString((int32_t)1) );

    EXPECT_TRUE( std::string("1") == unify::ToString((int64_t)1) );
    EXPECT_TRUE( std::string("1000") == unify::ToString((int64_t)1000) );
    EXPECT_TRUE( std::string("1234567") == unify::ToString((int64_t)1234567) );
    EXPECT_TRUE( std::string("-9223372036854775808") == unify::ToString((int64_t)std::numeric_limits<int64_t>::min()) );    
    EXPECT_TRUE( std::string("9223372036854775807") == unify::ToString((int64_t)std::numeric_limits<int64_t>::max()) );    
    EXPECT_FALSE( std::string("0") == unify::ToString((int64_t)1) );

    EXPECT_TRUE( std::string("0.000000") == unify::ToString((float)0.0f) );
    EXPECT_TRUE( std::string("1.000000") == unify::ToString((float)1.0f) );
    EXPECT_TRUE( std::string("12.345600") == unify::ToString((float)12.3456f) );
    EXPECT_TRUE( std::string("-12.345600") == unify::ToString((float)-12.3456f) );
    EXPECT_FALSE( std::string("0.000000") == unify::ToString((float)1.0f) );

    EXPECT_TRUE( std::string("0.000000") == unify::ToString((double)0.0) );
    EXPECT_TRUE( std::string("1.000000") == unify::ToString((double)1.0) );
    EXPECT_TRUE( std::string("12.345600") == unify::ToString((double)12.3456) );
    EXPECT_TRUE( std::string("-12.345600") == unify::ToString((double)-12.3456) );
    EXPECT_FALSE( std::string("0.000000") == unify::ToString((double)1.0) );

    EXPECT_TRUE( std::string("1") == unify::ToString((uint16_t)1) );
    EXPECT_TRUE( std::string("1000") == unify::ToString((uint16_t)1000) );
    EXPECT_TRUE( std::string("12345") == unify::ToString((uint16_t)12345) );
    EXPECT_TRUE( std::string("0") == unify::ToString((uint16_t)std::numeric_limits<uint16_t>::min()) );
    EXPECT_TRUE( std::string("65535") == unify::ToString((uint16_t)std::numeric_limits<uint16_t>::max()) );
    EXPECT_FALSE( std::string("0") == unify::ToString((uint16_t)1) );
    
    EXPECT_TRUE( std::string("1") == unify::ToString((uint16_t)1) );
    EXPECT_TRUE( std::string("1000") == unify::ToString((int16_t)1000) );
    EXPECT_TRUE( std::string("-1234") == unify::ToString((int16_t)-1234) );
    EXPECT_TRUE( std::string("-32768") == unify::ToString((int16_t)std::numeric_limits<int16_t>::min()) );
    EXPECT_TRUE( std::string("32767") == unify::ToString((int16_t)std::numeric_limits<int16_t>::max()) );
    EXPECT_FALSE( std::string("0") == unify::ToString((int16_t)1) );

    EXPECT_TRUE( true == unify::FromString<bool>("true") );
    EXPECT_TRUE( true == unify::FromString<bool>("on") );
    EXPECT_TRUE( true == unify::FromString<bool>("yes") );
    EXPECT_TRUE( true == unify::FromString<bool>("1") );
    EXPECT_TRUE( true == unify::FromString<bool>("123") );
    EXPECT_TRUE( true == unify::FromString<bool>("-123") );
    EXPECT_FALSE( true == unify::FromString<bool>("false") );

    EXPECT_TRUE( false == unify::FromString<bool>("false") );
    EXPECT_TRUE( false == unify::FromString<bool>("off") );
    EXPECT_TRUE( false == unify::FromString<bool>("no") );
    EXPECT_TRUE( false == unify::FromString<bool>("0") );
    EXPECT_FALSE( false == unify::FromString<bool>("true") );



    EXPECT_TRUE( (uint8_t)1 == unify::FromString<uint8_t>(std::string("1")) );
    EXPECT_TRUE( (uint8_t)12 == unify::FromString<uint8_t>(std::string("12")) );
    EXPECT_FALSE( (uint8_t)12 == unify::FromString<uint8_t>(std::string("21")) );

    EXPECT_TRUE( (uint32_t)1 == unify::FromString<uint32_t>("1") );
    EXPECT_TRUE( (uint32_t)1000 == unify::FromString<uint32_t>("1000") );
    EXPECT_TRUE( (uint32_t)1234567 == unify::FromString<uint32_t>("1234567") );
    EXPECT_TRUE( (uint32_t)std::numeric_limits<uint32_t>::max() == unify::FromString<uint32_t>("4294967295") );
    EXPECT_FALSE( (uint32_t)1 == unify::FromString<uint32_t>("0") );

    EXPECT_TRUE( (uint64_t)1 == unify::FromString<uint64_t>("1") );
    EXPECT_TRUE( (uint64_t)1000 == unify::FromString<uint64_t>("1000") );
    EXPECT_TRUE( (uint64_t)1234567 == unify::FromString<uint64_t>("1234567") );
    EXPECT_TRUE( (uint64_t)std::numeric_limits<uint64_t>::max() == unify::FromString<uint64_t>("18446744073709551615") );    
    EXPECT_FALSE( (uint64_t)1 == unify::FromString<uint64_t>("0") );    

    EXPECT_TRUE( (int32_t)1 == unify::FromString<int32_t>("1") );
    EXPECT_TRUE( (int32_t)1000 == unify::FromString<int32_t>("1000") );
    EXPECT_TRUE( (int32_t)1234567 == unify::FromString<int32_t>("1234567") );
    EXPECT_TRUE( (int32_t)std::numeric_limits<int32_t>::min() == unify::FromString<int32_t>("-2147483648") );
    EXPECT_TRUE( (int32_t)std::numeric_limits<int32_t>::max() == unify::FromString<int32_t>("2147483647") );
    EXPECT_FALSE( (int32_t)1 == unify::FromString<int32_t>("0") );

    EXPECT_TRUE( (float)0.0f == unify::FromString<float>("0.000000") );
    EXPECT_TRUE( (float)1.0f == unify::FromString<float>("1.000000") );
    EXPECT_TRUE( (float)12.3456f == unify::FromString<float>("12.345600") );
    EXPECT_TRUE( (float)-12.3456f == unify::FromString<float>("-12.345600") );
    EXPECT_FALSE( (float)1.0f == unify::FromString<float>("0.000000") );

    EXPECT_TRUE( (double)0.0 == unify::FromString<double>("0.000000") );
    EXPECT_TRUE( (double)1.0 == unify::FromString<double>("1.000000") );
    EXPECT_TRUE( (double)12.3456 == unify::FromString<double>("12.345600") );
    EXPECT_TRUE( (double)-12.3456 == unify::FromString<double>("-12.345600") );
    EXPECT_FALSE( (double)1.0 == unify::FromString<double>("0.000000") );
}