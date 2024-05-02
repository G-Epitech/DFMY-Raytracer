/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#pragma once

#include <cstddef>
#include <array>

#include "Pixel.hpp"

using namespace std;

namespace Graphics {
    template<size_t Width, size_t Height>
    class Screen {
    public:
        Screen() = default;
        ~Screen() = default;

        /// @brief Width of the screen
        const size_t width = Width;
        /// @brief Height of the screen
        const size_t height = Height;

        /// @brief Get the pixel at the given coordinates
        Pixel &operator()(size_t x, size_t y) {
            return _pixels[y][x];
        }

    private:
        /// @brief Pixels of the screen
        array<array<Pixel, Width>, Height> _pixels;
    };
}
