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

#include <unify/Ray.h>

class RayTests : public ::testing::Test
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
/// Tests the default constructor of the Ray class, ensuring it initializes origin facing forward (z-axis).
/// </summary>
TEST_F(RayTests, TestDefaultConstructor)
{
    unify::Ray<float> ray{};
    EXPECT_FLOAT_EQ(ray.origin.x, 0.0f);
    EXPECT_FLOAT_EQ(ray.origin.y, 0.0f);
    EXPECT_FLOAT_EQ(ray.origin.z, 0.0f);
    EXPECT_FLOAT_EQ(ray.direction.x, 0.0f);
    EXPECT_FLOAT_EQ(ray.direction.y, 0.0f);
    EXPECT_FLOAT_EQ(ray.direction.z, 1.0f);
}

/// <summary>
/// Tests the default constructor of the Ray class, ensuring it initializes origin facing forward (z-axis).
/// </summary>
TEST_F(RayTests, TestRayFromOriginAndDirection)
{
    unify::Ray<float> ray = unify::RayFromOriginAndDirection<float>({1.0f, 2.0f, 3.0}, {4.0, 5.0, 6.0});
    EXPECT_FLOAT_EQ(ray.origin.x, 1.0f);
    EXPECT_FLOAT_EQ(ray.origin.y, 2.0f);
    EXPECT_FLOAT_EQ(ray.origin.z, 3.0f);
    EXPECT_FLOAT_EQ(ray.direction.x, 4.0f);
    EXPECT_FLOAT_EQ(ray.direction.y, 5.0f);
    EXPECT_FLOAT_EQ(ray.direction.z, 6.0f);
}
