/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/rendering/Screen.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

TEST(ScreenTests, Create4x4Screen)
{
    Rendering::Screen::Config config = {
        .size = {4, 4},
        .origin = Math::Point3D(0, 34, 6)
    };
    Rendering::Screen screen(config);

    ASSERT_EQ(screen.size.width, 4);
    ASSERT_EQ(screen.size.height, 4);
    ASSERT_EQ(screen.origin.x, 0);
    ASSERT_EQ(screen.origin.y, 34);
    ASSERT_EQ(screen.origin.z, 6);
}

TEST(ScreenTests, UpdateAPixel)
{
    Rendering::Screen::Config config = {
        .size = {4, 4},
        .origin = Math::Point3D(0, 34, 6)
    };
    Rendering::Screen screen(config);

    screen(0, 3) = { 255, 255, 255, 255 };
    ASSERT_EQ(screen(0, 3).r, 255);
    ASSERT_EQ(screen(0, 3).g, 255);
    ASSERT_EQ(screen(0, 3).b, 255);
    ASSERT_EQ(screen(0, 3).a, 255);
}
