/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include <math.h>
#include "Camera.hpp"
#include "types/graphics/Pixel.hpp"

using namespace Raytracer::Core::Rendering;
using namespace Raytracer::Common;

Camera::Camera(const Config &config) :
        screen(config.screen),
        position(config.position),
        direction(config.direction),
        fov(config.fov),
        name(config.name) {}

void Camera::compute(size_t threads, std::vector<IObject::Ptr> &objects) {
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

void Camera::_computeSegment(Segment config, std::vector<IObject::Ptr> &objects) {
    for (size_t y = config.origin.height; y < config.origin.height + config.size.height; y++) {
        for (size_t x = config.origin.width; x < config.origin.width + config.size.width; x++) {
            float tx = (float) x / ((float) screen.size.width - 1.0f);
            float ty = (float) y / ((float) screen.size.height - 1.0f);

            auto pixelPosition = Math::Point3D(config.localScreenOrigin.x + config.localScreenSize.x * tx,
                                               config.localScreenOrigin.y,
                                               config.localScreenOrigin.z - config.localScreenSize.y * ty);
            auto rayDirection = Math::Vector3D(pixelPosition.x - position.x, pixelPosition.y - position.y,
                                               pixelPosition.z - position.z).normalize();
            auto ray = Math::Ray(position, rayDirection);

            size_t pixelIndex = y * screen.size.width + x;
            Common::Graphics::Color color = this->_getIncomingLight(ray, pixelIndex, objects);
            screen.setPixel(x, y, color.toPixel());
        }
    }
}

Math::HitInfo Camera::_computeRayCollision(const Math::Ray& ray, std::vector<IObject::Ptr> &objects)
{
    Math::HitInfo closestHit;

    closestHit.distance = std::numeric_limits<float>::max();

    for (auto &object: objects) {
        auto hitConfig = object->computeCollision(ray);

        if (hitConfig.didHit && hitConfig.distance < closestHit.distance) {
            closestHit = hitConfig;
        }
    }

    return closestHit;
}

Graphics::Color Camera::_getIncomingLight(Math::Ray &ray, unsigned int rngState, std::vector<IObject::Ptr> &objects) {
    Common::Graphics::Color incomingLight(0, 0, 0);
    Common::Graphics::Color rayColour(1, 1, 1);

    for (int i = 0; i <= 30; i++) {
        auto hitConfig = this->_computeRayCollision(ray, objects);
        if (hitConfig.didHit) {
            ray.origin = hitConfig.hitPoint;
            ray.direction = this->_getRandomDirection(hitConfig.normal, rngState);

            Common::Graphics::Color emittedLight = hitConfig.hitColor.emissionColor * hitConfig.hitColor.emissionStrength;
            Common::Graphics::Color localIncomingLight = emittedLight * rayColour;

            incomingLight += localIncomingLight;
            rayColour *= hitConfig.hitColor.color;
        } else {
            Common::Graphics::Color ambientLight = rayColour * 0.2f;
            incomingLight += ambientLight;

            break;
        }
    }
    return incomingLight;
}

Math::Vector3D Camera::_getRandomDirection(Math::Vector3D &normal, unsigned int &rngState)
{
    float randomX = rngState * (rngState + 195439) * (rngState + 124395) * (rngState + 845921);
    float randomY = rngState * (rngState + 59283) * (rngState + 48217) * (rngState + 271829);
    float randomZ = rngState * (rngState + 712849) * (rngState + 193847) * (rngState + 38291);
    randomX = randomX / 4294967295.0;
    randomY = randomY / 4294967295.0;
    randomZ = randomZ / 4294967295.0;

    float theta = 2 * M_PI * randomX;
    float rho = sqrt(-2 * log(randomY)) * cos(theta);
    float phi = 2 * M_PI * randomZ;

    float x = rho * cos(phi);
    float y = rho * sin(phi);
    float z = sqrt(1 - (x*x) - (y*y));

    Math::Vector3D randomDirection = Math::Vector3D(x, y, z).normalize();
    float dot = normal.dot(randomDirection);

    return randomDirection * dot;
}

Camera::ComputeError::ComputeError(const std::string &msg) {
    this->_msg = msg;
}

const char *Camera::ComputeError::what() const noexcept {
    return this->_msg.c_str();
}
