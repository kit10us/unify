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

#include <unify/TimeDelta.h>

class TimeDeltaTests : public ::testing::Test
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
/// Tests the default constructor of the TimeDelta class, ensuring it initializes to zero.
/// </summary>
TEST_F(TimeDeltaTests, DefaultConstructor)
{
    unify::TimeDelta timeDelta{};
    EXPECT_FLOAT_EQ(timeDelta.AsSeconds(), 0.0);
    EXPECT_FLOAT_EQ(timeDelta.AsMS(), 0.0);
    EXPECT_FLOAT_EQ(timeDelta.AsMicros(), 0.0);
}

TEST_F(TimeDeltaTests, ToString)
{
    unify::TimeDelta timeDelta{};
    auto result = unify::ToString(timeDelta);
    ASSERT_TRUE(!result); // Expecting std::nullopt since ToString is not implemented.
}

TEST_F(TimeDeltaTests, FromString)
{
    unify::TimeDelta timeDelta{};
    auto result = unify::FromString("1.0");
    ASSERT_TRUE(!result); // Expecting std::nullopt since FromString is not implemented.
}
