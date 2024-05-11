/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** export
*/

#include "CubeProvider.hpp"
#include "common/types/Libraries.hpp"

using namespace Raytracer::Common;

extern "C" {
    IObjectProvider *OBJECT_PROVIDER_GETTER_NAME(void)
    {
        return new Raytracer::Objects::CubeProvider();
    }
}