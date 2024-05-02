/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Float.hpp
*/

#pragma once

namespace Math {
    /// @brief Representing 3D coordinates
    class Float3 {
    public:
        /// @brief x coordinate
        float x;

        /// @brief y coordinate
        float y;

        /// @brief z coordinate
        float z;

    protected:
        /// @brief Create a new Float3
        explicit Float3(float x = 0, float y = 0, float z = 0);

        /// Default destructor
        ~Float3() = default;
    };
}
