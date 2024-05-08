/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color.cpp
*/

#include <iostream>
#include "Color.hpp"
#include "types/math/Float.hpp"

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
    Math::Float3 thisFloat3 = toFloat3(*this);
    Math::Float3 otherFloat3 = toFloat3(other);
    Math::Float3 resultFloat3 = thisFloat3 * otherFloat3;

    return toColor(resultFloat3);
}

Graphics::Color &Graphics::Color::operator*=(Graphics::Color &other) {
    *this = *this * other;
    return *this;
}

Graphics::Color Graphics::Color::operator+(Graphics::Color &other) const {
    Math::Float3 tf = toFloat3(*this);
    Math::Float3 of = toFloat3(other);
    Math::Float3 resultFloat3 = tf + of;

    if (resultFloat3.x > 1) resultFloat3.x = 1;
    if (resultFloat3.y > 1) resultFloat3.y = 1;
    if (resultFloat3.z > 1) resultFloat3.z = 1;

    return toColor(resultFloat3);
}

Graphics::Color &Graphics::Color::operator+=(Graphics::Color &other) {
    *this = *this + other;
    return *this;
}

Math::Float3 Graphics::Color::toFloat3(const Graphics::Color &color) const {
    Math::Float3 result(
            static_cast<float>(color.r) / 255,
            static_cast<float>(color.g) / 255,
            static_cast<float>(color.b) / 255
    );

    return result;
}

Graphics::Color Graphics::Color::toColor(const Math::Float3 &float3) const {
    return {
            static_cast<unsigned char>(float3.x * 255),
            static_cast<unsigned char>(float3.y * 255),
            static_cast<unsigned char>(float3.z * 255)
    };
}
