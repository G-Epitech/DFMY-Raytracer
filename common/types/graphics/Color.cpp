/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color.cpp
*/

#include <algorithm>
#include "Color.hpp"
#include "types/math/Float.hpp"

using namespace Raytracer::Common;

Graphics::Color::Color(
        float r,
        float g,
        float b,
        float a
) : r(r), g(g), b(b), a(a) {}

Graphics::Color::Color() : r(0), g(0), b(0), a(1) {}

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
    Graphics::Color color = *this;

    color.normalize();
    return {
            static_cast<unsigned char>(color.r * 255),
            static_cast<unsigned char>(color.g * 255),
            static_cast<unsigned char>(color.b * 255),
            static_cast<unsigned char>(color.a * 255)
    };
}

Graphics::Color Graphics::Color::operator*(float scalar) const {
    return {r * scalar, g * scalar, b * scalar, a};
}

Graphics::Color Graphics::Color::operator*(Graphics::Color &other) const {
    Math::Float3 tf(r, g, b);
    Math::Float3 of(other.r, other.g, other.b);
    Math::Float3 resultFloat3 = tf * of;

    return {resultFloat3.x, resultFloat3.y, resultFloat3.z, a};
}

Graphics::Color &Graphics::Color::operator*=(Graphics::Color &other) {
    *this = *this * other;
    return *this;
}

Graphics::Color Graphics::Color::operator+(Graphics::Color &other) const {
    Math::Float3 tf(r, g, b);
    Math::Float3 of(other.r, other.g, other.b);
    Math::Float3 resultFloat3 = tf + of;

    return {resultFloat3.x, resultFloat3.y, resultFloat3.z, a};
}

Graphics::Color &Graphics::Color::operator+=(Graphics::Color &other) {
    *this = *this + other;
    return *this;
}

void Graphics::Color::normalize() {
    r = std::clamp(r, 0.0f, 1.0f);
    g = std::clamp(g, 0.0f, 1.0f);
    b = std::clamp(b, 0.0f, 1.0f);
    a = std::clamp(a, 0.0f, 1.0f);
}

Graphics::Color Graphics::Color::fromRGB(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return {
            static_cast<float>(r) / 255.0f,
            static_cast<float>(g) / 255.0f,
            static_cast<float>(b) / 255.0f,
            static_cast<float>(a) / 255.0f
    };
}

Graphics::Color Graphics::Color::operator/(float scalar) const {
    return {r / scalar, g / scalar, b / scalar, a};
}
