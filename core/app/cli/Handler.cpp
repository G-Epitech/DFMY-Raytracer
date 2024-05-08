/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.cpp
*/

#include <iostream>
#include "Handler.hpp"
#include "types/rendering/Camera.hpp"
#include "libs/DLLoader/DLLoader.hpp"
#include "common/interfaces/IObjectProvider.hpp"
#include "common/types/Libraries.hpp"
#include "objects/sphere/src/SphereProvider.hpp"
#include "types/graphics/Image.hpp"

using namespace Raytracer::Core::Cli;

#if defined(__linux__)
    #define PLUGIN_PATH "plugins/raytracer_sphere.so"
#elif defined(__APPLE__)
    #define PLUGIN_PATH "plugins/raytracer_sphere.dylib"
#elif defined(_WIN32)
    #define PLUGIN_PATH "plugins/raytracer_sphere.dll"
#endif

Handler::Handler(Raytracer::Core::App::Arguments &args): _args(args) {}

Handler::~Handler() = default;

int Handler::run() {
    DLLoader dlloader(PLUGIN_PATH);

    std::shared_ptr<Common::Graphics::Material> green = std::make_shared<Common::Graphics::Material>(
            Common::Graphics::Color(155, 179, 138),
            Common::Graphics::Color(255, 255, 255),
            Common::Graphics::Color(255, 255, 255),
            0
    );
    std::shared_ptr<Common::Graphics::Material> orange = std::make_shared<Common::Graphics::Material>(
            Common::Graphics::Color(230, 119, 33),
            Common::Graphics::Color(255, 255, 255),
            Common::Graphics::Color(255, 255, 255),
            0
    );
    std::shared_ptr<Common::Graphics::Material> red = std::make_shared<Common::Graphics::Material>(
            Common::Graphics::Color(207, 0, 0),
            Common::Graphics::Color(255, 255, 255),
            Common::Graphics::Color(255, 255, 255),
            0
    );
    std::shared_ptr<Common::Graphics::Material> purple = std::make_shared<Common::Graphics::Material>(
            Common::Graphics::Color(168, 106, 212),
            Common::Graphics::Color(255, 255, 255),
            Common::Graphics::Color(255, 255, 255),
            0
    );
    std::shared_ptr<Common::Graphics::Material> yellow = std::make_shared<Common::Graphics::Material>(
            Common::Graphics::Color(224, 255, 0),
            Common::Graphics::Color(255, 255, 255),
            Common::Graphics::Color(255, 255, 255),
            0
    );
    std::shared_ptr<Common::Graphics::Material> light = std::make_shared<Common::Graphics::Material>(
            Common::Graphics::Color(0, 0, 0),
            Common::Graphics::Color(255, 255, 255),
            Common::Graphics::Color(255, 255, 255),
            1.0f
    );

    std::string name = STRINGIFY(OBJECT_PROVIDER_GETTER_NAME);
    auto objectProvider = dlloader.loadSymbol<Common::ObjectProviderGetter>(name);

    Rendering::Camera::Config camConfig = {
            .name = "Main camera",
            .screen = {
                    .size = { .width = 1920 * 2, .height = 1080 * 2 }
            },
            .position = Common::Math::Point3D(0, 0, 30),
            .direction = Common::Math::Vector3D(0, 0, 0),
            .fov = 50
    };
    Rendering::Camera camera(camConfig);
    std::vector<Common::IObject::Ptr> objects;

    objects.push_back(objectProvider()->create(light, Common::Math::Point3D(-35, 100, 80), 50.0f));
    objects.push_back(objectProvider()->create(light, Common::Math::Point3D(30, 50, 30), 3.0f));

    objects.push_back(objectProvider()->create(purple, Common::Math::Point3D(0, 80, -75), 100.0f));
    objects.push_back(objectProvider()->create(green, Common::Math::Point3D(10, 65, 35), 13.0f));
    objects.push_back(objectProvider()->create(orange, Common::Math::Point3D(-10, 60, 30), 10.0f));
    objects.push_back(objectProvider()->create(yellow, Common::Math::Point3D(50, 100, 70), 10.0f));

    camera.compute(COMPUTE_THREADS, objects);

    for (auto& thread : camera._threads) {
        thread.join();
    }

    std::cout << "Rendering done!" << std::endl;
    Core::Graphics::Image image(camera.screen.size.width, camera.screen.size.height, camera.screen.getPixels());

    image.saveTo("output.png");

    return 0;
}
