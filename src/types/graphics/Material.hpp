/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material.hpp
*/

#pragma once

#include "Color.hpp"

namespace Graphics {
    class Material {
    public:
        /// @brief Create a new material
        Material(
            const Color &color,
            const Color &emissionColor,
            const Color &specularColor,
            float emissionStrength
        );
        /// @brief Default destructor
        ~Material() = default;

        /// @brief Color of the material
        Color color;
        /// @brief Emission color of the material
        Color emissionColor;
        /// @brief Specular color of the material
        Color specularColor;
        /// @brief Emission strength of the material
        float emissionStrength;
    };
}