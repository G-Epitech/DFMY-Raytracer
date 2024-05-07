/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color.cpp
*/

#include "Color.hpp"

using namespace Raytracer::Common;

Graphics::Color::Color(
        unsigned char r,
        unsigned char g,
        unsigned char b,
        unsigned char a
) : r(r), g(g), b(b), a(a) {}

Graphics::Color::Color() : r(0), g(0), b(0), a(255) {}

bool Graphics::Color::operator==(const Color &color) const {
    return r == color.r &&
           g == color.g &&
           b == color.b &&
           a == color.a;
}

bool Graphics::Color::operator!=(const Color &color) const {
    return !(*this == color);
}

Graphics::Pixel Graphics::Color::toPixel() const {
    return {r, g, b, a};
}

Graphics::Color Graphics::Color::operator*(float scalar) const {
    return {
            static_cast<unsigned char>(this->r * scalar),
            static_cast<unsigned char>(this->g * scalar),
            static_cast<unsigned char>(this->b * scalar),
            this->a
    };
}

Graphics::Color Graphics::Color::operator*(Graphics::Color &other) const {
    Color result;

    result.r = this->r * other.r > 255 ? 255 : this->r * other.r;
    result.g = this->g * other.g > 255 ? 255 : this->g * other.g;
    result.b = this->b * other.b > 255 ? 255 : this->b * other.b;
    result.a = this->a;

    return result;
}

Graphics::Color &Graphics::Color::operator*=(Graphics::Color &other) {
    *this = *this * other;
    return *this;
}

Graphics::Color Graphics::Color::operator+(Graphics::Color &other) const {
    Color result;

    result.r = this->r + other.r > 255 ? 255 : this->r + other.r;
    result.g = this->g + other.g > 255 ? 255 : this->g + other.g;
    result.b = this->b + other.b > 255 ? 255 : this->b + other.b;
    result.a = this->a;

    return result;
}

Graphics::Color &Graphics::Color::operator+=(Graphics::Color &other) {
    *this = *this + other;
    return *this;
}
