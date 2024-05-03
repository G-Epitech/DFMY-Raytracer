/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereProvider
*/

#include <vector>
#include <memory>
#include "Sphere.hpp"
#include "SphereProvider.hpp"

using Raytracer::Objects::SphereProvider;

std::shared_ptr<Raytracer::Common::IObject> SphereProvider::create(Raytracer::Common::Graphics::Material &material)
{
    return std::make_shared<Raytracer::Objects::Sphere>(material);
}

Raytracer::Common::Object::Manifest SphereProvider::getManifest()
{
    Raytracer::Common::Object::Manifest manifest {
        "Sphere",
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
