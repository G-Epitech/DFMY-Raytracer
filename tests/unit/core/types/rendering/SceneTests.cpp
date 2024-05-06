/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SceneTests.cpp
*/

#include <gtest/gtest.h>

#include "types/rendering/Scene.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

TEST(SceneTests, CreateSimpleScene) {
    Rendering::Scene scene("Scene 1");

    ASSERT_EQ(scene.name, "Scene 1");
    ASSERT_TRUE(scene.objects.empty());
    ASSERT_TRUE(scene.cameras.empty());
    ASSERT_TRUE(scene.materials.empty());
}
