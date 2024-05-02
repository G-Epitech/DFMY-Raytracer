/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#include <memory>
#include "Screen.hpp"

Rendering::Screen::Screen(const Size &size) : size(size) {
    _pixels = std::make_unique<Pixel[]>(size.width * size.height);
}

Pixel &Rendering::Screen::operator()(size_t x, size_t y) {
    return _pixels[x + y * size.height];
}
