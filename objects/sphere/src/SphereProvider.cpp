/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereProvider
*/

#include <vector>
#include <memory>
#include "Sphere.hpp"
#include "config/ConfigUtils.hpp"
#include "SphereProvider.hpp"

using Raytracer::Objects::SphereProvider;

std::shared_ptr<Raytracer::Common::IObject> SphereProvider::create(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Sphere>(name, material, rotation, position, property);
}

Raytracer::Common::Object::Manifest SphereProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "sphere",
        "A simple sphere object",
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

Raytracer::Common::ObjectProperty SphereProvider::parseProperty(const libconfig::Setting &setting)
{
    float radius;

    if (!setting.isGroup()) {
        throw std::runtime_error("sphere properties must be a group");
    }
    ConfigUtils::settingHasValidKeys("sphere", setting, {"radius"});
    ConfigUtils::lookupValueWrapper("radius", setting, radius);
    return radius;
}
