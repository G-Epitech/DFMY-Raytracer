/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereProvider
*/

#include <vector>
#include "Sphere.hpp"
#include "SphereProvider.hpp"

using Raytracer::Objects::SphereProvider;

std::shared_ptr<Raytracer::Common::IObject> SphereProvider::create()
{
    return std::make_shared<Raytracer::Objects::Sphere>();
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
