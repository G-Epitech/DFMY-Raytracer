/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/graphics/Color.hpp"

TEST(ColorTests, EmptyConstruction)
{
    Graphics::Color color;

    EXPECT_EQ(color.r, 0) << "r should be 0";
    EXPECT_EQ(color.g, 0) << "g should be 0";
    EXPECT_EQ(color.b, 0) << "b should be 0";
    EXPECT_EQ(color.a, 255) << "a should be 255";
}

TEST(ColorTests, ConstructionWithoutAlpha)
{
    Graphics::Color color(255, 255, 255);

    EXPECT_EQ(color.r, 255) << "r should be 255";
    EXPECT_EQ(color.g, 255) << "g should be 255";
    EXPECT_EQ(color.b, 255) << "b should be 255";
    EXPECT_EQ(color.a, 255) << "a should be 255";
}

TEST(ColorTests, CopyConstructionWhitoutAlpha)
{
    Graphics::Color color(34, 89, 255);
    Graphics::Color color2(color);

    EXPECT_EQ(color2.r, 34) << "r should be 34";
    EXPECT_EQ(color2.g, 89) << "g should be 89";
    EXPECT_EQ(color2.b, 255) << "b should be 255";
    EXPECT_EQ(color2.a, 255) << "a should be 255";
}

TEST(ColorTests, ConstructionWithAlpha)
{
    Graphics::Color color(12, 34, 98, 230);

    EXPECT_EQ(color.r, 12) << "r should be 12";
    EXPECT_EQ(color.g, 34) << "g should be 34";
    EXPECT_EQ(color.b, 98) << "b should be 98";
    EXPECT_EQ(color.a, 230) << "a should be 230";
}

TEST(ColorTests, CopyConstructionWithAlpha)
{
    Graphics::Color color(12, 34, 98, 230);
    Graphics::Color color2(color);

    EXPECT_EQ(color2.r, 12) << "r should be 12";
    EXPECT_EQ(color2.g, 34) << "g should be 34";
    EXPECT_EQ(color2.b, 98) << "b should be 98";
    EXPECT_EQ(color2.a, 230) << "a should be 230";
}

TEST(ColorTests, Assignment)
{
    Graphics::Color color(12, 34, 98, 230);
    Graphics::Color color2(0, 0, 0, 0);

    color2 = color;
    EXPECT_EQ(color2.r, 12) << "r should be 12";
    EXPECT_EQ(color2.g, 34) << "g should be 34";
    EXPECT_EQ(color2.b, 98) << "b should be 98";
    EXPECT_EQ(color2.a, 230) << "a should be 230";
}

TEST(ColorTests, AssignmentWithUpdate)
{
    Graphics::Color color(12, 34, 98, 230);
    Graphics::Color color2(0, 0, 0, 0);

    color2 = color;
    EXPECT_EQ(color2.r, 12) << "r should be 12";
    EXPECT_EQ(color2.g, 34) << "g should be 34";
    EXPECT_EQ(color2.b, 98) << "b should be 98";
    EXPECT_EQ(color2.a, 230) << "a should be 230";
    color2.r = 1;
    color2.g = 2;
    color2.b = 3;
    color2.a = 4;
    EXPECT_EQ(color.r, 12) << "r should still be 12";
    EXPECT_EQ(color.g, 34) << "g should still be 34";
    EXPECT_EQ(color.b, 98) << "b should still be 98";
    EXPECT_EQ(color.a, 230) << "a should still be 230";
}

TEST(ColorTests, Equality)
{
    Graphics::Color red(255, 0, 0);
    Graphics::Color green(0, 255, 0);
    Graphics::Color blue(0, 0, 255);

    EXPECT_TRUE(red == red) << "red should be equal to red";
    EXPECT_TRUE(green == green) << "green should be equal to green";
    EXPECT_TRUE(blue == blue) << "blue should be equal to blue";
    EXPECT_FALSE(red == green) << "red should not be equal to green";
    EXPECT_FALSE(red == blue) << "red should not be equal to blue";
    EXPECT_FALSE(green == blue) << "green should not be equal to blue";
}

TEST(ColorTests, PartialEquality)
{
    Graphics::Color color1(255, 255, 255, 255);
    Graphics::Color color2(255, 255, 255, 0);
    Graphics::Color color3(255, 255, 0, 0);
    Graphics::Color color4(255, 0, 0, 0);
    Graphics::Color color5(0, 0, 0, 0);

    EXPECT_FALSE(color1 == color2) << "color1 should not be equal to color2";
    EXPECT_FALSE(color1 == color3) << "color1 should not be equal to color3";
    EXPECT_FALSE(color1 == color4) << "color1 should not be equal to color4";
    EXPECT_FALSE(color1 == color5) << "color1 should not be equal to color5";
}

TEST(ColorTests, Inequality)
{
    Graphics::Color red(255, 0, 0);
    Graphics::Color green(0, 255, 0);
    Graphics::Color blue(0, 0, 255);

    EXPECT_FALSE(red != red) << "red should not be different from red";
    EXPECT_FALSE(green != green) << "green should not be different from green";
    EXPECT_FALSE(blue != blue) << "blue should not be different from blue";
    EXPECT_TRUE(red != green) << "red should be different from green";
    EXPECT_TRUE(red != blue) << "red should be different from blue";
    EXPECT_TRUE(green != blue) << "green should be different from blue";
}
