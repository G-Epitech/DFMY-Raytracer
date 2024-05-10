/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PlaneProvider
*/

#include <vector>
#include <memory>
#include "Plane.hpp"
#include "PlaneProvider.hpp"
#include "common/config/ConfigUtils.hpp"

using Raytracer::Objects::PlaneProvider;

std::shared_ptr<Raytracer::Common::IObject> PlaneProvider::create(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Plane>(name, material, rotation, position, property);
}

Raytracer::Common::Object::Manifest PlaneProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "plane",
        "A simple plane object",
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

Raytracer::Common::ObjectProperty PlaneProvider::parseProperty(const libconfig::Setting &setting)
{
    Common::Math::Vector3D normal;

    if (!setting.isGroup()) {
        throw std::runtime_error("plane properties must be a group");
    }
    ConfigUtils::settingHasValidKeys("plane", setting, {"normal"});
    normal = ConfigUtils::parseVector3D("normal", setting["normal"]);
    if (normal == Common::Math::Vector3D(0, 0, 0)) {
        throw std::runtime_error("plane normal must be different from 0, 0, 0");
    }
    return normal;
}
