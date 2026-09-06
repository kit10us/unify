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

#include <unify/Color.h>

class ColorTests : public ::testing::Test
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
/// Tests the parameterized constructor of the Color class, ensuring it initializes to the provided values.
/// </summary>
TEST_F(ColorTests, ParameterizedConstructor)   
{
    unify::Color color{10, 20, 40, 255};
    EXPECT_EQ(color.r, 10);
    EXPECT_EQ(color.g, 20);
    EXPECT_EQ(color.b, 40);
    EXPECT_EQ(color.a, 255);
}

/// <summary>
/// Tests the operator[] of the Color class, ensuring it correctly accesses the r, g, b, and a components of the color.
/// </summary>
TEST_F(ColorTests, OperatorIndex)
{
    unify::Color color{10, 20, 40, 255};
    EXPECT_EQ(color.linear[0], 10);
    EXPECT_EQ(color.linear[1], 20);
    EXPECT_EQ(color.linear[2], 40);
    EXPECT_EQ(color.linear[3], 255);
}

TEST_F(ColorTests, ToString)
{
    using namespace std::string_literals;

    unify::Color color{10, 20, 40, 255};
    auto color_s = color.ToString();
    ASSERT_TRUE(color_s.has_value());
    EXPECT_EQ(*color_s, "10, 20, 40, 255"s);
}
