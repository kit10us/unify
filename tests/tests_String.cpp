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
#include <unify/String.h>

class StringTests : public ::testing::Test
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

TEST_F(StringTests, NoTrim)
{
    std::string str {};
    ASSERT_NO_THROW((str = unify::String::TrimWhitespace(str)));
    EXPECT_TRUE(str.empty());

}

TEST_F(StringTests, TrimSpacesFront)
{
    std::string str {"   One, Two, Three"};
    str = unify::String::TrimWhitespace(str);
    EXPECT_STREQ(str.c_str(), "One, Two, Three");
}

TEST_F(StringTests, TrimSpacesEnd)
{
    std::string str {"One, Two, Three   "};
    str = unify::String::TrimWhitespace(str);
    EXPECT_STREQ(str.c_str(), "One, Two, Three");
}

TEST_F(StringTests, TrimSpacesBoth)
{
    std::string str {"   One, Two, Three   "};
    str = unify::String::TrimWhitespace(str);
    EXPECT_STREQ(str.c_str(), "One, Two, Three");
}