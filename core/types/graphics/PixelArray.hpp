/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PixelArray.hpp
*/

#pragma once

#include <SFML/Config.hpp>
#include <memory>

namespace Raytracer::Core::Graphics {
    class PixelArray {
    public:
        /**
         * @brief Construct a new Pixel Array object
         * @param size Size of the pixel array
         */
        explicit PixelArray(size_t size);

        /**
         * @brief Destroy the Pixel Array object
         */
        ~PixelArray() = default;

        /**
         * @brief Get the origin of the pixel array
         * @return Pointer to the pixel array
         */
        sf::Uint8 *operator*() const;

        /**
         * @brief Get the pixel at the given index
         * @param index Index of the pixel
         * @return Reference to the pixel
         */
        sf::Uint8 &operator[](size_t index);

    private:
        /**
         * @brief Pixels of the pixel array
         */
        std::unique_ptr<sf::Uint8> _pixels;
    };
}
