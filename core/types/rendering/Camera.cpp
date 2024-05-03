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
        fov(config.fov),
        name(config.name) {}

void Rendering::Camera::compute(size_t threads) {
    if (threads % 2 != 0)
        throw ComputeError("Invalid number of threads. Must be divisible per two.");
}

Rendering::Camera::ComputeError::ComputeError(const std::string &msg) {
    this->_msg = msg;
}

const char *Rendering::Camera::ComputeError::what() const noexcept {
    return this->_msg.c_str();
}
