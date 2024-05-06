/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>

#include "types/rendering/Screen.hpp"
#include "types/rendering/Camera.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

TEST(CameraTests, CreateSimpleCamera) {
    Rendering::Screen::Config screen = {
        .size = {4, 8},
    };
    Rendering::Camera::Config config = {
        .name = "Camera 1",
        .screen = screen,
        .position = Math::Point3D(-1, 0,-1),
        .direction = Math::Vector3D(0, 12, 8),
        .fov = 90
    };
    Rendering::Camera camera(config);

    ASSERT_EQ(camera.screen.size.width, 4);
    ASSERT_EQ(camera.screen.size.height, 8);
    ASSERT_EQ(camera.position.x, -1);
    ASSERT_EQ(camera.position.y, 0);
    ASSERT_EQ(camera.position.z, -1);
    ASSERT_EQ(camera.direction.x, 0);
    ASSERT_EQ(camera.direction.y, 12);
    ASSERT_EQ(camera.direction.z, 8);
    ASSERT_EQ(camera.fov, 90);
    ASSERT_EQ(camera.name, "Camera 1");
}
