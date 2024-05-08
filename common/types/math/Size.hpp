/*
** EPITECH PROJECT, 2024
** Size.hpp
** File description:
** Size class
*/

#pragma once

#include <numbers>

namespace Raytracer::Common::Math {
    /// @brief Size of the screen
    typedef struct Size {
        /// @brief Width of the screen
        size_t width;
        /// @brief Height of the screen
        size_t height;
    } Size;
}
