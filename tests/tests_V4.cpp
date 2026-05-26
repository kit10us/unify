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

#include <unify/V4.h>

class V4Tests : public ::testing::Test
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
/// Tests the default constructor of the V4 class, ensuring it initializes to zero.
/// </summary>
TEST_F(V4Tests, TestDefaultConstructor)
{
    unify::V4 V4{};
    EXPECT_FLOAT_EQ(V4.x, 0.0);
    EXPECT_FLOAT_EQ(V4.y, 0.0);
    EXPECT_FLOAT_EQ(V4.z, 0.0);
}

/// <summary>
/// Tests the parameterized constructor of the V4 class, ensuring it initializes to the provided values.
/// </summary>
TEST_F(V4Tests, TestParameterizedConstructor)   
{
    unify::V4 V4{3.0f, 4.0f, 5.0f, 1.0f};
    EXPECT_FLOAT_EQ(V4.x, 3.0f);
    EXPECT_FLOAT_EQ(V4.y, 4.0f);
    EXPECT_FLOAT_EQ(V4.z, 5.0f);
    EXPECT_FLOAT_EQ(V4.w, 1.0f);
}

/// <summary>
/// Tests the operator[] of the V4 class, ensuring it correctly accesses the x, y, and z components of the vector.
/// </summary>
TEST_F(V4Tests, TestOperatorIndex)
{
    unify::V4 V4{3.0f, 4.0f, 5.0f, 1.0f};
    EXPECT_FLOAT_EQ(V4[0], 3.0f);
    EXPECT_FLOAT_EQ(V4[1], 4.0f);
    EXPECT_FLOAT_EQ(V4[2], 5.0f);
    EXPECT_FLOAT_EQ(V4[3], 1.0f);
    EXPECT_THROW(V4[4], unify::Exception);
    EXPECT_THROW(V4[100], unify::Exception);
    EXPECT_THROW(V4[static_cast<size_t>(-1)], unify::Exception);
}

/// <summary>
/// Tests the Length() method of the V4 class, ensuring it calculates the correct length of the vector.
/// </summary> 
TEST_F(V4Tests, TestLength)
{
    unify::V4 V4{3.0f, 4.0f, 5.0f, 1.0f};
    
    // Approximate
    EXPECT_TRUE(V4.Length() >= 7.1f);
    EXPECT_TRUE(V4.Length() <= 7.2f);
}

/// <summary>
/// Tests the Normalize() method of the V4 class, ensuring it normalizes the vector correctly.
/// </summary>
TEST_F(V4Tests, TestNormalize)
{
    unify::V4 V4{3.0f, 4.0f, 5.0f, 1.0f};
    V4.Normalize();

    // Approximate
    EXPECT_TRUE(V4.x >= 0.42f);
    EXPECT_TRUE(V4.x <= 0.43f);
    
    // Approximate
    EXPECT_TRUE(V4.y >= 0.56f); 
    EXPECT_TRUE(V4.y <= 0.57f);
    
    // Approximate
    EXPECT_TRUE(V4.z >= 0.70f); 
    EXPECT_TRUE(V4.z <= 0.71f);

    // Approximate
    EXPECT_TRUE(V4.w >= 0.14f); 
    EXPECT_TRUE(V4.w <= 0.15f);
}

/// <summary>
/// Tests the Dot() method of the V4 class, ensuring it calculates the correct dot product of two vectors.
/// </summary>
TEST_F(V4Tests, TestDot)
{
    unify::V4 v1{1.0f, 2.0f, 3.0f, 4.0f};
    unify::V4 V4{4.0f, 5.0f, 6.0f, 7.0f};
    EXPECT_FLOAT_EQ(v1.Dot(V4), 60.0);
}


/// <summary>
/// Tests the IsZero() method of the V4 class, ensuring it correctly identifies a zero vector
/// </summary>
TEST_F(V4Tests, TestIsZero)
{
    unify::V4 v1{0.0f, 0.0f, 0.0f, 0.0f};
    unify::V4 V4{1.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_TRUE(v1.IsZero());
    EXPECT_FALSE(V4.IsZero());
}

/// <summary>
/// Tests the Absolute() method of the V4 class, ensuring it returns the correct absolute value of the vector.
/// </summary>
TEST_F(V4Tests, TestAbsolute)
{
    unify::V4 v1{-3.0f, 4.0f, 5.0f, 1.0f};
    unify::V4 absV1 = v1.Absolute();
    EXPECT_FLOAT_EQ(absV1.x, 3.0f);
    EXPECT_FLOAT_EQ(absV1.y, 4.0f);
    EXPECT_FLOAT_EQ(absV1.z, 5.0f);
    EXPECT_FLOAT_EQ(absV1.w, 1.0f);
}

/*
/// <summary>
/// Tests the Cast() function for V4, ensuring it correctly converts a V4 to a string representation.
/// </summary>
TEST_F(V4Tests, TestCastToString)
{
    unify::V4<int> v1{3, 4, 5, 1};
    auto str = unify::ToString(v1);
    EXPECT_TRUE(str.has_value());
    if (!str.has_value())
    {
        return;
    }

    EXPECT_EQ(*str, "3, 4, 5, 1");
}

/// <summary>
/// Tests the Cast() function for V3, ensuring it correctly converts a string representation to a V3.
/// </summary>
TEST_F(V4Tests, TestCastFromString)
{
    std::string str = "3, 4, 5, 6";
    unify::V4<int> v = unify::V4FromString<int>(str);
    EXPECT_FLOAT_EQ(v.x, 3.0);
    EXPECT_FLOAT_EQ(v.y, 4.0);
    EXPECT_FLOAT_EQ(v.z, 5.0);
    EXPECT_FLOAT_EQ(v.w, 6.0);
}
*/