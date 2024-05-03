/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereProvider
*/

#pragma once

#include "common/types/object/Provider.hpp"
#include "common/interfaces/graphics/IObject.hpp"

namespace Raytracer::Objects::Sphere {
    class SphereProvider : public Raytracer::Common::Object::Provider {
        public:
            // void *create() override;
            // void destroy(void *object) override;
            int getType() override;
    };
}
