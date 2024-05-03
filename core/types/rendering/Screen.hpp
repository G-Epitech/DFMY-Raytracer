/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#pragma once

#include <memory>
#include <cstddef>
#include <SFML/Graphics.hpp>

#include "types/graphics/Pixel.hpp"
#include "types/math/Point.hpp"

using namespace std;

namespace Raytracer::Core::Rendering {
    class Screen {
    public:
        /// @brief Pixel array of the screen
        typedef std::unique_ptr<sf::Uint8[]> PixelArray;

        /// @brief Size of the screen
        typedef struct Size {
            /// @brief Width of the screen
            size_t width;
            /// @brief Height of the screen
            size_t height;
        } Size;

        /// @brief Configuration of the screen
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
        void setPixel(size_t x, size_t y, const Common::Graphics::Pixel &pixel);

        /**
         * @brief Get the pixels of the screen
         * @return PixelArray of the screen
         */
        PixelArray &getPixels();

    private:
        /// @brief Pixels of the screen
        PixelArray _pixels;
    };
}
