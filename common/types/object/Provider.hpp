/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Provider
*/

#pragma once

namespace Raytracer::Common::Object {
    class Provider;
}

class Raytracer::Common::Object::Provider {
    public:
        virtual ~Provider() = default;
        // virtual void *create() = 0;
        // virtual void destroy(void *object) = 0;
        virtual int getType() = 0;
};
