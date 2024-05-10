/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.cpp
*/

#include <iostream>
#include <iomanip>
#include "Handler.hpp"
#include "types/rendering/Camera.hpp"
#include "libs/DLLoader/DLLoader.hpp"
#include "objects/sphere/src/SphereProvider.hpp"
#include "types/graphics/Image.hpp"
#include "libs/DLLoader/DLLoader.hpp"
#include "common/types/Libraries.hpp"
#include "common/interfaces/IObjectProvider.hpp"

using namespace Raytracer::Core::Cli;

#if defined(__linux__)
    #define PLUGIN_PATH "plugins/raytracer_sphere.so"
#elif defined(__APPLE__)
    #define PLUGIN_PATH "plugins/raytracer_sphere.dylib"
#elif defined(_WIN32)
    #define PLUGIN_PATH "plugins/raytracer_sphere.dll"
#endif

Handler::Handler(Raytracer::Core::App::Context &context): _appContext(context), _camerasNamesMaxLength(0) {}

Handler::~Handler() = default;

int Handler::run() {
    Rendering::Camera::ComputeParams params = {
        .threads = _appContext.args.options.threadsCount,
        .additionalFrames = _appContext.args.options.additionalFramesCount,
        .raysPerPixel = _appContext.args.options.raysPerPixel,
        .rayBounceLimit = _appContext.args.options.rayBounce
    };

    _camerasNamesMaxLength = _getCamerasNamesMaxLength();
    for (auto &[name, camera]: _appContext.scene->cameras) {
        _renderCameraImage(name, params, camera);
    }
    return 0;
}

void Handler::_displayProgress(const std::string &cameraName, int camerasNamesMaxLength, float progress) {
    int barWidth = 50;
    int pos = int(float(barWidth) * progress);

    _displayCameraLabel(cameraName, camerasNamesMaxLength);
    std::cout << "[";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

int Handler::_getCamerasNamesMaxLength() {
    size_t maxLength = 0;

    for (auto &[name,_] : _appContext.scene->cameras) {
        if (name.size() > maxLength)
            maxLength = name.size();
    }
    return int(maxLength);
}

void Handler::_renderCameraImage(
    const string &cameraName,
    const Rendering::Camera::ComputeParams &params,
    Rendering::Camera::Ptr &camera
) {
    auto &screen = camera->screen;
    auto image = Graphics::Image(screen.size.width, screen.size.height, screen.getPixels());
    float status = 0;

    camera->compute(params, _appContext.scene->objects);
    status = camera->getComputeStatus();
    while (status < 1.0f) {
        _displayProgress(cameraName, _camerasNamesMaxLength, status);
        status = camera->getComputeStatus();
    }
    _displayProgress(cameraName, _camerasNamesMaxLength, 1.0f);
    camera->waitThreadsTeardown();
    _saveImage(cameraName, camera);
}

void Handler::_displayCameraLabel(const string &cameraName, int camerasNamesMaxLength) {
    auto paddingSize = camerasNamesMaxLength - cameraName.size();
    auto paddingL = std::string(paddingSize / 2, ' ');
    auto paddingR = std::string(paddingSize - paddingL.size(), ' ');

    std::cout << "[" << paddingL << cameraName << paddingR << "]";
}

void Handler::_saveImage(const string &cameraName, Raytracer::Core::Rendering::Camera::Ptr &camera) const {
    auto &screen = camera->screen;
    auto image = Graphics::Image(screen.size.width, screen.size.height, screen.getPixels());
    auto fileName = cameraName + '.' + _appContext.args.options.outputFormat;

    std::cout << std::endl;
    if (image.saveTo(fileName)) {
        _displayCameraLabel(cameraName, _camerasNamesMaxLength);
        std::cout << " Image " << fileName << " saved. Done." << std::endl;
    } else {
        _displayCameraLabel(cameraName, _camerasNamesMaxLength);
        std::cerr << " Fail to save image." << std::endl;
    }
}
