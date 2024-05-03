/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#pragma once

#include <memory>
#include <cstddef>

#include "types/graphics/Pixel.hpp"
#include "types/math/Point.hpp"

using namespace std;

namespace Raytracer::Core::Rendering {
    class Screen {
    public:
        typedef struct Size {
            /// @brief Width of the screen
            size_t width;
            /// @brief Height of the screen
            size_t height;
        } Size;

        typedef struct Config {
            /// @brief Size of the screen
            Size size;
            /// @brief Origin of the screen
            Common::Math::Point3D origin;
        } Config;

        /**
         * @brief Construct a new Screen object
         * @param size Size of the screen
         */
        explicit Screen(const Config &config);
        /// @brief Default destructor of the screen
        ~Screen() = default;

        /// @brief Width of the screen
        const Size size;

        /// @brief Origin of the screen
        const Common::Math::Point3D origin;

        /// @brief Get the pixel at the given coordinates
        Common::Graphics::Pixel &operator()(size_t x, size_t y);

    private:
        /// @brief Pixels of the screen
        unique_ptr<Common::Graphics::Pixel[]> _pixels;
    };
}
