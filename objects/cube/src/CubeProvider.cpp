/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CubeProvider
*/

#include <vector>
#include <memory>
#include "Cube.hpp"
#include "CubeProvider.hpp"
#include "common/config/ConfigUtils.hpp"

using Raytracer::Objects::CubeProvider;

std::shared_ptr<Raytracer::Common::IObject> CubeProvider::create(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Cube>(name, material, rotation, position, property);
}

Raytracer::Common::Object::Manifest CubeProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "cube",
        "A simple cube object",
        "1.0.0",
        {
            {
                "Yann Masson",
                "yann.masson@epitech.eu",
                "https://github.com/Yann-Masson"
            }
        }
    };

    return manifest;
}

Raytracer::Common::ObjectProperty CubeProvider::parseProperty(const libconfig::Setting &setting)
{
    Common::Math::Float3 size;

    if (!setting.isGroup()) {
        throw std::runtime_error("cube properties must be a group");
    }
    ConfigUtils::settingHasValidKeys("cube", setting, {"width", "height", "depth"});
    ConfigUtils::lookupValueWrapper("width", setting, size.x);
    ConfigUtils::lookupValueWrapper("height", setting, size.y);
    ConfigUtils::lookupValueWrapper("depth", setting, size.z);
    if (size.x <= 0 || size.y <= 0 || size.z <= 0) {
        throw std::runtime_error("cube size must be greater than 0");
    }
    return size;
}
