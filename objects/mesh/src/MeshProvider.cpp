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

using Raytracer::Objects::MeshProvider;

std::shared_ptr<Raytracer::Common::IObject> MeshProvider::create(
    const Raytracer::Common::Graphics::Material::Ptr material,
    const Raytracer::Common::Math::Point3D &position,
    const Raytracer::Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Mesh>(material, position, property);
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
