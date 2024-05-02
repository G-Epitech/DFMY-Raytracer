/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Color.cpp
*/

#include "Color.hpp"

Graphics::Color::Color(float r, float g, float b, float a): r(r), g(g), b(b), a(a) {}

Graphics::Color::Color(): r(0), g(0), b(0), a(255) {}

bool Graphics::Color::operator==(const Color &color) const
{
    return  r == color.r &&
            g == color.g &&
            b == color.b &&
            a == color.a;
}

bool Graphics::Color::operator!=(const Color &color) const
{
    return !(*this == color);
}