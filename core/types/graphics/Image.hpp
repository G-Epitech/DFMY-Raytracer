/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Image.hpp
*/

#pragma once

#include <cstddef>
#include <SFML/Graphics.hpp>
#include "PixelArray.hpp"

namespace Raytracer::Core::Graphics {
    class Image {
    public:
        /**
         * @brief Create a new Image
         * @param width Width of image
         * @param height Height of image
         */
        explicit Image(size_t width, size_t height, PixelArray &array);

        /// @brief Default destructor of the image
        ~Image() = default;

        /// @brief Width of the image
        const size_t width;

        /// @brief Height of the image
        const size_t height;

        /**
         * @brief Save the image to the given path
         * @param path Path to save the image
         * @return Saving status
         */
        [[nodiscard]]
        bool saveTo(const std::string &path) const;

    private:
        /// @brief Inner SFML image
        sf::Image _image;

        /**
         * @brief Save the image as a PPM file
         * @param path Path to save the image
         * @return Success status
         */
        [[nodiscard]]
        bool _saveAsPpm(const std::string &path) const;
    };
}
