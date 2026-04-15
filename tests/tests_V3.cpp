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

#include <unify/V3.h>

class V3Tests : public ::testing::Test
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
/// Tests the default constructor of the V3 class, ensuring it initializes to zero.
/// </summary>
TEST_F(V3Tests, TestDefaultConstructor)
{
    unify::V3 V3{};
    EXPECT_FLOAT_EQ(V3.x, 0.0);
    EXPECT_FLOAT_EQ(V3.y, 0.0);
    EXPECT_FLOAT_EQ(V3.z, 0.0);
}

/// <summary>
/// Tests the parameterized constructor of the V3 class, ensuring it initializes to the provided values.
/// </summary>
TEST_F(V3Tests, TestParameterizedConstructor)   
{
    unify::V3 V3{3.0f, 4.0f, 5.0f};
    EXPECT_FLOAT_EQ(V3.x, 3.0);
    EXPECT_FLOAT_EQ(V3.y, 4.0);
    EXPECT_FLOAT_EQ(V3.z, 5.0);
}

/// <summary>
/// Tests the operator[] of the V3 class, ensuring it correctly accesses the x, y, and z components of the vector.
/// </summary>
TEST_F(V3Tests, TestOperatorIndex)
{
    unify::V3 V3{3.0f, 4.0f, 5.0f};
    EXPECT_FLOAT_EQ(V3[0], 3.0);
    EXPECT_FLOAT_EQ(V3[1], 4.0);
    EXPECT_FLOAT_EQ(V3[2], 5.0);
    EXPECT_THROW(V3[3], unify::Exception);
    EXPECT_THROW(V3[100], unify::Exception);
    EXPECT_THROW(V3[static_cast<size_t>(-1)], unify::Exception);
}

/// <summary>
/// Tests the Length() method of the V3 class, ensuring it calculates the correct length of the vector.
/// </summary> 
TEST_F(V3Tests, TestLength)
{
    unify::V3 V3{3.0f, 4.0f, 5.0f};
    EXPECT_FLOAT_EQ(V3.Length(), 7.0710678118654755);
}

/// <summary>
/// Tests the Normalize() method of the V3 class, ensuring it normalizes the vector correctly.
/// </summary>
TEST_F(V3Tests, TestNormalize)
{
    unify::V3 V3{3.0f, 4.0f, 5.0f};
    V3.Normalize();
    EXPECT_FLOAT_EQ(V3.x, 0.4242640687119285);
    EXPECT_FLOAT_EQ(V3.y, 0.5656854249492381);
    EXPECT_FLOAT_EQ(V3.z, 0.7071067811865476);
}

/// <summary>
/// Tests the Dot() method of the V3 class, ensuring it calculates the correct dot product of two vectors.
/// </summary>
TEST_F(V3Tests, TestDot)
{
    unify::V3 v1{1.0f, 2.0f, 3.0f};
    unify::V3 V3{4.0f, 5.0f, 6.0f};
    EXPECT_FLOAT_EQ(v1.Dot(V3), 32.0);
}

/// <summary>
/// Tests the Distance() method of the V3 class, ensuring it calculates the correct distance between two vectors.
/// </summary>
TEST_F(V3Tests, TestDistance)
{
    unify::V3 v1{1.0f, 2.0f, 3.0f};
    unify::V3 V3{4.0f, 6.0f, 4.0f};
    auto distance = v1.Distance(V3);
    EXPECT_TRUE(distance >= 5.0f); // Approximate distance is 5.0990195135927845
    EXPECT_TRUE(distance <= 5.1f); // Approximate distance is 5.0990195135927845
}

/// <summary>
/// Tests the IsZero() method of the V3 class, ensuring it correctly identifies a zero vector
/// </summary>
TEST_F(V3Tests, TestIsZero)
{
    unify::V3 v1{0.0f, 0.0f, 0.0f};
    unify::V3 V3{1.0f, 0.0f, 0.0f};
    EXPECT_TRUE(v1.IsZero());
    EXPECT_FALSE(V3.IsZero());
}

/// <summary>
/// Tests the Absolute() method of the V3 class, ensuring it returns the correct absolute value of the vector.
/// </summary>
TEST_F(V3Tests, TestAbsolute)
{
    unify::V3 v1{-3.0f, 4.0f, 5.0f};
    unify::V3 absV1 = v1.Absolute();
    EXPECT_FLOAT_EQ(absV1.x, 3.0);
    EXPECT_FLOAT_EQ(absV1.y, 4.0);
    EXPECT_FLOAT_EQ(absV1.z, 5.0);
}

/// <summary>
/// Tests the Cast() function for V3, ensuring it correctly converts a V3 to a string representation.
/// </summary>
TEST_F(V3Tests, TestCastToString)
{
    unify::V3<int> v1{3, 4, 5};
    std::string str = unify::Cast(v1);
    EXPECT_EQ(str, "3, 4, 5");
}

/// <summary>
/// Tests the Cast() function for V3, ensuring it correctly converts a string representation to a V3.
/// </summary>
TEST_F(V3Tests, TestCastFromString)
{
    std::string str = "3, 4, 5";
    unify::V3<int> V3 = unify::V3FromString<int>(str);
    EXPECT_FLOAT_EQ(V3.x, 3.0);
    EXPECT_FLOAT_EQ(V3.y, 4.0);
    EXPECT_FLOAT_EQ(V3.z, 5.0);
}