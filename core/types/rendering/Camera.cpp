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

    float screenHeight = 2 * tan(fov * 0.5 * (M_PI / 180.0)) * 2;
    float cameraAspect = (float) screen.size.width / (float) screen.size.height;
    float screenWidth = screenHeight * cameraAspect;

    auto screenOrigin = Math::Point3D(position.x - screenWidth / 2, position.y + 2,
                                      position.z + screenHeight / 2);

    for (size_t y = 0; y < 2; y++) {
        for (size_t x = 0; x < threads / 2; x++) {
            Segment config{
                    .origin = {
                            .width = (screen.size.width / (threads / 2)) * x,
                            .height = (screen.size.height / 2) * y
                    },
                    .size {
                            .width = screen.size.width / (threads / 2),
                            .height = screen.size.height / 2
                    },
                    .localScreenSize = Math::Float2(screenWidth, screenHeight),
                    .localScreenOrigin = screenOrigin
            };

            this->_threads.emplace_back(&Camera::_computeSegment, this, config, std::ref(objects));
        }
    }
}

void Rendering::Camera::_computeSegment(Segment config, std::vector<IObject::Ptr> &objects) {
    std::vector<IObject::Ptr> castObjects;

    for (size_t y = config.origin.height; y < config.origin.height + config.size.height; y++) {
        for (size_t x = config.origin.width; x < config.origin.width + config.size.width; x++) {
            float tx = (float) x / ((float) screen.size.width - 1.0f);
            float ty = (float) y / ((float) screen.size.height - 1.0f);

            auto pixelPosition = Math::Point3D(config.localScreenOrigin.x + config.localScreenSize.x * tx,
                                               config.localScreenOrigin.y,
                                               config.localScreenOrigin.z - config.localScreenSize.y * ty);
            auto rayDirection = Math::Vector3D(pixelPosition.x - position.x, pixelPosition.y - position.y,
                                               pixelPosition.z - position.z).normalize();

            for (auto &object: objects) {
                Math::Ray ray = Math::Ray(position, rayDirection);
                auto hitConfig = object->computeCollision(ray);

                if (hitConfig.didHit) {
                    castObjects.push_back(object);
                    screen.setPixel(x, y, hitConfig.hitColor.color.toPixel());
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
