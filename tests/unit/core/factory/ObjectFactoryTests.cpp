/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactoryTests.cpp
*/

#include <gtest/gtest.h>

#include "factory/ObjectFactory.hpp"

using namespace Raytracer::Core;

TEST(ObjectFactoryTests, AppRunWithBadOptions)
{
    PluginsManager pluginsManager;
    ObjectFactory objectFactory(pluginsManager);

    pluginsManager.load("./plugins");
    ASSERT_THROW(objectFactory.create(
        "invalidName",
        "invalid", nullptr,
        Math::Vector3D(),
        Math::Point3D(),
        ObjectProperty()
    ), ObjectFactory::Exception);
}

TEST(ObjectFactoryTests, GetErrorMessageOfException)
{
    ObjectFactory::Exception exception("Error message");

    ASSERT_STREQ(exception.what(), "Error message");
}

TEST(ObjectFactoryTests, CreateObject)
{
    PluginsManager pluginsManager;
    ObjectFactory objectFactory(pluginsManager);

    pluginsManager.load("./plugins");
    ASSERT_NO_THROW(objectFactory.create(
        "sphereName",
        "sphere", nullptr,
        Math::Vector3D(),
        Math::Point3D(),
        ObjectProperty()
    ));
}