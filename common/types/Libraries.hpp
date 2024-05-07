/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Libraries
*/

#pragma once

#include "interfaces/IObjectProvider.hpp"

#define OBJECT_PROVIDER_GETTER_NAME getObjectProvider
#define INNER_STRINGIFY(x) #x
#define STRINGIFY(x) INNER_STRINGIFY(x)

namespace Raytracer::Common {
    /// @brief Function pointer to get an object provider
    typedef IObjectProvider* (*ObjectProviderGetter)();
}
