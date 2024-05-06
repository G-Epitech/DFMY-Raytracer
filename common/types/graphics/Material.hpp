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

        /**
         * @brief Construct a new Material object
         * @param color Color of the material
         * @param emissionColor Emission color of the material
         * @param specularColor Specular color of the material
         * @param emissionStrength Emission strength of the material
         */
        explicit Material(
            const Color &color,
            const Color &emissionColor,
            const Color &specularColor,
            float emissionStrength
        );

        /**
         * @brief Construct a new Material object
         * @param material Material to copy
         */
        Material(const Material &material) = default;

        /**
         * @brief Destroy the Material object
         */
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