/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** meshProvider
*/

#include <vector>
#include <memory>
#include "Mesh.hpp"
#include "MeshProvider.hpp"
#include "config/ConfigUtils.hpp"

using Raytracer::Objects::MeshProvider;

std::shared_ptr<Raytracer::Common::IObject> MeshProvider::create(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Mesh>(name, material, rotation, position, property);
}

Raytracer::Common::Object::Manifest MeshProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "mesh",
        "A simple mesh object",
        "1.1.2",
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

Raytracer::Common::ObjectProperty MeshProvider::parseProperty(const libconfig::Setting &setting)
{
    Raytracer::Common::MeshProperty property;

    if (!setting.isGroup()) {
        throw std::runtime_error("mesh properties must be a group");
    }
    ConfigUtils::settingHasValidKeys("mesh", setting, {"path", "scale"});
    ConfigUtils::lookupValueWrapper("path", setting, property.filename);
    ConfigUtils::lookupValueWrapper("scale", setting, property.scale);
    if (property.scale <= 0) {
        throw std::runtime_error("mesh scale must be greater than 0");
    }
    return property;
}
