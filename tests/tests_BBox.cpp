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

#include <unify/BBox.h>
#include <unify/Ray.h>
#include <unify/LineSegment3.h>

#include <array>

class BBoxTests : public ::testing::Test
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
/// Tests the default constructor of the BBox class, ensuring it initializes to zero.
/// </summary>
TEST_F(BBoxTests, DefaultConstructor)
{
    unify::BBox bbox{};
    EXPECT_FLOAT_EQ(bbox.sup.x, 0.0f);
    EXPECT_FLOAT_EQ(bbox.sup.y, 0.0f);
    EXPECT_FLOAT_EQ(bbox.inf.x, 0.0f);
    EXPECT_FLOAT_EQ(bbox.inf.y, 0.0f);
}

/// <summary>
/// Tests the parameterized constructor of the BBox class, ensuring it initializes to the provided values
/// </summary>
TEST_F(BBoxTests, ParameterizedConstructor)
{
    unify::V3 sup{3.0f, 4.0f, 5.0f};
    unify::V3 inf{1.0f, 2.0f, 3.0f};
    unify::BBox bbox{inf, sup};
    EXPECT_FLOAT_EQ(bbox.sup.x, 3.0f);
    EXPECT_FLOAT_EQ(bbox.sup.y, 4.0f);
    EXPECT_FLOAT_EQ(bbox.sup.z, 5.0f);
    EXPECT_FLOAT_EQ(bbox.inf.x, 1.0f);
    EXPECT_FLOAT_EQ(bbox.inf.y, 2.0f);
    EXPECT_FLOAT_EQ(bbox.inf.z, 3.0f);
}

/// <summary>
/// Tests the square constructor of the BBox class, ensuring it initializes to a cube with the
/// correct dimensions.
/// </summary>
TEST_F(BBoxTests, SquareConstructor)
{
    unify::BBox bbox{10.0f};
    EXPECT_FLOAT_EQ(bbox.sup.x, 5.0f);
    EXPECT_FLOAT_EQ(bbox.sup.y, 5.0f);
    EXPECT_FLOAT_EQ(bbox.sup.z, 5.0f);
    EXPECT_FLOAT_EQ(bbox.inf.x, -5.0f);
    EXPECT_FLOAT_EQ(bbox.inf.y, -5.0f);
    EXPECT_FLOAT_EQ(bbox.inf.z, -5.0f);
}

/// <summary>
/// Tests the Fix() method of the BBox class, ensuring it correctly identifies when the sup
/// and inf corners are reversed and fixes them.
/// </summary>
TEST_F(BBoxTests, Fix)
{
    unify::BBox bbox{};
    bbox.inf = {3.0f, 4.0f, 5.0f};
    bbox.sup = {1.0f, 2.0f, 3.0f};
    EXPECT_TRUE(bbox.Fix());
    EXPECT_FALSE(bbox.Fix());
    EXPECT_FLOAT_EQ(bbox.sup.x, 3.0f);
    EXPECT_FLOAT_EQ(bbox.sup.y, 4.0f);
    EXPECT_FLOAT_EQ(bbox.sup.z, 5.0f);
    EXPECT_FLOAT_EQ(bbox.inf.x, 1.0f);
    EXPECT_FLOAT_EQ(bbox.inf.y, 2.0f);
    EXPECT_FLOAT_EQ(bbox.inf.z, 3.0f);
}

/// <summary>
/// Tests the GenerateCorners() method of the BBox class, ensuring it correctly generates the corners
/// of the bounding box.
/// </summary>
TEST_F(BBoxTests, GenerateCorners)
{
    unify::BBox bbox{unify::V3{1.0f, 2.0f, 3.0f}, unify::V3{4.0f, 5.0f, 6.0f}};
    std::array<unify::V3<float>, 8> corners;
    bbox.GenerateCorners(corners.data());
    EXPECT_FLOAT_EQ(corners[0].x, 1.0f);
    EXPECT_FLOAT_EQ(corners[0].y, 2.0f);
    EXPECT_FLOAT_EQ(corners[0].z, 3.0f);
    EXPECT_FLOAT_EQ(corners[7].x, 4.0f);
    EXPECT_FLOAT_EQ(corners[7].y, 5.0f);
    EXPECT_FLOAT_EQ(corners[7].z, 6.0f);
}

/// <summary>
/// Tests the ContainsPoint() method of the BBox class, ensuring it correctly identifies when a
/// point is within the bounding box.
/// </summary>
TEST_F(BBoxTests, ContainsPoint)
{
    unify::BBox bbox{unify::V3{1.0f, 2.0f, 3.0f}, unify::V3{4.0f, 5.0f, 6.0f}};
    EXPECT_TRUE(bbox.ContainsPoint(unify::V3{2.0f, 3.0f, 4.0f}));
    EXPECT_FALSE(bbox.ContainsPoint(unify::V3{0.0f, 0.0f, 0.0f}));
    EXPECT_FALSE(bbox.ContainsPoint(unify::V3{5.0f, 6.0f, 7.0f}));
}

/// <summary>
/// Tests the ContainsBBox() method of the BBox class, ensuring it correctly identifies when a
/// bounding box is within the bounding box.
/// </summary>
TEST_F(BBoxTests, ContainsBBox)
{
    unify::BBox bbox{unify::V3{1.0f, 2.0f, 3.0f}, unify::V3{4.0f, 5.0f, 6.0f}};
    unify::BBox innerBox{unify::V3{2.0f, 3.0f, 4.0f}, unify::V3{3.0f, 4.0f, 5.0f}};
    unify::BBox outerBox{unify::V3{0.0f, 1.0f, 2.0f}, unify::V3{5.0f, 6.0f, 7.0f}};
    EXPECT_TRUE(bbox.ContainsBBox(innerBox));
    EXPECT_FALSE(bbox.ContainsBBox(outerBox));
}

/// <summary>
/// Tests the Union() method of the BBox class, ensuring it correctly adds a bounding box with a position to the current bounding box.
/// </summary>
TEST_F(BBoxTests, Union)
{
    unify::BBox bbox{{-3.0f, -4.0f, -5.0f}, {1.0f, 1.0f, 1.0f}};
    unify::BBox otherBBox{unify::V3{1.0f, 2.0f, 3.0f}, unify::V3{4.0f, 5.0f, 6.0f}};
    unify::V3 position_sup{10.0f, 20.0f, 30.0f};
    bbox.Union(otherBBox, position_sup);
    EXPECT_FLOAT_EQ(bbox.inf.x, -3.0f);
    EXPECT_FLOAT_EQ(bbox.inf.y, -4.0f);
    EXPECT_FLOAT_EQ(bbox.inf.z, -5.0f);
    EXPECT_FLOAT_EQ(bbox.sup.x, 14.0f);
    EXPECT_FLOAT_EQ(bbox.sup.y, 25.0f);
    EXPECT_FLOAT_EQ(bbox.sup.z, 36.0f);
    
    unify::V3 position_inf{-40.0f, -50.0f, -60.0f};
    bbox.Union(otherBBox, position_inf);
    EXPECT_FLOAT_EQ(bbox.inf.x, -39.0f);
    EXPECT_FLOAT_EQ(bbox.inf.y, -48.0f);
    EXPECT_FLOAT_EQ(bbox.inf.z, -57.0f);
    EXPECT_FLOAT_EQ(bbox.sup.x, 14.0f);
    EXPECT_FLOAT_EQ(bbox.sup.y, 25.0f);
    EXPECT_FLOAT_EQ(bbox.sup.z, 36.0f);
}

/// <summary>
/// Tests the Intersects() method of the BBox class, ensuring it correctly identifies when a ray intersects with the bounding box.
/// </summary>
TEST_F(BBoxTests, Intersects)
{
    unify::BBox bbox{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    unify::Ray ray = unify::RayFromOriginAndDirection<float>({-1.0f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f});
    auto hit = bbox.Intersects(ray);
    EXPECT_TRUE(hit.has_value());
    EXPECT_FLOAT_EQ(hit->distance, 1.0f);
    EXPECT_FLOAT_EQ(hit->point.x, 0.0f);
    EXPECT_FLOAT_EQ(hit->point.y, 0.5f);
    EXPECT_FLOAT_EQ(hit->point.z, 0.5f);
}

TEST_F(BBoxTests, Clip)
{
    unify::BBox bbox{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    unify::Ray ray = unify::RayFromOriginAndDirection<float>({-1.0f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f});
    auto segment = bbox.Clip(ray);
    EXPECT_TRUE(segment.has_value());
    EXPECT_FLOAT_EQ(segment->begin.x, 0.0f);
    EXPECT_FLOAT_EQ(segment->begin.y, 0.5f);
    EXPECT_FLOAT_EQ(segment->begin.z, 0.5f);
    EXPECT_FLOAT_EQ(segment->end.x, 1.0f);
    EXPECT_FLOAT_EQ(segment->end.y, 0.5f);
    EXPECT_FLOAT_EQ(segment->end.z, 0.5f);
}