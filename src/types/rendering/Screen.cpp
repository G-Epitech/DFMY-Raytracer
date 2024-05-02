/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#include <memory>
#include "Screen.hpp"

Rendering::Screen::Screen(size_t width, size_t height): width(width), height(height) {
    _pixels = std::make_unique<Pixel[]>(width * height);
}

Pixel &Rendering::Screen::operator()(size_t x, size_t y) {
    return _pixels[x + y * width];
}
