/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"
#include "types/graphics/Pixel.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

Rendering::Camera::Camera(const Config &config) :
        screen(config.screen),
        position(config.position),
        direction(config.direction),
        fov(config.fov),
        name(config.name) {}

void Rendering::Camera::compute(size_t threads, std::vector<Graphics::IObject> &objects) {
    if (threads % 2 != 0)
        throw ComputeError("Invalid number of threads. Must be divisible per two.");

    for (size_t y = 0; y < 2; y++) {
        for (size_t x = 0; x < threads / 2; x++) {
            Common::Math::Size origin{
                    .width = (screen.size.width / threads) * x,
                    .height = (screen.size.height / 2) * y
            };
            Common::Math::Size size{
                    .width = screen.size.width / threads,
                    .height = screen.size.height / 2
            };

            this->_threads.emplace_back(&Camera::computeSegment, this, origin, size, std::ref(objects));
        }
    }
}

void Rendering::Camera::computeSegment(Common::Math::Size origin, Common::Math::Size size,
                                       std::vector<Graphics::IObject> &objects) {
    std::vector<Graphics::IObject> castObjects;

    for (size_t y = origin.height; y < origin.height + size.height; y++) {
        for (size_t x = origin.width; x < origin.width + size.width; x++) {
            for (auto &object : objects) {
                Math::Ray ray = Math::Ray();
                auto hitConfig = object.computeCollision();
            }
        }
    }
}

Rendering::Camera::ComputeError::ComputeError(const std::string &msg) {
    this->_msg = msg;
}

const char *Rendering::Camera::ComputeError::what() const noexcept {
    return this->_msg.c_str();
}
