/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** HitInfoTests.cpp
*/

#include <gtest/gtest.h>

#include "types/math/HitInfo.hpp"

using namespace Raytracer::Common;

TEST(HitInfoTests, SimpleConstruction)
{
    Math::HitInfo info = {
        .didHit = true,
        .distance = 12.34f,
        .hitPoint = Math::Point3D(1, 2, 3),
        .normal = Math::Vector3D(4, 5, 6),
    };

    EXPECT_EQ(info.didHit, true) << "didHit should be true";
    EXPECT_EQ(info.distance, 12.34f) << "distance should be 12.34f";
    EXPECT_EQ(info.hitPoint.x, 1) << "hitPoint.x should be 1";
    EXPECT_EQ(info.hitPoint.y, 2) << "hitPoint.y should be 2";
    EXPECT_EQ(info.hitPoint.z, 3) << "hitPoint.z should be 3";
    EXPECT_EQ(info.normal.x, 4) << "normal.x should be 4";
    EXPECT_EQ(info.normal.y, 5) << "normal.y should be 5";
    EXPECT_EQ(info.normal.z, 6) << "normal.z should be 6";
}

TEST(HitInfoTests, CopyConstruction)
{
    Math::HitInfo info = {
        .didHit = true,
        .distance = 12.34f,
        .hitPoint = Math::Point3D(1, 2, 3),
        .normal = Math::Vector3D(4, 5, 6),
    };
    Math::HitInfo info2(info);

    EXPECT_EQ(info2.didHit, true) << "didHit should be true";
    EXPECT_EQ(info2.distance, 12.34f) << "distance should be 12.34f";
    EXPECT_EQ(info2.hitPoint.x, 1) << "hitPoint.x should be 1";
    EXPECT_EQ(info2.hitPoint.y, 2) << "hitPoint.y should be 2";
    EXPECT_EQ(info2.hitPoint.z, 3) << "hitPoint.z should be 3";
    EXPECT_EQ(info2.normal.x, 4) << "normal.x should be 4";
    EXPECT_EQ(info2.normal.y, 5) << "normal.y should be 5";
    EXPECT_EQ(info2.normal.z, 6) << "normal.z should be 6";
}

TEST(HitInfoTests, CopyAssignment)
{
    Math::HitInfo info = {
        .didHit = true,
        .distance = 12.34f,
        .hitPoint = Math::Point3D(1, 2, 3),
        .normal = Math::Vector3D(4, 5, 6),
    };
    Math::HitInfo info2 = info;

    EXPECT_EQ(info2.didHit, true) << "didHit should be true";
    EXPECT_EQ(info2.distance, 12.34f) << "distance should be 12.34f";
    EXPECT_EQ(info2.hitPoint.x, 1) << "hitPoint.x should be 1";
    EXPECT_EQ(info2.hitPoint.y, 2) << "hitPoint.y should be 2";
    EXPECT_EQ(info2.hitPoint.z, 3) << "hitPoint.z should be 3";
    EXPECT_EQ(info2.normal.x, 4) << "normal.x should be 4";
    EXPECT_EQ(info2.normal.y, 5) << "normal.y should be 5";
    EXPECT_EQ(info2.normal.z, 6) << "normal.z should be 6";
    info.hitPoint.x = 7;
    info.hitPoint.y = 8;
    info.hitPoint.z = 9;
    info.normal.x = 10;
    info.normal.y = 11;
    info.normal.z = 12;
    EXPECT_EQ(info2.hitPoint.x, 1) << "hitPoint.x should still be 1";
    EXPECT_EQ(info2.hitPoint.y, 2) << "hitPoint.y should still be 2";
    EXPECT_EQ(info2.hitPoint.z, 3) << "hitPoint.z should still be 3";
    EXPECT_EQ(info2.normal.x, 4) << "normal.x should still be 4";
    EXPECT_EQ(info2.normal.y, 5) << "normal.y should still be 5";
    EXPECT_EQ(info2.normal.z, 6) << "normal.z should still be 6";
}

TEST(HitInfoTests, DefaultConstruction)
{
    Math::HitInfo info = {
        .didHit = false,
        .distance = 0.0f,
        .hitPoint = Math::Point3D(0, 0, 0),
        .normal = Math::Vector3D(0, 0, 0),
    };

    EXPECT_EQ(info.didHit, false) << "didHit should be false";
    EXPECT_EQ(info.distance, 0.0f) << "distance should be 0.0f";
    EXPECT_EQ(info.hitPoint.x, 0) << "hitPoint.x should be 0";
    EXPECT_EQ(info.hitPoint.y, 0) << "hitPoint.y should be 0";
    EXPECT_EQ(info.hitPoint.z, 0) << "hitPoint.z should be 0";
    EXPECT_EQ(info.normal.x, 0) << "normal.x should be 0";
    EXPECT_EQ(info.normal.y, 0) << "normal.y should be 0";
    EXPECT_EQ(info.normal.z, 0) << "normal.z should be 0";
}
