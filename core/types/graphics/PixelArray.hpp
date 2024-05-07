/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PixelArray.hpp
*/

#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

namespace Raytracer::Core::Graphics {
    /// @brief Pixel array of the screen
    typedef std::unique_ptr<sf::Uint8[]> PixelArray;
}
