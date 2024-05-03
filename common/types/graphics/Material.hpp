/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material.hpp
*/

#pragma once

#include <memory>
#include "Color.hpp"

namespace Raytracer::Common::Graphics {
    class Material {
    public:
        /// @brief Shared pointer to a material
        typedef std::shared_ptr<Material> Ptr;

        /// @brief Create a new material
        explicit Material(
            const Color &color,
            const Color &emissionColor,
            const Color &specularColor,
            float emissionStrength
        );

        /// @brief Default copy constructor
        Material(const Material &material) = default;

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