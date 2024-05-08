/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Vector.cpp
*/

#include <cmath>
#include "Vector.hpp"

using namespace Raytracer::Common;

Math::Vector3D::Vector3D(float x, float y, float z) : Float3(x, y, z) {}

Math::Vector3D::Vector3D(const Math::Vector3D &vector): Vector3D(vector.x, vector.y, vector.z) {}

float Math::Vector3D::dot(const Math::Vector3D &other) const {
    return this->x * other.x +
           this->y * other.y +
           this->z * other.z;
}

Math::Vector3D Math::Vector3D::normalize() const {
    return *this / length();
}

Math::Vector3D Math::Vector3D::operator+(const Math::Vector3D &other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Math::Vector3D &Math::Vector3D::operator+=(const Math::Vector3D &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Math::Vector3D Math::Vector3D::operator-(const Math::Vector3D &other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Math::Vector3D &Math::Vector3D::operator-=(const Math::Vector3D &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Math::Vector3D Math::Vector3D::operator*(const Math::Vector3D &other) const {
    return Vector3D(x * other.x, y * other.y, z * other.z);
}

Math::Vector3D &Math::Vector3D::operator*=(const Math::Vector3D &other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Math::Vector3D Math::Vector3D::operator*(float c) const {
    return Vector3D(x * c, y * c, z * c);
}

Math::Vector3D &Math::Vector3D::operator*=(float c) {
    x *= c;
    y *= c;
    z *= c;
    return *this;
}

Math::Vector3D Math::Vector3D::operator/(float c) const {
    return c == 0 ? Vector3D(0, 0, 0) : operator*(1 / c);
}

Math::Vector3D &Math::Vector3D::operator/=(float c) {
    return c == 0 ? *this : operator*=(1 / c);
}

float Math::Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

Math::Vector3D Math::Vector3D::cross(const Math::Vector3D &other) const {
    return Vector3D(
        (y * other.z - z * other.y),
        (z * other.x - x * other.z),
        (x * other.y - y * other.x)
    );
}

std::ostream &operator<<(std::ostream &os, const Math::Vector3D &vec) {
    os << "Vector3D(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

Math::Vector2D::Vector2D(float x, float y) : Float2(x, y) {}

Math::Vector2D::Vector2D(const Math::Vector2D &vector): Vector2D(vector.x, vector.y) {}

Math::Vector2D Math::Vector2D::operator+(const Math::Vector2D &other) const {
    return Vector2D(x + other.x, y + other.y);
}

Math::Vector2D &Math::Vector2D::operator+=(const Math::Vector2D &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Math::Vector2D Math::Vector2D::operator-(const Math::Vector2D &other) const {
    return Vector2D(x - other.x, y - other.y);
}

Math::Vector2D &Math::Vector2D::operator-=(const Math::Vector2D &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Math::Vector2D Math::Vector2D::operator*(const Math::Vector2D &other) const {
    return Vector2D(x * other.x, y * other.y);
}

Math::Vector2D &Math::Vector2D::operator*=(const Math::Vector2D &other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Math::Vector2D Math::Vector2D::operator*(float c) const {
    return Vector2D(x * c, y * c);
}

Math::Vector2D &Math::Vector2D::operator*=(float c) {
    x *= c;
    y *= c;
    return *this;
}

Math::Vector2D Math::Vector2D::operator/(float c) const {
    return c == 0 ? Vector2D(0, 0) : operator*(1 / c);
}

Math::Vector2D &Math::Vector2D::operator/=(float c) {
    return c == 0 ? *this : operator*=(1 / c);
}

float Math::Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

Math::Vector3D Math::Vector3D::rotate(const Math::Vector3D &axis) {
    float x = this->x;
    float y = this->y;
    float z = this->z;
    float u = axis.x;
    float v = axis.y;
    float w = axis.z;
    float xPrime = u * (u * x + v * y + w * z) * (1 - std::cos(0.1)) + x * std::cos(0.1) + (-w * y + v * z) * std::sin(0.1);
    float yPrime = v * (u * x + v * y + w * z) * (1 - std::cos(0.1)) + y * std::cos(0.1) + (w * x - u * z) * std::sin(0.1);
    float zPrime = w * (u * x + v * y + w * z) * (1 - std::cos(0.1)) + z * std::cos(0.1) + (-v * x + u * y) * std::sin(0.1);
    return Vector3D(xPrime, yPrime, zPrime);
}
