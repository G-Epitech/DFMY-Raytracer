/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Float.hpp
*/

#pragma once

namespace Raytracer::Common::Math {
    /// @brief Representing 2D coordinates
    class Float2 {
    public:
        /// @brief x coordinate
        float x;

        /// @brief y coordinate
        float y;

        /**
         * @brief Construct a new Float2 object
         * @param x X coordinate
         * @param y Y coordinate
         */
        explicit Float2(float x = 0, float y = 0);

        /**
         * @brief Destroy the Float 2 object
         */
        ~Float2() = default;
    };

    /// @brief Representing 3D coordinates
    class Float3: public Float2 {
    public:
        /// @brief z coordinate
        float z;

        /**
         * @brief Construct a new Float3 object
         * @param x X coordinate
         * @param y Y coordinate
         * @param z Z coordinate
         */
        explicit Float3(float x = 0, float y = 0, float z = 0);

        /**
         * @brief Destroy the Float 3 object
         */
        ~Float3() = default;
    };
}
