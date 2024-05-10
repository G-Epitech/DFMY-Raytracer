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

using Raytracer::Objects::PlaneProvider;

std::shared_ptr<Raytracer::Common::IObject> PlaneProvider::create(
    const Raytracer::Common::Graphics::Material::Ptr material,
    const Raytracer::Common::Math::Point3D &position,
    const Raytracer::Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Plane>(material, position, property);
}

Raytracer::Common::Object::Manifest PlaneProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "Plane",
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
