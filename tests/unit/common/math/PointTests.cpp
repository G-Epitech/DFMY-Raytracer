/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/math/Point.hpp"

using namespace Raytracer::Common;

TEST(Point3DTests, ValidConstruction)
{
    Math::Point3D p(1, 2, 3);

    EXPECT_EQ(p.x, 1) << "x should be 1";
    EXPECT_EQ(p.y, 2) << "y should be 2";
    EXPECT_EQ(p.z, 3) << "z should be 3";
}

TEST(Point3DTests, ValidCopyConstruction)
{
    Math::Point3D p(1, 2, 3);
    Math::Point3D p2(p);

    EXPECT_EQ(p2.x, 1) << "x should be 1";
    EXPECT_EQ(p2.y, 2) << "y should be 2";
    EXPECT_EQ(p2.z, 3) << "z should be 3";
}

TEST(Point3DTests, ValidAssignment)
{
    Math::Point3D a(1, 2, 3);
    Math::Point3D b(4, 5, 6);

    a = b;
    EXPECT_EQ(a.x, 4) << "x should be 4";
    EXPECT_EQ(a.y, 5) << "y should be 5";
    EXPECT_EQ(a.z, 6) << "z should be 6";
    EXPECT_EQ(b.x, 4) << "x should still be 4";
    EXPECT_EQ(b.y, 5) << "y should still be 5";
    EXPECT_EQ(b.z, 6) << "z should still be 6";
}

TEST(Point3DTests, ValidAssignmentWithUpdate)
{
    Math::Point3D a(1, 2, 3);
    Math::Point3D b(4, 5, 6);

    a = b;
    EXPECT_EQ(a.x, 4) << "x should be 4";
    EXPECT_EQ(a.y, 5) << "y should be 5";
    EXPECT_EQ(a.z, 6) << "z should be 6";
    a.x = 7;
    a.y = 8;
    a.z = 9;
    EXPECT_EQ(b.x, 4) << "x should still be 4";
    EXPECT_EQ(b.y, 5) << "y should still be 5";
    EXPECT_EQ(b.z, 6) << "z should still be 6";
}

TEST(Point3DTests, PrintPoint)
{
    Math::Point3D p(1, 2, 3);
    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "Point3D(1, 2, 3)") << "Point should be printed as Point3D(1, 2, 3)";
}
