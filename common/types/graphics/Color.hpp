/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color.hpp
*/

#pragma once

#include "Pixel.hpp"
#include "types/math/Float.hpp"

namespace Raytracer::Common::Graphics {
    /// @brief Represent an RGBA color
    typedef struct Color {
        /// @brief Create a color with the given values
        Color(float r, float g, float b, float a = 1.0f);

        static Color fromRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);

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

        /// @brief Multiply the color by a scalar
        Color operator*(float scalar) const;

        /// @brief Multiply the color by another color
        Color operator*(Color &other) const;

        /// @brief Multiply this color by another color
        Color &operator*=(Color &other);

        /// @brief Add two colors
        Color operator+(Color &other) const;

        /// @brief Add color to this color
        Color &operator+=(Color &other);

        /// @brief Divide the color by a scalar
        Color operator/(float scalar) const;

        /// @brief Convert the color to a pixel
        [[nodiscard]] Pixel toPixel() const;

        /// @brief Normalize the color
        void normalize();

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
