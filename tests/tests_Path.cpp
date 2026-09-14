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
TEST_F(PathTests, Constructors)
{
    unify::Path path{};
    EXPECT_TRUE(path.IsEmpty());
    EXPECT_FALSE(path.HasScheme());
}

/// <summary>
/// Test URI named constructors.
/// </summary>
TEST_F(PathTests, FileSchemeConstructorEmpty)
{
    using namespace unify;

    Path path = Path::MakeFile();

    EXPECT_TRUE(path.IsEmpty());

    // A default file path has a scheme.
    EXPECT_TRUE(path.HasScheme());
}

TEST_F(PathTests, DefaultConstructor)
{
    using namespace unify;
    Path path = {};

    EXPECT_TRUE(path.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_FALSE(path.HasScheme());

    EXPECT_STREQ(path.GetScheme().c_str(), "");
    
    EXPECT_STREQ(path.GetPath().c_str(), "");

    EXPECT_STREQ(path.ToString().c_str(), "");
}

TEST_F(PathTests, FileSchemeConstructor)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path path = Path::MakeFile("/home/user");

    EXPECT_FALSE(path.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path.HasScheme());

    EXPECT_STREQ(path.GetScheme().c_str(), "file");
    
    EXPECT_STREQ(path.GetPath().c_str(), "/home/user");

    EXPECT_STREQ(path.ToString().c_str(), "file:///home/user");

    EXPECT_STREQ(path.ToString(Slash::Backward).c_str(), R"(file://\home\user)");
}

TEST_F(PathTests, FileStringConstructorWithScheme)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path path = Path("file:///home/user");

    EXPECT_FALSE(path.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path.HasScheme());

    EXPECT_STREQ(path.GetScheme().c_str(), "file");
    
    EXPECT_STREQ(path.GetPath().c_str(), "/home/user");

    EXPECT_STREQ(path.ToString().c_str(), "file:///home/user");

    EXPECT_STREQ(path.ToString(Slash::Backward).c_str(), R"(file://\home\user)");
}

TEST_F(PathTests, CombineSameSchemeConstructor)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path path_combine = Path::Path(Path("file:///home/user"), Path("file://documents"));

    EXPECT_FALSE(path_combine.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path_combine.HasScheme());

    EXPECT_STREQ(path_combine.GetScheme().c_str(), "file");
    
    EXPECT_STREQ(path_combine.GetPath().c_str(), "/home/user/documents");

    EXPECT_STREQ(path_combine.ToString().c_str(), "file:///home/user/documents");

    EXPECT_STREQ(path_combine.ToString(Slash::Backward).c_str(), R"(file://\home\user\documents)");
}

TEST_F(PathTests, CombineLeftSchemeConstructor)
{
    using namespace unify;
    using namespace std::string_view_literals;
    
    Path path_left_scheme = Path::Path(Path("file:///home/user"), Path("documents"));

    EXPECT_FALSE(path_left_scheme.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path_left_scheme.HasScheme());

    EXPECT_STREQ(path_left_scheme.GetScheme().c_str(), "file");
    
    EXPECT_STREQ(path_left_scheme.GetPath().c_str(), "/home/user/documents");

    EXPECT_STREQ(path_left_scheme.ToString().c_str(), "file:///home/user/documents");

    EXPECT_STREQ(path_left_scheme.ToString(Slash::Backward).c_str(), R"(file://\home\user\documents)");

    Path path_right_scheme = Path::Path(Path("/home/user"), Path("file://documents"));

    EXPECT_FALSE(path_right_scheme.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path_right_scheme.HasScheme());

    EXPECT_STREQ(path_right_scheme.GetScheme().c_str(), "file");
    
    EXPECT_STREQ(path_right_scheme.GetPath().c_str(), "/home/user/documents");

    EXPECT_STREQ(path_right_scheme.ToString().c_str(), "file:///home/user/documents");

    EXPECT_STREQ(path_right_scheme.ToString(Slash::Backward).c_str(), R"(file://\home\user\documents)");
}

TEST_F(PathTests, CombineMixedSchemeConstructor)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path path_mixed_scheme = Path::Path(Path("http://www.example.com/site"), Path("file://documents"));

    EXPECT_FALSE(path_mixed_scheme.IsEmpty());

    // An empty URI path is still a URI path format.
    EXPECT_TRUE(path_mixed_scheme.HasScheme());

    EXPECT_STREQ(path_mixed_scheme.GetScheme().c_str(), "http");
    
    EXPECT_STREQ(path_mixed_scheme.GetPath().c_str(), "www.example.com/site/documents");

    EXPECT_STREQ(path_mixed_scheme.ToString().c_str(), "http://www.example.com/site/documents");

    EXPECT_STREQ(path_mixed_scheme.ToString(Slash::Forward).c_str(), R"(http://www.example.com/site/documents)");
}

TEST_F(PathTests, SplitForward)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path back_slash_path = {"/one/two/three"};
    auto spliced = back_slash_path.Split();

    ASSERT_EQ(spliced.size(), 6);
    EXPECT_STREQ(spliced[0].c_str(), "/");
    EXPECT_STREQ(spliced[1].c_str(), "one");
    EXPECT_STREQ(spliced[2].c_str(), "/");
    EXPECT_STREQ(spliced[3].c_str(), "two");
    EXPECT_STREQ(spliced[4].c_str(), "/");
    EXPECT_STREQ(spliced[5].c_str(), "three");
}

TEST_F(PathTests, SplitBackward)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path back_slash_path = {"\\one\\two\\three"};
    auto spliced = back_slash_path.Split();

    ASSERT_EQ(spliced.size(), 6);
    EXPECT_STREQ(spliced[0].c_str(), "/");
    EXPECT_STREQ(spliced[1].c_str(), "one");
    EXPECT_STREQ(spliced[2].c_str(), "/");
    EXPECT_STREQ(spliced[3].c_str(), "two");
    EXPECT_STREQ(spliced[4].c_str(), "/");
    EXPECT_STREQ(spliced[5].c_str(), "three");
}

TEST_F(PathTests, SplitMixedSlash)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path back_slash_path = {"/one\\two/three"};
    auto spliced = back_slash_path.Split();

    ASSERT_EQ(spliced.size(), 6);
    EXPECT_STREQ(spliced[0].c_str(), "/");
    EXPECT_STREQ(spliced[1].c_str(), "one");
    EXPECT_STREQ(spliced[2].c_str(), "/");
    EXPECT_STREQ(spliced[3].c_str(), "two");
    EXPECT_STREQ(spliced[4].c_str(), "/");
    EXPECT_STREQ(spliced[5].c_str(), "three");
}

TEST_F(PathTests, SplitNoRoot)
{
    using namespace unify;
    using namespace std::string_view_literals;

    Path back_slash_path = {"one/two/three/four/five.ext"};
    auto spliced = back_slash_path.Split();

    ASSERT_EQ(spliced.size(), 9);
    EXPECT_STREQ(spliced[0].c_str(), "one");
    EXPECT_STREQ(spliced[1].c_str(), "/");
    EXPECT_STREQ(spliced[2].c_str(), "two");
    EXPECT_STREQ(spliced[3].c_str(), "/");
    EXPECT_STREQ(spliced[4].c_str(), "three");
    EXPECT_STREQ(spliced[5].c_str(), "/");
    EXPECT_STREQ(spliced[6].c_str(), "four");
    EXPECT_STREQ(spliced[7].c_str(), "/");
    EXPECT_STREQ(spliced[8].c_str(), "five.ext");
}

TEST_F(PathTests, SplitQuoted)
{
        using namespace unify;
    using namespace std::string_view_literals;

    Path back_slash_path = {R"(c:\one\two\"file with spaces.ext)"};
    auto spliced = back_slash_path.Split(Slash::Backward);

    ASSERT_EQ(spliced.size(), 7);
    EXPECT_STREQ(spliced[0].c_str(), "c:");
    EXPECT_STREQ(spliced[1].c_str(), "\\");
    EXPECT_STREQ(spliced[2].c_str(), "one");
    EXPECT_STREQ(spliced[3].c_str(), "\\");
    EXPECT_STREQ(spliced[4].c_str(), "two");
    EXPECT_STREQ(spliced[5].c_str(), "\\");
    EXPECT_STREQ(spliced[6].c_str(), "file with spaces.ext");
}