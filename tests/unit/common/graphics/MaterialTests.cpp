/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** MaterialTests.cpp
*/

#include <gtest/gtest.h>

#include "types/graphics/Material.hpp"

using namespace Raytracer::Common;

TEST(MaterialTests, ValidConstruction)
{
    Graphics::Color materialColor = Graphics::Color(255, 0, 0);
    Graphics::Color emissionColor = Graphics::Color(0, 255, 0);
    float emissionStrength = 0.5;
    float reflectivity = 0.5;


    Graphics::Material material(
        materialColor,
        emissionColor,
        emissionStrength,
        reflectivity,
        {}
    );

    EXPECT_EQ(material.color, materialColor) << "Color should be materialColor";
    EXPECT_EQ(material.emissionColor, emissionColor) << "Emission color should be emissionColor";
    EXPECT_EQ(material.emissionStrength, emissionStrength) << "Emission strength should be emissionStrength";
}

TEST(MaterialTests, ValidCopyConstruction)
{
    Graphics::Color materialColor = Graphics::Color(255, 0, 0);
    Graphics::Color emissionColor = Graphics::Color(0, 255, 0);
    float emissionStrength = 0.5;
    float reflectivity = 0.5;

    Graphics::Material material(
        materialColor,
        emissionColor,
        emissionStrength,
        reflectivity,
        {}
    );

    Graphics::Material material2(material);

    EXPECT_EQ(material2.color, materialColor) << "Color should be materialColor";
    EXPECT_EQ(material2.emissionColor, emissionColor) << "Emission color should be emissionColor";
    EXPECT_EQ(material2.emissionStrength, emissionStrength) << "Emission strength should be emissionStrength";
}

TEST(MaterialTests, ValidCopyAssignment)
{
    Graphics::Color materialColor = Graphics::Color(255, 0, 0);
    Graphics::Color emissionColor = Graphics::Color(0, 255, 0);
    float emissionStrength = 0.5;
    float reflectivity = 0.5;

    Graphics::Material material(
        materialColor,
        emissionColor,
        emissionStrength,
        reflectivity,
        {}
    );
    Graphics::Material material2 = material;

    EXPECT_EQ(material2.color, materialColor) << "Color should be materialColor";
    EXPECT_EQ(material2.emissionColor, emissionColor) << "Emission color should be emissionColor";
    EXPECT_EQ(material2.emissionStrength, emissionStrength) << "Emission strength should be emissionStrength";
    EXPECT_EQ(material.color, materialColor) << "Color should still be materialColor";
    EXPECT_EQ(material.emissionColor, emissionColor) << "Emission color should still be emissionColor";
    EXPECT_EQ(material.emissionStrength, emissionStrength) << "Emission strength should still be emissionStrength";
}
