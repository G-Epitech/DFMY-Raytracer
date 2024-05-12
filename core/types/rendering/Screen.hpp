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
#include "types/graphics/PixelArray.hpp"
#include "types/math/Size.hpp"

using namespace std;

namespace Raytracer::Core::Rendering {
    class Screen {
    public:
        /// @brief Configuration of the screen
        typedef struct Config {
            /// @brief Size of the screen
            Common::Math::Size size;
        } Config;

        /**
         * @brief Construct a new Screen object
         * @param size Size of the screen
         */
        explicit Screen(const Config &config);

        /**
         * @brief Default constructor of the screen
         */
        ~Screen();

        /// @brief Width of the screen
        Common::Math::Size size;

        /// @brief Get the pixel at the given coordinates
        void setPixel(size_t x, size_t y, const Common::Graphics::Pixel &pixel);

        /**
         * @brief Get the pixels of the screen
         * @return PixelArray of the screen
         */
        Graphics::PixelArray &getPixels();

        /**
         * @brief Resize the screen
         * @param size New size of the screen
         */
        void resize(const Common::Math::Size &size);

        /**
         * @brief Clear the screen
         */
        void clear();

    private:
        /// @brief Pixels of the screen
        Graphics::PixelArray _pixels;
    };
}
