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

#include <unify/Matrix.h>

class MatrixTests : public ::testing::Test
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
/// Tests the default constructor of the Matrix class (not identity for optimization).
/// </summary>
TEST_F(MatrixTests, DefaultConstructor)
{
    unify::Matrix matrix{};
    EXPECT_FLOAT_EQ(matrix.m[0][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[0][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[0][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[0][3], 0.0f);

    EXPECT_FLOAT_EQ(matrix.m[1][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[1][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[1][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[1][3], 0.0f);

    EXPECT_FLOAT_EQ(matrix.m[2][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[2][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[2][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[2][3], 0.0f);

    EXPECT_FLOAT_EQ(matrix.m[3][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[3][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[3][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[3][3], 0.0f);
}

TEST_F(MatrixTests, IdentityConstructor)
{
    unify::Matrix matrix = unify::MatrixIdentity();
    EXPECT_FLOAT_EQ(matrix.m[0][0], 1.0f);
    EXPECT_FLOAT_EQ(matrix.m[0][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[0][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[0][3], 0.0f);

    EXPECT_FLOAT_EQ(matrix.m[1][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[1][1], 1.0f);
    EXPECT_FLOAT_EQ(matrix.m[1][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[1][3], 0.0f);

    EXPECT_FLOAT_EQ(matrix.m[2][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[2][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[2][2], 1.0f);
    EXPECT_FLOAT_EQ(matrix.m[2][3], 0.0f);

    EXPECT_FLOAT_EQ(matrix.m[3][0], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[3][1], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[3][2], 0.0f);
    EXPECT_FLOAT_EQ(matrix.m[3][3], 1.0f);
}