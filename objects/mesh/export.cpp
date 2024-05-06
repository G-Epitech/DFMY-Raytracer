/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** export
*/

#include "MeshProvider.hpp"
#include "common/types/Libraries.hpp"

using namespace Raytracer::Common;

extern "C" {
    ObjectType OBJECT_TYPE_GETTER_NAME(void)
    {
        return ObjectType::MESH;
    }

    IObjectProvider *OBJECT_PROVIDER_GETTER_NAME(void)
    {
        return new Raytracer::Objects::MeshProvider();
    }
}
