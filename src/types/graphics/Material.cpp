/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material.cpp
*/

#include "Material.hpp"

using namespace Graphics;

Material::Material(
    const Color &color,
    const Color &emissionColor,
    const Color &specularColor,
    float emissionStrength
) {
    this->color = color;
    this->emissionColor = emissionColor;
    this->specularColor = specularColor;
    this->emissionStrength = emissionStrength;
}
