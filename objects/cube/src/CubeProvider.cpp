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
    Common::Math::Vector3D vsize;

    if (!setting.isGroup()) {
        throw std::runtime_error("cube properties must be a group");
    }
    ConfigUtils::settingHasValidKeys("cube", setting, {"size"});
    vsize = ConfigUtils::parseVector3D("size", setting["size"]);
    if (vsize == Common::Math::Vector3D(0, 0, 0)) {
        throw std::runtime_error("cube size must be different from 0, 0, 0");
    }
    size.x = vsize.x;
    size.y = vsize.y;
    size.z = vsize.z;
    return size;
}
