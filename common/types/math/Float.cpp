/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Float.cpp
*/

#include "Float.hpp"

using namespace Raytracer::Common;

Math::Float2::Float2(float x, float y): x(x), y(y) {}

Math::Float3::Float3(float x, float y, float z): Float2(x, y), z(z) {}

Math::Float3 Math::Float3::operator*(Math::Float3 &other) const {
    Float3 result(
        this->x * other.x,
        this->y * other.y,
        this->z * other.z
    );

    return result;
}

Math::Float3 Math::Float3::operator+(Math::Float3 &other) const {
    Float3 result(
        this->x + other.x,
        this->y + other.y,
        this->z + other.z
    );

    return result;
}
