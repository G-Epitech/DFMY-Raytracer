/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/graphics/Color.hpp"

using namespace Raytracer::Common;

TEST(ColorTests, EmptyConstruction)
{
    Graphics::Color color;

    EXPECT_FLOAT_EQ(color.r, 0) << "r should be 0";
    EXPECT_FLOAT_EQ(color.g, 0) << "g should be 0";
    EXPECT_FLOAT_EQ(color.b, 0) << "b should be 0";
    EXPECT_FLOAT_EQ(color.a, 1) << "a should be 1";
}

TEST(ColorTests, ConstructionWithoutAlpha)
{
    Graphics::Color color(1, 1, 1);

    EXPECT_FLOAT_EQ(color.r, 1) << "r should be 255";
    EXPECT_FLOAT_EQ(color.g, 1) << "g should be 255";
    EXPECT_FLOAT_EQ(color.b, 1) << "b should be 255";
    EXPECT_FLOAT_EQ(color.a, 1) << "a should be 255";
}

TEST(ColorTests, CopyConstructionWhitoutAlpha)
{
    Graphics::Color color(0.2f, 0.3f, 0.4f);
    Graphics::Color color2(color);

    EXPECT_FLOAT_EQ(color2.r, 0.2f) << "r should be 34";
    EXPECT_FLOAT_EQ(color2.g, 0.3f) << "g should be 89";
    EXPECT_FLOAT_EQ(color2.b, 0.4f) << "b should be 255";
    EXPECT_FLOAT_EQ(color2.a, 1) << "a should be 255";
}

TEST(ColorTests, ConstructionWithAlpha)
{
    Graphics::Color color(0.2, 0.3, 0.4, 0.5);

    EXPECT_FLOAT_EQ(color.r, 0.2) << "r should be 0.2";
    EXPECT_FLOAT_EQ(color.g, 0.3) << "g should be 0.3";
    EXPECT_FLOAT_EQ(color.b, 0.4) << "b should be 0.4";
    EXPECT_FLOAT_EQ(color.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, CopyConstructionWithAlpha)
{
    Graphics::Color color(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(color);

    EXPECT_FLOAT_EQ(color2.r, 0.2) << "r should be 0.2";
    EXPECT_FLOAT_EQ(color2.g, 0.3) << "g should be 0.3";
    EXPECT_FLOAT_EQ(color2.b, 0.4) << "b should be 0.4";
    EXPECT_FLOAT_EQ(color2.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, Assignment)
{
    Graphics::Color color(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(0, 0, 0, 0);

    color2 = color;
    EXPECT_FLOAT_EQ(color2.r, 0.2) << "r should be 0.2";
    EXPECT_FLOAT_EQ(color2.g, 0.3) << "g should be 0.3";
    EXPECT_FLOAT_EQ(color2.b, 0.4) << "b should be 0.4";
    EXPECT_FLOAT_EQ(color2.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, AssignmentWithUpdate)
{
    Graphics::Color color(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(0, 0, 0, 0);

    color2 = color;
    EXPECT_FLOAT_EQ(color2.r, 0.2) << "r should be 0.2";
    EXPECT_FLOAT_EQ(color2.g, 0.3) << "g should be 0.3";
    EXPECT_FLOAT_EQ(color2.b, 0.4) << "b should be 0.4";
    EXPECT_FLOAT_EQ(color2.a, 0.5) << "a should be 0.5";
    color2.r = 1;
    color2.g = 1;
    color2.b = 1;
    color2.a = 1;
    EXPECT_FLOAT_EQ(color.r, 0.2) << "r should be 0.2";
    EXPECT_FLOAT_EQ(color.g, 0.3) << "g should be 0.3";
    EXPECT_FLOAT_EQ(color.b, 0.4) << "b should be 0.4";
    EXPECT_FLOAT_EQ(color.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, Equality)
{
    Graphics::Color red(1, 0, 0);
    Graphics::Color green(0, 1, 0);
    Graphics::Color blue(0, 0, 1);

    EXPECT_TRUE(red == red) << "red should be equal to red";
    EXPECT_TRUE(green == green) << "green should be equal to green";
    EXPECT_TRUE(blue == blue) << "blue should be equal to blue";
    EXPECT_FALSE(red == green) << "red should not be equal to green";
    EXPECT_FALSE(red == blue) << "red should not be equal to blue";
    EXPECT_FALSE(green == blue) << "green should not be equal to blue";
}

TEST(ColorTests, PartialEquality)
{
    Graphics::Color color1(1, 1, 1, 1);
    Graphics::Color color2(1, 1, 1, 0);
    Graphics::Color color3(1, 1, 0, 0);
    Graphics::Color color4(1, 0, 0, 0);
    Graphics::Color color5(0, 0, 0, 0);

    EXPECT_FALSE(color1 == color2) << "color1 should not be equal to color2";
    EXPECT_FALSE(color1 == color3) << "color1 should not be equal to color3";
    EXPECT_FALSE(color1 == color4) << "color1 should not be equal to color4";
    EXPECT_FALSE(color1 == color5) << "color1 should not be equal to color5";
}

TEST(ColorTests, Inequality)
{
    Graphics::Color red(1, 0, 0);
    Graphics::Color green(0, 1, 0);
    Graphics::Color blue(0, 0, 1);

    EXPECT_FALSE(red != red) << "red should not be different from red";
    EXPECT_FALSE(green != green) << "green should not be different from green";
    EXPECT_FALSE(blue != blue) << "blue should not be different from blue";
    EXPECT_TRUE(red != green) << "red should be different from green";
    EXPECT_TRUE(red != blue) << "red should be different from blue";
    EXPECT_TRUE(green != blue) << "green should be different from blue";
}

TEST(ColorTests, ExportColorToSimplePixel)
{
    Graphics::Color color(1, 1, 1, 1);
    auto pixel = color.toPixel();

    EXPECT_EQ(pixel.r, 255) << "r should be 255";
    EXPECT_EQ(pixel.g, 255) << "g should be 255";
    EXPECT_EQ(pixel.b, 255) << "b should be 255";
    EXPECT_EQ(pixel.a, 255) << "a should be 255";
}

TEST(ColorTests, MultiplyColorByScalar)
{
    Graphics::Color color(0.2, 0.3, 0.4, 0.5);
    Graphics::Color result = color * 2;

    EXPECT_FLOAT_EQ(result.r, 0.4) << "r should be 0.4";
    EXPECT_FLOAT_EQ(result.g, 0.6) << "g should be 0.6";
    EXPECT_FLOAT_EQ(result.b, 0.8) << "b should be 0.8";
    EXPECT_FLOAT_EQ(result.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, Multiply2Colors)
{
    Graphics::Color color1(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(0.1, 0.2, 0.3, 0.4);
    Graphics::Color result = color1 * color2;

    EXPECT_FLOAT_EQ(result.r, 0.02) << "r should be 0.02";
    EXPECT_FLOAT_EQ(result.g, 0.06) << "g should be 0.06";
    EXPECT_FLOAT_EQ(result.b, 0.12) << "b should be 0.12";
    EXPECT_FLOAT_EQ(result.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, MultiplyAndAssign2Colors)
{
    Graphics::Color color1(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(0.1, 0.2, 0.3, 0.4);

    color1 *= color2;
    EXPECT_FLOAT_EQ(color1.r, 0.02) << "r should be 0.02";
    EXPECT_FLOAT_EQ(color1.g, 0.06) << "g should be 0.06";
    EXPECT_FLOAT_EQ(color1.b, 0.12) << "b should be 0.12";
    EXPECT_FLOAT_EQ(color1.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, Add2Colors)
{
    Graphics::Color color1(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(0.1, 0.2, 0.3, 0.4);
    Graphics::Color result = color1 + color2;

    EXPECT_FLOAT_EQ(result.r, 0.3) << "r should be 0.3";
    EXPECT_FLOAT_EQ(result.g, 0.5) << "g should be 0.5";
    EXPECT_FLOAT_EQ(result.b, 0.7) << "b should be 0.7";
    EXPECT_FLOAT_EQ(result.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, AddAndAssign2Colors)
{
    Graphics::Color color1(0.2, 0.3, 0.4, 0.5);
    Graphics::Color color2(0.1, 0.2, 0.3, 0.4);

    color1 += color2;
    EXPECT_FLOAT_EQ(color1.r, 0.3) << "r should be 0.3";
    EXPECT_FLOAT_EQ(color1.g, 0.5) << "g should be 0.5";
    EXPECT_FLOAT_EQ(color1.b, 0.7) << "b should be 0.7";
    EXPECT_FLOAT_EQ(color1.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, BuildColorFromRGBValues)
{
    Graphics::Color color = Graphics::Color::fromRGB(255, 0, 0);

    EXPECT_FLOAT_EQ(color.r, 1) << "r should be 1";
    EXPECT_FLOAT_EQ(color.g, 0) << "g should be 0";
    EXPECT_FLOAT_EQ(color.b, 0) << "b should be 0";
    EXPECT_FLOAT_EQ(color.a, 1) << "a should be 1";
}

TEST(ColorTests, DivideColorByScalar)
{
    Graphics::Color color(0.2, 0.3, 0.4, 0.5);
    Graphics::Color result = color / 2;

    EXPECT_FLOAT_EQ(result.r, 0.1) << "r should be 0.1";
    EXPECT_FLOAT_EQ(result.g, 0.15) << "g should be 0.15";
    EXPECT_FLOAT_EQ(result.b, 0.2) << "b should be 0.2";
    EXPECT_FLOAT_EQ(result.a, 0.5) << "a should be 0.5";
}

TEST(ColorTests, NormalizeColorUnderLimit)
{
    Graphics::Color color(-0.2, -0.3, -0.4, -0.5);
    color.normalize();

    EXPECT_FLOAT_EQ(color.r, 0) << "r should be 0";
    EXPECT_FLOAT_EQ(color.g, 0) << "g should be 0";
    EXPECT_FLOAT_EQ(color.b, 0) << "b should be 0";
    EXPECT_FLOAT_EQ(color.a, 0) << "a should be 0";
}

TEST(ColorTests, NormalizeColorAboveLimit)
{
    Graphics::Color color(1.2, 1.3, 1.4, 1.5);
    color.normalize();

    EXPECT_FLOAT_EQ(color.r, 1) << "r should be 1";
    EXPECT_FLOAT_EQ(color.g, 1) << "g should be 1";
    EXPECT_FLOAT_EQ(color.b, 1) << "b should be 1";
    EXPECT_FLOAT_EQ(color.a, 1) << "a should be 1";
}
