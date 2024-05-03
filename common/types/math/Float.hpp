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

        /// @brief Create a new Float3
        explicit Float2(float x = 0, float y = 0);

        /// Default destructor
        ~Float2() = default;
    };

    /// @brief Representing 3D coordinates
    class Float3: public Float2 {
    public:
        /// @brief z coordinate
        float z;

        /// @brief Create a new Float3
        explicit Float3(float x = 0, float y = 0, float z = 0);

        /// Default destructor
        ~Float3() = default;
    };
}
