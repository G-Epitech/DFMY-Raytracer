/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Handler.cpp
*/

#include <iostream>
#include "Handler.hpp"
#include "libs/DLLoader/DLLoader.hpp"
#include "common/types/Libraries.hpp"
#include "common/interfaces/IObjectProvider.hpp"

using namespace Raytracer::Core::Cli;


Handler::Handler(Raytracer::Core::App::Arguments &args): _args(args) {}

Handler::~Handler() = default;

int Handler::run() {
    DLLoader loader("plugins/raytracer_mesh.so");

    auto mesh = loader.loadSymbol<Raytracer::Common::ObjectProviderGetter>(SHARED_STRINGIFY(OBJECT_PROVIDER_GETTER_NAME));

    Raytracer::Common::Graphics::Material material(
        {255, 255, 255},
        {0, 0, 0},
        {0, 0, 0},
        0
    );
    Raytracer::Common::Math::Point3D position(0, 0, 0);

    auto mug = mesh()->create(std::make_shared<Raytracer::Common::Graphics::Material>(material), position, {"mug.obj"});

    std::cout << "Handler cli running" << std::endl;
    return 0;
}
