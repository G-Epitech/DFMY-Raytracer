/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Camera.cpp
*/

#include <cmath>
#include "Camera.hpp"
#include "types/graphics/Pixel.hpp"

using namespace Raytracer::Core::Rendering;
using namespace Raytracer::Common;

Camera::Camera(const Config &config) :
        screen(config.screen),
        position(config.position),
        direction(config.direction),
        fov(config.fov),
        name(config.name),
        _computeStatus(FINISHED)
        {}

void Camera::compute(const ComputeParams &params, std::vector<IObject::Ptr> &objects) {
    if (params.threads % 2 != 0)
        throw ComputeError("Invalid number of threads. Must be divisible per two.");

    float screenHeight = 2 * tanf(fov * 0.5f * (float(M_PI) / 180.0f)) * 2.f;
    float cameraAspect = (float) screen.size.width / (float) screen.size.height;
    float screenWidth = screenHeight * cameraAspect;

    auto screenOrigin = Math::Point3D(position.x - screenWidth / 2, position.y + 2,
                                      position.z + screenHeight / 2);

    screen.clear();
    cancelCompute();
    waitThreadsTeardown();

    _processedPixels = 0;
    _computeStatus = RUNNING;
    for (size_t y = 0; y < 2; y++) {
        for (size_t x = 0; x < params.threads / 2; x++) {
            Segment config{
                    .origin = {
                            .width = (screen.size.width / (params.threads / 2)) * x,
                            .height = (screen.size.height / 2) * y
                    },
                    .size {
                            .width = screen.size.width / (params.threads / 2),
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
            Common::Graphics::Color oldFrame = this->_computeFrame(config, objects, x, y);

            for (size_t i = 0; i < 0; i++) {
                auto newFrame = this->_computeFrame(config, objects, x, y);
                float weight = 1.0f / (i + 1);

                Common::Graphics::Color firstFrame = oldFrame * (1 - weight);
                Common::Graphics::Color secondFrame = newFrame * weight;

                oldFrame = firstFrame + secondFrame;
            }
            if (_computeStatus == ABORTED)
                return;
            while (_computeStatus == PAUSED) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            screen.setPixel(x, y, oldFrame.toPixel());

            this->_statusMutex.lock();
            this->_processedPixels++;
            this->_statusMutex.unlock();
        }
    }
}

Graphics::Color Camera::_computeFrame(Raytracer::Core::Rendering::Camera::Segment config,
                                      std::vector<Common::IObject::Ptr> &objects, size_t x, size_t y) {
    float tx = (float) x / ((float) screen.size.width - 1.0f);
    float ty = (float) y / ((float) screen.size.height - 1.0f);

    auto pixelPosition = Math::Point3D(config.localScreenOrigin.x + config.localScreenSize.x * tx,
                                       config.localScreenOrigin.y,
                                       config.localScreenOrigin.z - config.localScreenSize.y * ty);
    auto rayDirection = Math::Vector3D(pixelPosition.x - position.x, pixelPosition.y - position.y,
                                       pixelPosition.z - position.z).normalize();
    auto ray = Math::Ray(position, rayDirection);

    size_t pixelIndex = y * screen.size.width + x;

    Common::Graphics::Color totalIncomingLight(0, 0, 0);

    size_t raysPerPixels = 10;
    for (size_t ri = 0; ri < raysPerPixels; ri++) {
        auto random = pixelIndex + ri;
        auto incomingLight = this->_getIncomingLight(ray, random, objects);

        totalIncomingLight += incomingLight;
    }

    return totalIncomingLight / static_cast<float>(raysPerPixels / 2);
}

Math::HitInfo Camera::_computeRayCollision(const Math::Ray &ray, std::vector<IObject::Ptr> &objects) {
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

Graphics::Color Camera::_getIncomingLight(Math::Ray ray, unsigned int rngState, std::vector<IObject::Ptr> &objects) {
    Common::Graphics::Color incomingLight(0, 0, 0);
    Common::Graphics::Color rayColor(1, 1, 1);

    for (unsigned int i = 0; i <= 15; i++) {
        auto hitConfig = this->_computeRayCollision(ray, objects);
        if (hitConfig.didHit) {
            auto randomSeed = rngState + i;
            ray.origin = hitConfig.hitPoint;
            ray.direction = this->_getRandomDirection(hitConfig.normal, randomSeed);

            Common::Graphics::Color emittedLight =
                    hitConfig.hitColor.emissionColor * hitConfig.hitColor.emissionStrength;
            Common::Graphics::Color localIncomingLight = emittedLight * rayColor;

            incomingLight += localIncomingLight;
            rayColor *= hitConfig.hitColor.color;
        } else {
            Common::Graphics::Color environmentLight = _getEnvironmentLight(ray);
            Common::Graphics::Color ambientLight = rayColor;

            ambientLight = ambientLight * 0.6f;
            if (i == 0) {
                ambientLight = ambientLight * 2.0f;
                ambientLight *= environmentLight;
            }

            incomingLight += ambientLight;
            break;
        }
    }
    return incomingLight;
}

Math::Vector3D Camera::_getRandomDirection(Math::Vector3D &normal, unsigned int &rngState) {
    float randomX = rngState * (rngState + rand() % 1000) * (rngState + rand() % 1000) * (rngState + rand() % 1000);
    float randomY = rngState * (rngState + rand() % 1000) * (rngState + rand() % 1000) * (rngState + rand() % 1000);
    float randomZ = rngState * (rngState + rand() % 1000) * (rngState + rand() % 1000) * (rngState + rand() % 1000);
    randomX = randomX / 4294967295.0;
    randomY = randomY / 4294967295.0;
    randomZ = randomZ / 4294967295.0;

    float theta = 2 * M_PI * randomX;
    float rho = sqrt(-2 * logf(randomY)) * cosf(theta);
    float phi = 2 * M_PI * randomZ;

    float x = rho * cosf(phi);
    float y = rho * sinf(phi);
    float z = sqrtf(fabs(1 - (x * x) - (y * y)));

    Math::Vector3D randomDirection = Math::Vector3D(x, y, z).normalize();
    float dot = normal.dot(randomDirection);

    return randomDirection * dot;
}

Graphics::Color Camera::_getEnvironmentLight(Math::Ray &ray) {
    float skyGradiantT = pow(_smoothStep(-0.25, 0.4f, ray.direction.z), 0.35f);
    Common::Graphics::Color skyGradiant = _lErp(Common::Graphics::Color(1, 1, 1),
                                                Common::Graphics::Color::fromRGB(0, 63, 93), skyGradiantT);
    Common::Graphics::Color groundColor = Common::Graphics::Color::fromRGB(80, 80, 80);

    Math::Vector3D sunDirection = Math::Vector3D(0, 0, -1);
    float max = std::max<float>(0, ray.direction.dot(sunDirection * -1));
    float sun = pow(max, 200) * 10;

    float groundToSkyT = _smoothStep(-0.1, 0, ray.direction.z);
    float sunMask = groundToSkyT >= 1 ? 0 : 1;

    return _lErp(groundColor, skyGradiant, groundToSkyT);
}

float Camera::_smoothStep(float edge0, float edge1, float x) {
    x = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3.0f - 2.0f * x);
}

Graphics::Color Camera::_lErp(const Common::Graphics::Color &a, const Common::Graphics::Color &b, float t) {
    Common::Graphics::Color bt = b * t;

    return a * (1 - t) + bt;
}

Camera::ComputeError::ComputeError(const std::string &msg) {
    this->_msg = msg;
}

const char *Camera::ComputeError::what() const noexcept {
    return this->_msg.c_str();
}

Camera::ComputeStatus Camera::getComputeStatus() const {
    return _computeStatus;
}

void Camera::cancelCompute() {
    _computeStatus = ABORTED;
}

void Camera::pauseCompute() {
    if (_computeStatus == RUNNING)
        _computeStatus = PAUSED;
}

void Camera::resumeCompute() {
    if (_computeStatus == PAUSED)
        _computeStatus = RUNNING;
}

void Camera::waitThreadsTeardown() {
    for (auto &thread : _threads) {
        thread.join();
    }
    _threads.clear();
    _computeStatus = FINISHED;
}

void Camera::waitFinished() const {
    while (_computeStatus != FINISHED);
}

float Camera::getComputeProgress() const {
    if (this->_processedPixels == screen.size.width * screen.size.height)
        return 1.0f;
    return (float) _processedPixels / (float) (screen.size.width * screen.size.height);
}
