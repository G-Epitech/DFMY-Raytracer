/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Pixel.hpp
*/

#pragma once

namespace Graphics {
    /// @brief Representing a pixel
    typedef struct Pixel {
        /// @brief Red value of the pixel
        unsigned char r;

        /// @brief Green value of the pixel
        unsigned char g;

        /// @brief Blue value of the pixel
        unsigned char b;

        /// @brief Alpha value of the pixel
        unsigned char a;
    } Pixel;
}
