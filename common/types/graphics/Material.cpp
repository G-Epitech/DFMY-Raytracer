/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material.cpp
*/

#include "Material.hpp"

using namespace Raytracer::Common;

Graphics::Material::Material(
    const Color &color,
    const Color &emissionColor,
    float emissionStrength,
    float reflectivity,
    std::vector<Emission> emissions
) {
    this->color = color;
    this->emissionColor = emissionColor;
    this->emissionStrength = emissionStrength;
    this->reflectivity = reflectivity;
    this->emissions = emissions;
}
