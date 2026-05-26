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

#include <unify/V2.h>

class V2Tests : public ::testing::Test
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
/// Tests the default constructor of the V2 class, ensuring it initializes to zero.
/// </summary>
TEST_F(V2Tests, TestDefaultConstructor)
{
    unify::V2 v2{};
    EXPECT_FLOAT_EQ(v2.x, 0.0);
    EXPECT_FLOAT_EQ(v2.y, 0.0);
}

/// <summary>
/// Tests the parameterized constructor of the V2 class, ensuring it initializes to the provided values.
/// </summary>
TEST_F(V2Tests, TestParameterizedConstructor)   
{
    unify::V2 v2{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(v2.x, 3.0);
    EXPECT_FLOAT_EQ(v2.y, 4.0);
}

/// <summary>
/// Tests the operator[] of the V2 class, ensuring it correctly accesses the x and y components of the vector.
/// </summary>
TEST_F(V2Tests, TestOperatorIndex)
{
    unify::V2 v2{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(v2[0], 3.0);
    EXPECT_FLOAT_EQ(v2[1], 4.0);
    EXPECT_THROW(v2[2], unify::Exception);
    EXPECT_THROW(v2[100], unify::Exception);
    EXPECT_THROW(v2[static_cast<size_t>(-1)], unify::Exception);
}

/// <summary>
/// Tests the Length() method of the V2 class, ensuring it calculates the correct length of the vector.
/// </summary> 
TEST_F(V2Tests, TestLength)
{
    unify::V2 v2{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(v2.Length(), 5.0);
}

/// <summary>
/// Tests the Normalize() method of the V2 class, ensuring it normalizes the vector correctly.
/// </summary>
TEST_F(V2Tests, TestNormalize)
{
    unify::V2 v2{3.0f, 4.0f};
    v2.Normalize();
    EXPECT_FLOAT_EQ(v2.x, 0.6);
    EXPECT_FLOAT_EQ(v2.y, 0.8);
}

/// <summary>
/// Tests the Dot() method of the V2 class, ensuring it calculates the correct dot product of two vectors.
/// </summary>
TEST_F(V2Tests, TestDot)
{
    unify::V2 v1{1.0f, 2.0f};
    unify::V2 v2{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(v1.Dot(v2), 11.0);
}

/// <summary>
/// Tests the Angle() method of the V2 class, ensuring it calculates the correct angle between two vectors.
/// </summary>
TEST_F(V2Tests, TestAngle)
{
    unify::V2 v1{1.0f, 0.0f};
    unify::V2 v2{0.0f, 1.0f};
    unify::Angle angle = v1.Angle(v2);
    EXPECT_FLOAT_EQ(angle.ToDegrees(), 90.0);
}

/// <summary>
/// Tests the Distance() method of the V2 class, ensuring it calculates the correct distance between two vectors.
/// </summary>
TEST_F(V2Tests, TestDistance)
{
    unify::V2 v1{1.0f, 2.0f};
    unify::V2 v2{4.0f, 6.0f};
    EXPECT_FLOAT_EQ(v1.Distance(v2), 5.0);
}

/// <summary>
/// Tests the IsZero() method of the V2 class, ensuring it correctly identifies a zero vector
/// </summary>
TEST_F(V2Tests, TestIsZero)
{
    unify::V2 v1{0.0f, 0.0f};
    unify::V2 v2{1.0f, 0.0f};
    EXPECT_TRUE(v1.IsZero());
    EXPECT_FALSE(v2.IsZero());
}

/// <summary>
/// Tests the Absolute() method of the V2 class, ensuring it returns the correct absolute value of the vector.
/// </summary>
TEST_F(V2Tests, TestAbsolute)
{
    unify::V2 v1{-3.0f, 4.0f};
    unify::V2 absV1 = v1.Absolute();
    EXPECT_FLOAT_EQ(absV1.x, 3.0);
    EXPECT_FLOAT_EQ(absV1.y, 4.0);
}

/// <summary>
/// Tests the Cast() function for V2, ensuring it correctly converts a V2 to a string representation.
/// </summary>
TEST_F(V2Tests, TestCastToString)
{
    unify::V2<int> v1{3, 4};
    auto str = unify::ToString(v1);    
    EXPECT_TRUE(str.has_value());
    if (!str.has_value())
    {
        return;
    }
    
    EXPECT_EQ(*str, "3, 4");
}