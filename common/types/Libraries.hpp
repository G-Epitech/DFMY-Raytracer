/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Libraries
*/

#pragma once

#include "interfaces/IObjectProvider.hpp"

#define OBJECT_PROVIDER_GETTER_NAME getObjectProvider
#define STRINGIFY(x) #x
#define SHARED_STRINGIFY(x) STRINGIFY(x)

namespace Raytracer::Common{
    typedef IObjectProvider* (*ObjectProviderGetter)(void);
}
