/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

using namespace Rendering;

Camera::Camera(
    const Screen::Size &screenSize,
    const Math::Point3D &position,
    const Math::Vector3D &rotation,
    float fov
) : screen(screenSize), position(position), rotation(rotation), fov(fov) {}
