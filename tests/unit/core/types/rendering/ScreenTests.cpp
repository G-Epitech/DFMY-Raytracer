/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/rendering/Screen.hpp"

using namespace Raytracer::Core;

TEST(ScreenTests, Create4x4Screen)
{
    Rendering::Screen screen({4, 4});

    ASSERT_EQ(screen.size.width, 4);
    ASSERT_EQ(screen.size.height, 4);
}

TEST(ScreenTests, UpdateAPixel)
{
    Rendering::Screen screen({4, 4});

    screen(0, 3) = { 255, 255, 255, 255 };

    ASSERT_EQ(screen(0, 3).r, 255);
    ASSERT_EQ(screen(0, 3).g, 255);
    ASSERT_EQ(screen(0, 3).b, 255);
    ASSERT_EQ(screen(0, 3).a, 255);
}
