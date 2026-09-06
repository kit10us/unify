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

#include <unify/Angle.h>

class AngleTests : public ::testing::Test
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
/// Tests the default constructor of the Angle class, ensuring it initializes to zero radians and zero degrees.
/// </summary>
TEST_F(AngleTests, DefaultConstructor)
{
    unify::Angle angle;
    EXPECT_FLOAT_EQ(angle.ToRadians(), 0.0);
    EXPECT_FLOAT_EQ(angle.ToDegrees(), 0.0);
}

/// <summary>
/// Tests that PI in radians equates to 180 in degrees.
/// </summary>
TEST_F(AngleTests, RadiansPIDegrees180)
{
    unify::Angle angle {unify::AnglePI()};
    EXPECT_FLOAT_EQ(angle.ToRadians(), unify::PI);
    EXPECT_FLOAT_EQ(angle.ToDegrees(), 180.0);
}

/// <summary>
/// Tests multiplying an angle by a scalar, ensuring that multiplying 2*PI radians results in TAU radians.
/// </summary>
TEST_F(AngleTests, Multiply)
{
    unify::Angle angle {unify::AnglePI() * 2.0f};
    EXPECT_FLOAT_EQ(angle.ToRadians(), unify::TAU);
}

TEST_F(AngleTests, Divide)
{
    unify::Angle angle {unify::AnglePI2() / 2.0f};
    EXPECT_FLOAT_EQ(angle.ToRadians(), unify::PI);
}

TEST_F(AngleTests, ExcessPI)
{
    unify::Angle angle {unify::AnglePI2() + unify::AnglePI()};
    EXPECT_FLOAT_EQ(angle.ToRadians(), unify::TAU + unify::PI);
}

TEST_F(AngleTests, Normalize)
{
    unify::Angle angle {unify::AnglePI2() + unify::AnglePI()};
    auto magnitude = angle.Normalize();
    EXPECT_FLOAT_EQ(magnitude, 1.0f);
    EXPECT_PRED_FORMAT2(::testing::FloatLE, (angle - unify::AngleInDegrees(180.0f)).ToDegrees(), 1.0f);
}

TEST_F(AngleTests, SineOf90Degrees)
{
    unify::Angle angle {unify::AngleInDegrees(90.0f)};
    EXPECT_FLOAT_EQ(std::sin(angle.ToRadians()), 1.0f);
}

TEST_F(AngleTests, CosineOf180Degrees)
{
    unify::Angle angle {unify::AngleInDegrees(180.0f)};
    EXPECT_FLOAT_EQ(std::cos(angle.ToRadians()), -1.0f);
}

TEST_F(AngleTests, ToStringRadians)
{
    unify::Angle angle {unify::AnglePI()};
    EXPECT_STREQ(angle.ToString().c_str(), "3.141593r");
}

TEST_F(AngleTests, ToStringDegrees)
{
    unify::Angle angle {unify::AngleInDegrees(90.0f)};
    EXPECT_STREQ(angle.ToString(false).c_str(), "90.000000d");
}