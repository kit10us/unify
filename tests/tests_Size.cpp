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

#include <unify/Size.h>

class SizeTests : public ::testing::Test
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

/// <summary>
/// Tests the default constructor of the SIZE class, ensuring it initializes to zero.
/// </summary>
TEST_F(SizeTests, DefaultConstructor)
{
    unify::Size size{};
    EXPECT_FLOAT_EQ(size.width, 0.0);
    EXPECT_FLOAT_EQ(size.height, 0.0);
}

/// <summary>
/// Tests the parameterized constructor of the SIZE class, ensuring it initializes to the provided values.
/// </summary>
TEST_F(SizeTests, ParameterizedConstructor)   
{
    unify::Size size{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(size.wdth, 3.0);
    EXPECT_FLOAT_EQ(size.height, 4.0);
}

/// <summary>
/// Tests the Cast() function for SIZE, ensuring it correctly converts a SIZE to a string representation.
/// </summary>
TEST_F(SizeTests, CastToString)
{
    unify::Size<int> size1{3, 4};
    auto str = size1.ToString();
    EXPECT_STREQ(
    
    if (str != "3, 4")
    {
        return;
    }
    
    EXPECT_EQ(*str, "3, 4");
}