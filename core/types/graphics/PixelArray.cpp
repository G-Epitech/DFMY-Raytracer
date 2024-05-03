/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PixelArray.cpp
*/

#include "PixelArray.hpp"

using namespace Raytracer::Core::Graphics;

sf::Uint8 *PixelArray::operator*() const {
    return _pixels.get();
}

PixelArray::PixelArray(size_t size) {
    _pixels = std::make_unique<sf::Uint8>(size);
}

sf::Uint8 &PixelArray::operator[](size_t index)  {
    return _pixels.get()[index];
}
