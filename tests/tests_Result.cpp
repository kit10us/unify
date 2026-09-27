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
#include <chrono>
#include <iomanip>

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

unify::Result<> FailureWithMessage()
{
    return unify::Failure{ "Failure Message." };
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
    unify::Success success{};
    EXPECT_EQ(typeid(*default_result) == typeid(success), true);
}

TEST_F(ResultTests, DefaultFailure)
{
    auto default_result = DefaultFailure();
    EXPECT_EQ(default_result.Success(), false);
    EXPECT_TRUE(default_result.Message().empty());
}

TEST_F(ResultTests, FailureWithMessage)
{
    auto default_result = FailureWithMessage();
    EXPECT_EQ(default_result.Success(), false);
    EXPECT_STREQ(default_result.Message().c_str(), "Failure Message.");
}

TEST_F(ResultTests, ValueSuccess)
{
    auto default_result = ValueSuccess();
    EXPECT_EQ(default_result.Success(), true);
    EXPECT_EQ(default_result.Value(), TestEnum::Value1);
}

TEST_F(ResultTests, Dereference)
{
    auto default_result = DefaultFailure();
    EXPECT_TRUE(!default_result);
    EXPECT_TRUE(default_result.Message().empty());
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
    EXPECT_STREQ(value_result.Message().c_str(), "Value failure.");
}

TEST_F(ResultTests, Or)
{
    EXPECT_EQ(ValueFailure().Or(TestEnum::Value2), TestEnum::Value2);
    EXPECT_EQ(ValueSuccess().Or(TestEnum::Value3), TestEnum::Value1);
}

bool TestReturnBool()
{
    volatile static uint32_t counter {};
    counter++;
    return true;
}

uint32_t TestReturnUInt32()
{
    volatile static uint32_t counter {};
    counter++;
    return counter;
}

unify::Result<> TestResultReturnSuccess()
{
    volatile static uint32_t counter {};
    counter++;
    return {};
}

unify::Result<> TestResultReturnFailure()
{
    volatile static uint32_t counter {};
    counter++;
    return unify::Failure{"Failure"};
}

/// @brief Counter used to measure how many times a result success is copy constructed.
class Counter
{
public:
    static int count;

    Counter()
    {
        count++;
    }
};

int Counter::count = 0;

unify::Result<Counter> ResultWithCounterOne()
{
    Counter::count = 0;
    return Counter{};
}

unify::Result<Counter> ResultWithCounterTwo()
{
    auto result = ResultWithCounterOne();
    return result;
}

unify::Result<Counter> ResultWithCounterThree()
{
    auto result = ResultWithCounterTwo();
    return result;
}

unify::Result<Counter> ResultWithCounterFour()
{
    auto result = ResultWithCounterThree();
    return result;
}

TEST_F(ResultTests, CounterTestOnce)
{
    auto result = ResultWithCounterOne();
    EXPECT_EQ(Counter::count, 1);
}

TEST_F(ResultTests, CounterTestFourTimes)
{
    auto result = ResultWithCounterFour();
    EXPECT_EQ(Counter::count, 1);
}


TEST_F(ResultTests, SpeedTest)
{
    using namespace std::chrono_literals;
    
    size_t call_duration_ms = 100;
    size_t call_iterations = 5;
    size_t bool_iterations {};
    size_t uint32_iterations {};
    size_t success_iterations {};
    size_t failure_iterations {};

    auto TestFunc = [&]()
    {
        {
            auto begin = std::chrono::steady_clock::now();
            do
            {
                auto result = TestReturnBool();
                bool_iterations++;
            } while ((std::chrono::steady_clock::now() - begin) < std::chrono::milliseconds(call_duration_ms));
        }
    
        {
            auto begin = std::chrono::steady_clock::now();
            do
            {
                auto result = TestReturnUInt32();
                uint32_iterations++;
            } while ((std::chrono::steady_clock::now() - begin) < std::chrono::milliseconds(call_duration_ms));
        }
        
        {
            auto begin = std::chrono::steady_clock::now();
            do
            {
                auto result = TestResultReturnSuccess(); 
                success_iterations++;
            } while ((std::chrono::steady_clock::now() - begin) < std::chrono::milliseconds(call_duration_ms));
        }

        {
            auto begin = std::chrono::steady_clock::now();
            do
            {
                auto result = TestResultReturnFailure(); 
                failure_iterations++;
            } while ((std::chrono::steady_clock::now() - begin) < std::chrono::milliseconds(call_duration_ms));
        }
    };

    for (size_t i = 0; i < call_iterations; i++)
    {
        TestFunc();
    }

    std::cout << "\n[ METRIC   ] call iterations:       " << std::setw(10) << std::right << call_iterations << std::flush;
    ::testing::Test::RecordProperty("Call iterations    ", std::to_string(call_iterations));
    
    std::cout << "\n[ METRIC   ] Call duration ms:      " << std::setw(10) << std::right << call_duration_ms << std::flush;
    ::testing::Test::RecordProperty("Call duration ms   ", std::to_string(call_duration_ms));

    std::cout << "\n[ METRIC   ] Bool iterations:       " << std::setw(10) << std::right << bool_iterations << std::flush;
    ::testing::Test::RecordProperty("Bool iterations    ", std::to_string(bool_iterations));

    std::cout << "\n[ METRIC   ] UInt32 iterations:     " << std::setw(10) << std::right << uint32_iterations << std::flush;
    ::testing::Test::RecordProperty("UInt32 iterations  ", std::to_string(uint32_iterations));

    std::cout << "\n[ METRIC   ] Success iterations:    " << std::setw(10) << std::right << success_iterations << std::flush;
    ::testing::Test::RecordProperty("Success iterations ", std::to_string(success_iterations));

    std::cout << "\n[ METRIC   ] Failure iterations:    " << std::setw(10) << std::right << failure_iterations << "\n" << std::flush;
    ::testing::Test::RecordProperty("Failure iterations ", std::to_string(failure_iterations));
}