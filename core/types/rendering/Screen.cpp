/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Screen.hpp
*/

#include "Screen.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

Rendering::Screen::Screen(const Config &config) : size(config.size) {
    resize(size);
}

void Rendering::Screen::setPixel(size_t x, size_t y, const Common::Graphics::Pixel &pixel) {
    auto index = static_cast<ptrdiff_t>(y * size.width + x) * 4;

    _pixels[index] = pixel.r;
    _pixels[index + 1] = pixel.g;
    _pixels[index + 2] = pixel.b;
    _pixels[index + 3] = pixel.a;
}

Raytracer::Core::Graphics::PixelArray &Rendering::Screen::getPixels() {
    return _pixels;
}

void Rendering::Screen::resize(const Math::Size &newSize) {
    auto pixelsSize = newSize.width * newSize.height * 4;

    _pixels.reset();
    _pixels = std::unique_ptr<sf::Uint8[]>(new sf::Uint8[pixelsSize]);
    size = newSize;
}

void Rendering::Screen::clear() {
    auto pixelsSize = size.width * size.height * 4;

    for (size_t i = 0; i < pixelsSize; i++)
        _pixels[i] = 0;
}

Rendering::Screen::~Screen() = default;
