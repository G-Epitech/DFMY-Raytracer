/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** VectorTests.cpp
*/

#include <gtest/gtest.h>

#include "types/math/Vector.hpp"

using namespace Raytracer::Common;

TEST(Vector3DTests, ValidConstruction)
{
    Math::Vector3D v(1, 2, 3);

    EXPECT_EQ(v.x, 1) << "x should be 1";
    EXPECT_EQ(v.y, 2) << "y should be 2";
    EXPECT_EQ(v.z, 3) << "z should be 3";
}

TEST(Vector3DTests, EmptyConstruction)
{
    Math::Vector3D v;

    EXPECT_EQ(v.x, 0) << "x should be 0";
    EXPECT_EQ(v.y, 0) << "y should be 0";
    EXPECT_EQ(v.z, 0) << "z should be 0";
}

TEST(Vector3DTests, ValidCopyConstruction)
{
    Math::Vector3D v(1, 2, 3);
    Math::Vector3D v2(v);

    EXPECT_EQ(v2.x, 1) << "x should be 1";
    EXPECT_EQ(v2.y, 2) << "y should be 2";
    EXPECT_EQ(v2.z, 3) << "z should be 3";
}

TEST(Vector3DTests, ValidCopyAssignment)
{
    Math::Vector3D v(1, 2, 3);
    Math::Vector3D u(4, 5, 6);
    u = v;

    EXPECT_EQ(u.x, 1) << "v2.x should be 1";
    EXPECT_EQ(u.y, 2) << "v2.y should be 2";
    EXPECT_EQ(u.z, 3) << "v2.z should be 3";
    EXPECT_EQ(v.x, 1) << "v.x should still be 1";
    EXPECT_EQ(v.y, 2) << "v.y should still be 2";
    EXPECT_EQ(v.z, 3) << "v.z should still be 3";
}

TEST(Vector3DTests, TwoVectorsAddition)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    Math::Vector3D w = u + v;

    EXPECT_EQ(w.x, 5) << "w.x should be 5";
    EXPECT_EQ(w.y, 7) << "w.y should be 7";
    EXPECT_EQ(w.z, 9) << "w.z should be 9";
}

TEST(Vector3DTests, VectorAdditionOnThis)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    u += v;

    EXPECT_EQ(u.x, 5) << "u.x should be 5";
    EXPECT_EQ(u.y, 7) << "u.y should be 7";
    EXPECT_EQ(u.z, 9) << "u.z should be 9";
}

TEST(Vector3DTests, TwoVectorsSubtraction)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    Math::Vector3D w = u - v;

    EXPECT_EQ(w.x, -3) << "w.x should be -3";
    EXPECT_EQ(w.y, -3) << "w.y should be -3";
    EXPECT_EQ(w.z, -3) << "w.z should be -3";
}

TEST(Vector3DTests, VectorSubstractionOnThis)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    u -= v;

    EXPECT_EQ(u.x, -3) << "u.x should be -3";
    EXPECT_EQ(u.y, -3) << "u.y should be -3";
    EXPECT_EQ(u.z, -3) << "u.z should be -3";
}

TEST(Vector3DTests, TwoVectorsMultiplication)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    Math::Vector3D w = u * v;

    EXPECT_EQ(w.x, 4) << "w.x should be 4";
    EXPECT_EQ(w.y, 10) << "w.y should be 10";
    EXPECT_EQ(w.z, 18) << "w.z should be 18";
}

TEST(Vector3DTests, ScalarMultiplication)
{
    Math::Vector3D v(1, 2, 3);
    Math::Vector3D w = v * 2;

    EXPECT_EQ(w.x, 2) << "w.x should be 2";
    EXPECT_EQ(w.y, 4) << "w.y should be 4";
    EXPECT_EQ(w.z, 6) << "w.z should be 6";
}

TEST(Vector3DTests, VectorMultiplicationOnThis)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    u *= v;

    EXPECT_EQ(u.x, 4) << "u.x should be 4";
    EXPECT_EQ(u.y, 10) << "u.y should be 10";
    EXPECT_EQ(u.z, 18) << "u.z should be 18";
}

TEST(Vector3DTests, ScalarMultiplicationOnThis)
{
    Math::Vector3D v(1, 2, 3);
    v *= 2;

    EXPECT_EQ(v.x, 2) << "v.x should be 2";
    EXPECT_EQ(v.y, 4) << "v.y should be 4";
    EXPECT_EQ(v.z, 6) << "v.z should be 6";
}

TEST(Vector3DTests, VectorDivisionBy2)
{
    Math::Vector3D v(4, 8, 6);
    Math::Vector3D w = v / 2;

    EXPECT_EQ(w.x, 2) << "w.x should be 2";
    EXPECT_EQ(w.y, 4) << "w.y should be 4";
    EXPECT_EQ(w.z, 3) << "w.z should be 3";
}

TEST(Vector3DTests, VectorDivisionBy0)
{
    Math::Vector3D v(4, 8, 6);
    Math::Vector3D w = v / 0;

    EXPECT_EQ(w.x, 0) << "w.x should be 0";
    EXPECT_EQ(w.y, 0) << "w.y should be 0";
    EXPECT_EQ(w.z, 0) << "w.z should be 0";
}

TEST(Vector3DTests, VectorDivisionOnThis)
{
    Math::Vector3D v(4, 8, 6);
    v /= 2;

    EXPECT_EQ(v.x, 2) << "v.x should be 2";
    EXPECT_EQ(v.y, 4) << "v.y should be 4";
    EXPECT_EQ(v.z, 3) << "v.z should be 3";
}

TEST(Vector3DTests, VectorDivisionBy0OnThis)
{
    Math::Vector3D v(4, 8, 6);
    v /= 0;

    EXPECT_EQ(v.x, 4) << "v.x should be 4";
    EXPECT_EQ(v.y, 8) << "v.y should be 8";
    EXPECT_EQ(v.z, 6) << "v.z should be 6";
}

TEST(Vector3DTests, DotProduct)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    auto dot = u.dot(v);

    EXPECT_EQ(dot, 32) << "dot should be 32";
}

TEST(Vector3DTests, LengthOfNullVector)
{
    Math::Vector3D v(0, 0, 0);
    auto length = v.length();

    EXPECT_EQ(length, 0) << "length should be 0";
}

TEST(Vector3DTests, LengthOfPositiveVector)
{
    Math::Vector3D v(1, 2, 3);
    auto length = v.length();

    EXPECT_FLOAT_EQ(length, 3.7416575) << "length should be 3.7416575";
}

TEST(Vector3DTests, LengthOfNegativeVector)
{
    Math::Vector3D v(-1, -2, -3);
    auto length = v.length();

    EXPECT_FLOAT_EQ(length, 3.7416575) << "length should be 3.7416575";
}

TEST(Vector3DTests, CrossProduct)
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);
    auto w = u.cross(v);

    EXPECT_EQ(w.x, -3) << "w.x should be -3";
    EXPECT_EQ(w.y, 6) << "w.y should be 6";
    EXPECT_EQ(w.z, -3) << "w.z should be -3";
}

TEST(Vector3DTests, PrintVector)
{
    Math::Vector3D v(1, 2, 3);
    std::stringstream ss;
    ss << v;

    EXPECT_EQ(ss.str(), "Vector3D(1, 2, 3)") << "string should be (1, 2, 3)";
}


TEST(Vector2DTests, ValidConstruction)
{
    Math::Vector2D v(1, 2);

    EXPECT_EQ(v.x, 1) << "x should be 1";
    EXPECT_EQ(v.y, 2) << "y should be 2";
}

TEST(Vector2DTests, EmptyConstruction)
{
    Math::Vector2D v;

    EXPECT_EQ(v.x, 0) << "x should be 0";
    EXPECT_EQ(v.y, 0) << "y should be 0";
}

TEST(Vector2DTests, ValidCopyConstruction)
{
    Math::Vector2D v(1, 2);
    Math::Vector2D v2(v);

    EXPECT_EQ(v2.x, 1) << "x should be 1";
    EXPECT_EQ(v2.y, 2) << "y should be 2";
}

TEST(Vector2DTests, ValidCopyAssignment)
{
    Math::Vector2D v(1, 2);
    Math::Vector2D u(4, 5);
    u = v;

    EXPECT_EQ(u.x, 1) << "v2.x should be 1";
    EXPECT_EQ(u.y, 2) << "v2.y should be 2";
    EXPECT_EQ(v.x, 1) << "v.x should still be 1";
    EXPECT_EQ(v.y, 2) << "v.y should still be 2";
}

TEST(Vector2DTests, TwoVectorsAddition)
{
    Math::Vector2D u(1, 2);
    Math::Vector2D v(4, 5);
    Math::Vector2D w = u + v;

    EXPECT_EQ(w.x, 5) << "w.x should be 5";
    EXPECT_EQ(w.y, 7) << "w.y should be 7";
}

TEST(Vector2DTests, VectorAdditionOnThis)
{
    Math::Vector2D u(1, 2);
    Math::Vector2D v(4, 5);
    u += v;

    EXPECT_EQ(u.x, 5) << "u.x should be 5";
    EXPECT_EQ(u.y, 7) << "u.y should be 7";
}

TEST(Vector2DTests, TwoVectorsSubtraction)
{
    Math::Vector2D u(1, 2);
    Math::Vector2D v(4, 5);
    Math::Vector2D w = u - v;

    EXPECT_EQ(w.x, -3) << "w.x should be -3";
    EXPECT_EQ(w.y, -3) << "w.y should be -3";
}

TEST(Vector2DTests, VectorSubstractionOnThis)
{
    Math::Vector2D u(1, 2);
    Math::Vector2D v(4, 5);
    u -= v;

    EXPECT_EQ(u.x, -3) << "u.x should be -3";
    EXPECT_EQ(u.y, -3) << "u.y should be -3";
}

TEST(Vector2DTests, TwoVectorsMultiplication)
{
    Math::Vector2D u(1, 2);
    Math::Vector2D v(4, 5);
    Math::Vector2D w = u * v;

    EXPECT_EQ(w.x, 4) << "w.x should be 4";
    EXPECT_EQ(w.y, 10) << "w.y should be 10";
}

TEST(Vector2DTests, ScalarMultiplication)
{
    Math::Vector2D v(1, 2);
    Math::Vector2D w = v * 2;

    EXPECT_EQ(w.x, 2) << "w.x should be 2";
    EXPECT_EQ(w.y, 4) << "w.y should be 4";
}

TEST(Vector2DTests, VectorMultiplicationOnThis)
{
    Math::Vector2D u(1, 2);
    Math::Vector2D v(4, 5);
    u *= v;

    EXPECT_EQ(u.x, 4) << "u.x should be 4";
    EXPECT_EQ(u.y, 10) << "u.y should be 10";
}

TEST(Vector2DTests, ScalarMultiplicationOnThis)
{
    Math::Vector2D v(1, 2);
    v *= 2;

    EXPECT_EQ(v.x, 2) << "v.x should be 2";
    EXPECT_EQ(v.y, 4) << "v.y should be 4";
}

TEST(Vector2DTests, VectorDivisionBy2)
{
    Math::Vector2D v(4, 8);
    Math::Vector2D w = v / 2;

    EXPECT_EQ(w.x, 2) << "w.x should be 2";
    EXPECT_EQ(w.y, 4) << "w.y should be 4";
}

TEST(Vector2DTests, VectorDivisionBy0)
{
    Math::Vector2D v(4, 8);
    Math::Vector2D w = v / 0;

    EXPECT_EQ(w.x, 0) << "w.x should be 0";
    EXPECT_EQ(w.y, 0) << "w.y should be 0";
}

TEST(Vector2DTests, VectorDivisionOnThis)
{
    Math::Vector2D v(4, 8);
    v /= 2;

    EXPECT_EQ(v.x, 2) << "v.x should be 2";
    EXPECT_EQ(v.y, 4) << "v.y should be 4";
}

TEST(Vector2DTests, VectorDivisionBy0OnThis)
{
    Math::Vector2D v(4, 8);
    v /= 0;

    EXPECT_EQ(v.x, 4) << "v.x should be 4";
    EXPECT_EQ(v.y, 8) << "v.y should be 8";
}

TEST(Vector2DTests, LengthOfNullVector)
{
    Math::Vector2D v(0, 0);
    auto length = v.length();

    EXPECT_EQ(length, 0) << "length should be 0";
}

TEST(Vector2DTests, LengthOfPositiveVector)
{
    Math::Vector2D v(1, 2);
    auto length = v.length();

    EXPECT_FLOAT_EQ(length, 2.236068) << "length should be 2.236068";
}

TEST(Vector2DTests, LengthOfNegativeVector)
{
    Math::Vector2D v(-1, -2);
    auto length = v.length();

    EXPECT_FLOAT_EQ(length, 2.236068) << "length should be 2.236068";
}

TEST(Vector3DTests, NormalizeVector)
{
    Math::Vector3D v(1, 2, 3);
    Math::Vector3D w = v.normalize();

    EXPECT_FLOAT_EQ(w.x, 0.26726124f) << "x should be 0.26726124";
    EXPECT_FLOAT_EQ(w.y, 0.53452247f) << "y should be 0.53452247";
    EXPECT_FLOAT_EQ(w.z, 0.8017837f) << "z should be 0.8017837";
}
