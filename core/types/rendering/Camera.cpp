/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

Rendering::Camera::Camera(const Config &config) :
    screen(config.screen),
    position(config.position),
    direction(config.direction),
    fov(config.fov) {}
