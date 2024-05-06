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
        .size = {6, 6},
        .origin = Math::Point3D(0, 34, 6)
    };
    Rendering::Screen screen(config);
    auto pos = static_cast<ptrdiff_t>(3 * 6 * 4);
    auto &pixels = screen.getPixels();

    screen.setPixel(0, 3, { 255, 255, 255, 255 });
    ASSERT_EQ(pixels[pos], 255);
    ASSERT_EQ(pixels[pos + 1], 255);
    ASSERT_EQ(pixels[pos + 2], 255);
    ASSERT_EQ(pixels[pos + 3], 255);
}
