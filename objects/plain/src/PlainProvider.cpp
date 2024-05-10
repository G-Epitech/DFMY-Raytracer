/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PlainProvider
*/

#include <vector>
#include <memory>
#include "Plain.hpp"
#include "PlainProvider.hpp"

using Raytracer::Objects::PlainProvider;

std::shared_ptr<Raytracer::Common::IObject> PlainProvider::create(
    const Raytracer::Common::Graphics::Material::Ptr material,
    const Raytracer::Common::Math::Point3D &position,
    const Raytracer::Common::ObjectProperty &property)
{
    return std::make_shared<Raytracer::Objects::Plain>(material, position, property);
}

Raytracer::Common::Object::Manifest PlainProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "Plain",
        "A simple plain object",
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
