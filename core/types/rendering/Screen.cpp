/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#include <memory>
#include "Screen.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

Rendering::Screen::Screen(const Config &config) : size(config.size), origin(config.origin) {
    _pixels = std::make_unique<Graphics::Pixel[]>(size.width * size.height);
}

Graphics::Pixel &Rendering::Screen::operator()(size_t x, size_t y) {
    return _pixels[x + y * size.height];
}
