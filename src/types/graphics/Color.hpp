/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color.hpp
*/

#pragma once

namespace Graphics {
    /// @brief Represent an RGBA color
    typedef struct Color {
        /// @brief Create a color with the given values
        Color(float r, float g, float b, float a = 255.0f);
        /// @brief Create a new color, black by default
        Color();
        /// @brief Create a new color from another color
        Color(const Color &color) = default;
        /// @brief Redefine the color from another color
        Color &operator=(const Color &color) = default;
        /// @brief Compare two colors
        bool operator==(const Color &color) const;
        /// @brief Compare two colors
        bool operator!=(const Color &color) const;
        /// @brief Red component of the color
        float r;
        /// @brief Green component of the color
        float g;
        /// @brief Blue component of the color
        float b;
        /// @brief Alpha component of the color
        float a;
    } Color;
}
