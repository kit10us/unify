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

#include <unify/TexCoords.h>

class TexCoordsTests : public ::testing::Test
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
/// Tests the default constructor of the UV class, ensuring it initializes to zero.
/// </summary>
TEST_F(TexCoordsTests, TestDefaultConstructor)
{
    unify::TexCoords uv{};
    EXPECT_FLOAT_EQ(uv.u, 0.0);
    EXPECT_FLOAT_EQ(uv.v, 0.0);
}

/// <summary>
/// Tests the parameterized constructor of the UV class, ensuring it initializes to the provided values.
/// </summary>
TEST_F(TexCoordsTests, TestParameterizedConstructor)   
{
    unify::TexCoords uv{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(uv.u, 3.0);
    EXPECT_FLOAT_EQ(uv.v, 4.0);
}

/// <summary>
/// Tests the operator[] of the UV class, ensuring it correctly accesses the x and y components of the vector.
/// </summary>
TEST_F(TexCoordsTests, TestOperatorIndex)
{
    unify::TexCoords uv{3.0f, 4.0f};
    EXPECT_FLOAT_EQ(uv[0], 3.0);
    EXPECT_FLOAT_EQ(uv[1], 4.0);
    EXPECT_THROW(uv[2], unify::Exception);
    EXPECT_THROW(uv[100], unify::Exception);
    EXPECT_THROW(uv[static_cast<size_t>(-1)], unify::Exception);
}

/// <summary>
/// Tests the Cast() function for UV, ensuring it correctly converts a UV to a string representation.
/// </summary>
TEST_F(TexCoordsTests, TestCastToString)
{
    unify::TexCoords uv{3.1, 4.2};
    auto str = unify::ToString(uv);    
    EXPECT_TRUE(str.has_value());
    if (!str.has_value())
    {
        return;
    }
    
    EXPECT_EQ(*str, "3.100000, 4.200000");
}