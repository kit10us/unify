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

#include <unify/BRectangle.h>
#include <unify/V2.h>
#include <array>

class BRectangleTests : public ::testing::Test
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
/// Tests the default constructor of the Brect class, ensuring it initializes to zero.
/// </summary>
TEST_F(BRectangleTests, DefaultConstructor)
{
    unify::BRectangle<float> brect{};
    EXPECT_FLOAT_EQ(brect.dr.x, 0.0f);
    EXPECT_FLOAT_EQ(brect.dr.y, 0.0f);
    EXPECT_FLOAT_EQ(brect.ul.x, 0.0f);
    EXPECT_FLOAT_EQ(brect.ul.y, 0.0f);
}

/// <summary>
/// Tests the parameterized constructor of the Brect class, ensuring it initializes to the provided values
/// </summary>
TEST_F(BRectangleTests, ParameterizedConstructor)
{
    unify::V2<float> ul{1.0f, 2.0f};
    unify::V2<float> dr{3.0f, 4.0f};
    unify::BRectangle<float> brect{ul, dr};
    EXPECT_FLOAT_EQ(brect.ul.x, 1.0f);
    EXPECT_FLOAT_EQ(brect.ul.y, 2.0f);
    EXPECT_FLOAT_EQ(brect.dr.x, 3.0f);
    EXPECT_FLOAT_EQ(brect.dr.y, 4.0f);
}

/// <summary>
/// Tests the Fix() method of the Brect class, ensuring it correctly identifies when the dr
/// and ul corners are reversed and fixes them.
/// </summary>
TEST_F(BRectangleTests, Normalization)
{
    unify::BRectangle<float> brect{};
    brect.ul = {3.0f, 4.0f};
    brect.dr = {1.0f, 2.0f};
    EXPECT_TRUE(brect.Normalized() == unify::BRectangle<float>({1.0f, 2.0f}, {3.0f, 4.0f}));
    EXPECT_TRUE(brect.Normalize());
    EXPECT_FLOAT_EQ(brect.ul.x, 1.0f);
    EXPECT_FLOAT_EQ(brect.ul.y, 2.0f);
    EXPECT_FLOAT_EQ(brect.dr.x, 3.0f);
    EXPECT_FLOAT_EQ(brect.dr.y, 4.0f);
}

/// <summary>
/// Tests the Union() method of the Brect class, ensuring it correctly adds a bounding box with a position to the current bounding box.
/// </summary>
TEST_F(BRectangleTests, AddVector)
{
    unify::BRectangle<float> brect{{-3.0f, -4.0f}, {1.0f, 1.0f}};    
    unify::V2 position_inf{-40.0f, -50.0f};
    brect.Add(position_inf);
    EXPECT_FLOAT_EQ(brect.ul.x, -40.0f);
    EXPECT_FLOAT_EQ(brect.ul.y, -50.0f);
    EXPECT_FLOAT_EQ(brect.dr.x, 1.0f);
    EXPECT_FLOAT_EQ(brect.dr.y, 1.0f);

    unify::V2<float> position_sup{10.0f, 20.0f};
    brect.Add(unify::V2<float>{10.0f, 20.0f});

    EXPECT_FLOAT_EQ(brect.ul.x, -40.0f);
    EXPECT_FLOAT_EQ(brect.ul.y, -50.0f);
    EXPECT_FLOAT_EQ(brect.dr.x, 10.0f);
    EXPECT_FLOAT_EQ(brect.dr.y, 20.0f); 
}

/// <summary>
/// Tests the ContainsPoint() method of the Brect class, ensuring it correctly identifies when a
/// point is within the bounding box.
/// </summary>
TEST_F(BRectangleTests, ContainsPoint)
{
    unify::BRectangle brect{unify::V2{1.0f, 2.0f}, unify::V2{4.0f, 5.0f}};
    EXPECT_TRUE(brect.Contains(unify::V2{2.0f, 3.0f}));
    EXPECT_FALSE(brect.Contains(unify::V2{0.0f, 0.0f}));
    EXPECT_FALSE(brect.Contains(unify::V2{5.0f, 6.0f}));
}

/// <summary>
/// Tests the ContainsBrect() method of the Brect class, ensuring it correctly identifies when a
/// bounding box is within the bounding box.
/// </summary>
TEST_F(BRectangleTests, ContainsBrect)
{
    unify::BRectangle brect{unify::V2{1.0f, 2.0f}, unify::V2{4.0f, 5.0f}};
    unify::BRectangle innerBox{unify::V2{2.0f, 3.0f}, unify::V2{3.0f, 4.0f}};
    unify::BRectangle outerBox{unify::V2{0.0f, 1.0f}, unify::V2{5.0f, 6.0f}};
    EXPECT_TRUE(brect.Contains(innerBox));
    EXPECT_FALSE(brect.Contains(outerBox));
}

TEST_F(BRectangleTests, Size)
{
    unify::BRectangle brect{unify::V2{1.0f, 2.0f}, unify::V2{4.0f, 5.0f}};
    unify::V2 size = brect.Size();
    EXPECT_FLOAT_EQ(size.x, 3.0f);
    EXPECT_FLOAT_EQ(size.y, 3.0f);
}
