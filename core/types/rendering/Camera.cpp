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

void Rendering::Camera::compute(size_t threads, std::vector<IObject::Ptr> &objects) {
    if (threads % 2 != 0)
        throw ComputeError("Invalid number of threads. Must be divisible per two.");

    for (size_t y = 0; y < 2; y++) {
        for (size_t x = 0; x < threads / 2; x++) {
            Common::Math::Size origin{
                    .width = (screen.size.width / (threads / 2)) * x,
                    .height = (screen.size.height / 2) * y
            };
            Common::Math::Size size{
                    .width = screen.size.width / (threads / 2),
                    .height = screen.size.height / 2
            };

            this->_threads.emplace_back(&Camera::computeSegment, this, origin, size, std::ref(objects));
        }
    }
}

void Rendering::Camera::computeSegment(Common::Math::Size origin, Common::Math::Size size,
                                       std::vector<IObject::Ptr> &objects) {
    float screenHeight = 5 * tan(fov * 0.5 * (M_PI / 180.0)) * 2;
    float cameraAspect = (float) screen.size.width / (float) screen.size.height;
    float screenWidth = screenHeight * cameraAspect;

    auto screenOrigin = Math::Point3D(position.x - screenWidth / 2, position.y + 5,
                                      position.z + screenHeight / 2);

    std::vector<IObject::Ptr> castObjects;
    for (size_t y = origin.height; y < origin.height + size.height; y++) {
        for (size_t x = origin.width; x < origin.width + size.width; x++) {
            float tx = (float) x / ((float) screen.size.width - 1.0f);
            float ty = (float) y / ((float) screen.size.height - 1.0f);

            auto pixelPosition = Math::Point3D(screenOrigin.x + screenWidth * tx, screenOrigin.y, screenOrigin.z - screenHeight * ty);
            auto rayDirection = Math::Vector3D(pixelPosition.x - position.x, pixelPosition.y - position.y,
                                               pixelPosition.z - position.z);

            for (auto &object: objects) {
                Math::Ray ray = Math::Ray(position, rayDirection);
                auto hitConfig = object->computeCollision(ray);

                if (hitConfig.didHit) {
                    castObjects.push_back(object);
                    screen.setPixel(x, y, {
                            .r = 255,
                            .g = 0,
                            .b = 0,
                            .a = 255
                    });
                }
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
