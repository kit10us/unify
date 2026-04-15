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

#include <unify/LineSegment3.h>

class LineSegment3Tests : public ::testing::Test
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
/// Tests the default constructor of the LineSegment3 class, ensuring it initializes correctly.
/// </summary>
TEST_F(LineSegment3Tests, TestDefaultConstructor)
{
    unify::LineSegment3<float> segment;
    EXPECT_FLOAT_EQ(segment.begin.x, 0.0);
    EXPECT_FLOAT_EQ(segment.begin.y, 0.0);
    EXPECT_FLOAT_EQ(segment.begin.z, 0.0);
    EXPECT_FLOAT_EQ(segment.end.x, 0.0);
    EXPECT_FLOAT_EQ(segment.end.y, 0.0);
    EXPECT_FLOAT_EQ(segment.end.z, 0.0);
}

/// <summary>
/// Tests the parameterized constructor of the LineSegment3 class, ensuring it initializes to the provided values
/// </summary>
TEST_F(LineSegment3Tests, TestParameterizedConstructor)
{
    unify::V3<float> begin{1.0f, 2.0f, 3.0f};
    unify::V3<float> end{4.0f, 5.0f, 6.0f};
    unify::LineSegment3<float> segment{begin, end};
    EXPECT_FLOAT_EQ(segment.begin.x, 1.0);
    EXPECT_FLOAT_EQ(segment.begin.y, 2.0);
    EXPECT_FLOAT_EQ(segment.begin.z, 3.0);
    EXPECT_FLOAT_EQ(segment.end.x, 4.0);
    EXPECT_FLOAT_EQ(segment.end.y, 5.0);
    EXPECT_FLOAT_EQ(segment.end.z, 6.0);
}

/// <summary>
/// Tests the Length() method of the LineSegment3 class, ensuring it correctly calculates the length of
/// the line segment.
/// </summary>
TEST_F(LineSegment3Tests, TestLength)
{
    unify::V3<float> begin{1.0f, 2.0f, 3.0f};
    unify::V3<float> end{4.0f, 6.0f, 8.0f};
    unify::LineSegment3<float> segment{begin, end};
    auto length = segment.Length();
    EXPECT_TRUE(length >= 7.07f); // Approximate length is 7.0710678118654755
    EXPECT_TRUE(length <= 7.08f); // Approximate length is 7.0710678118654755
}
