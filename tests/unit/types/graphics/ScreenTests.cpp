/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/graphics/Screen.hpp"

TEST(ScreenTests, Create4x4Screen)
{
    Graphics::Screen<4, 4> screen;


    ASSERT_EQ(screen.width, 4);
    ASSERT_EQ(screen.height, 4);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ASSERT_EQ(screen(i, j).r, 0);
            ASSERT_EQ(screen(i, j).g, 0);
            ASSERT_EQ(screen(i, j).b, 0);
            ASSERT_EQ(screen(i, j).a, 0);
        }
    }
}

TEST(ScreenTests, UpdateAPixel)
{
    Graphics::Screen<4, 4> screen;

    screen(0, 3) = { 255, 255, 255, 255 };

    ASSERT_EQ(screen(0, 3).r, 255);
    ASSERT_EQ(screen(0, 3).g, 255);
    ASSERT_EQ(screen(0, 3).b, 255);
    ASSERT_EQ(screen(0, 3).a, 255);
}