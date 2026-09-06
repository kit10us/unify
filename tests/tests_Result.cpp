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

#include <unify/Result.h>

class ResultTests : public ::testing::Test
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

unify::Result<> DefaultSuccess()
{
    return {};
}

unify::Result<> DefaultFailure()
{
    return unify::Failure{};
}

unify::Result<> DefaultFailureMessage()
{
    return unify::Failure{ "Default failure." };
}

enum class TestEnum
{
    Value1,
    Value2,
    Value3
};

unify::Result<TestEnum> ValueSuccess()
{
    return TestEnum::Value1;
}

unify::Result<TestEnum> ValueFailure()
{
    return unify::Failure{ "Value failure." };
}

TEST_F(ResultTests, DefaultSuccess)
{
    auto default_result = DefaultSuccess();
    EXPECT_EQ(default_result.Success(), true);
}

TEST_F(ResultTests, DefaultFailure)
{
    auto default_result = DefaultFailure();
    EXPECT_EQ(default_result.Success(), false);
    EXPECT_EQ(default_result.Message(), "Unspecified failure.");
}

TEST_F(ResultTests, Dereference)
{
    auto default_result = DefaultFailure();
    EXPECT_TRUE(!default_result);
    EXPECT_EQ(default_result.Message(), "Unspecified failure.");
}

TEST_F(ResultTests, DefaultFailureMessage)
{
    auto default_result = DefaultFailure();
    EXPECT_FALSE(default_result.Success());
    EXPECT_EQ(default_result.Message(), "Unspecified failure.");
}

TEST_F(ResultTests, ValueSuccess)
{
    auto value_result = ValueSuccess();
    EXPECT_EQ(value_result.Success(), true);
    EXPECT_EQ(value_result.Value(), TestEnum::Value1);
}

TEST_F(ResultTests, OperatorValueSuccess)
{
    auto value_result = ValueSuccess();
    EXPECT_EQ(value_result.Success(), true);
    EXPECT_EQ(value_result(), TestEnum::Value1);
}

TEST_F(ResultTests, OperatorValueFailure)
{
    auto value_result = ValueFailure();
    EXPECT_EQ(value_result.Success(), false);
    EXPECT_EQ(value_result.Message(), "Value failure.");
    EXPECT_THROW((value_result() == TestEnum::Value1), std::bad_variant_access);
}

TEST_F(ResultTests, Or)
{
    EXPECT_EQ(ValueFailure().Or(TestEnum::Value2), TestEnum::Value2);
    EXPECT_EQ(ValueSuccess().Or(TestEnum::Value3), TestEnum::Value1);
}
