/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** export
*/

#include "SphereProvider.hpp"
#include "common/types/Libraries.hpp"

using namespace Raytracer::Common;

extern "C" {
    ObjectType OBJECT_TYPE_GETTER_NAME(void)
    {
        return ObjectType::SPHERE;
    }

    IObjectProvider *OBJECT_PROVIDER_GETTER_NAME(void)
    {
        return new Raytracer::Objects::SphereProvider();
    }
}
