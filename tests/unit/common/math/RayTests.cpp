/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** RayTests.cpp
*/

#include <gtest/gtest.h>

#include "types/math/Ray.hpp"

using namespace Raytracer::Common;

TEST(RayTests, ValidConstruction)
{
    Math::Ray ray(
        Math::Point3D(1, 2, 3),
        Math::Vector3D(4, 5, 6)
    );

    EXPECT_EQ(ray.origin.x, 1) << "origin.x should be 1";
    EXPECT_EQ(ray.origin.y, 2) << "origin.y should be 2";
    EXPECT_EQ(ray.origin.z, 3) << "origin.z should be 3";
    EXPECT_EQ(ray.direction.x, 4) << "direction.x should be 4";
    EXPECT_EQ(ray.direction.y, 5) << "direction.y should be 5";
    EXPECT_EQ(ray.direction.z, 6) << "direction.z should be 6";
}

TEST(RayTests, ValidCopyConstruction)
{
    Math::Ray ray(
        Math::Point3D(1, 2, 3),
        Math::Vector3D(4, 5, 6)
    );
    Math::Ray ray2(ray);

    EXPECT_EQ(ray2.origin.x, 1) << "origin.x should be 1";
    EXPECT_EQ(ray2.origin.y, 2) << "origin.y should be 2";
    EXPECT_EQ(ray2.origin.z, 3) << "origin.z should be 3";
    EXPECT_EQ(ray2.direction.x, 4) << "direction.x should be 4";
    EXPECT_EQ(ray2.direction.y, 5) << "direction.y should be 5";
    EXPECT_EQ(ray2.direction.z, 6) << "direction.z should be 6";
}

TEST(RayTests, ValidAssignment)
{
    Math::Point3D origin(1, 2, 3);
    Math::Vector3D direction(4, 5, 6);
    Math::Ray ray(origin, direction);
    Math::Ray copy;

    copy = ray;
    EXPECT_EQ(copy.origin.x, origin.x) << "origin.x should be 1";
    EXPECT_EQ(copy.origin.y, origin.y) << "origin.y should be 2";
    EXPECT_EQ(copy.origin.z, origin.z) << "origin.z should be 3";
    EXPECT_EQ(copy.direction.x, direction.x) << "direction.x should be 4";
    EXPECT_EQ(copy.direction.y, direction.y) << "direction.y should be 5";
    EXPECT_EQ(copy.direction.z, direction.z) << "direction.z should be 6";
    origin.x = 7;
    origin.y = 8;
    origin.z = 9;
    direction.x = 10;
    direction.y = 11;
    direction.z = 12;
    EXPECT_EQ(ray.origin.x, 1) << "origin.x should still be 1";
    EXPECT_EQ(ray.origin.y, 2) << "origin.y should still be 2";
    EXPECT_EQ(ray.origin.z, 3) << "origin.z should still be 3";
}
