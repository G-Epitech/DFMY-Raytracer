/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Material.hpp
*/

#pragma once

#include <memory>
#include <vector>
#include "Color.hpp"
#include "types/math/Vector.hpp"

namespace Raytracer::Common::Graphics {
    class Material {
    public:
        /// @brief Shared pointer to a material
        typedef std::shared_ptr<Material> Ptr;

        /// @brief Emission struct for the material
        typedef struct {
            /// @brief Light emission color
            Color color;
            /// @brief Light emission strength
            float strength;
            /// @brief Light emission direction
            Math::Vector3D direction;
        } Emission;

        /**
         * @brief Construct a new Material object
         * @param color Color of the material
         * @param emissionColor General emission color of the material
         * @param emissionStrength General emissions strength
         * @param reflectivity Reflectivity of the material
         * @param emissions Emissions vector of the material
         */
        explicit Material(
            const Color &color,
            const Color &emissionColor,
            float emissionStrength,
            float reflectivity,
            std::vector<Emission> emissions
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

        /// @brief Reflectivity of the material
        float reflectivity;

        /// @brief Emissions vector of the material
        std::vector<Emission> emissions;

    };  
}