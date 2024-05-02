/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Float.cpp
*/

#include "Float.hpp"

Math::Float2::Float2(float x, float y): x(x), y(y) {}

Math::Float3::Float3(float x, float y, float z): Float2(x, y), z(z) {}
