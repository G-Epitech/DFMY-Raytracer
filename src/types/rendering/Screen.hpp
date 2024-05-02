/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#pragma once

#include <cstddef>

#include "types/graphics/Pixel.hpp"

using namespace std;
using namespace Graphics;

namespace Rendering {
    class Screen {
    public:
        /**
         * @brief Construct a new Screen object
         * @param width Width of the screen
         * @param height Height of the screen
         */
        Screen(size_t width, size_t height);
        /// @brief Default destructor of the screen
        ~Screen() = default;

        /// @brief Width of the screen
        const size_t width;
        /// @brief Height of the screen
        const size_t height;

        /// @brief Get the pixel at the given coordinates
        Pixel &operator()(size_t x, size_t y);

    private:
        /// @brief Pixels of the screen
        unique_ptr<Pixel[]> _pixels;
    };
}
