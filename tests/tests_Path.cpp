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

#include <unify/Path.h>

class PathTests : public ::testing::Test
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
/// Tests the default constructor of the Path class, ensuring it initializes correctly.
/// </summary>
TEST_F(PathTests, TestConstructors)
{
    unify::Path path{};
    EXPECT_TRUE(path.IsEmpty());
    EXPECT_FALSE(path.HasScheme());
}

/// <summary>
/// Test URI named constructors.
/// </summary>
TEST_F(PathTests, TestFileSchemeConstructorEmpty)
{
    using namespace unify;

    Path path = Path::MakeFile();

    EXPECT_TRUE(path.IsEmpty());

    // A default file path has a scheme.
    EXPECT_TRUE(path.HasScheme());
}

TEST_F(PathTests, TestFileSchemeConstructorPath)
{
    using namespace unify;
    Path path = Path::MakeFile("/home/user");

    EXPECT_FALSE(path.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path.HasScheme());

    EXPECT_STREQ(path.GetScheme().c_str(), "file");
    
    EXPECT_STREQ(path.GetPath().c_str(), "/home/user");

    EXPECT_STREQ(path.ToString().c_str(), "file:///home/user");

    EXPECT_STREQ(path.ToString(Slash::Backward).c_str(), "file://\\home\\user");
}