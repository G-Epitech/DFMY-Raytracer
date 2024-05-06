/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactory.cpp
*/

#include "ObjectFactory.hpp"

#include <utility>

using namespace Raytracer::Core;

ObjectFactory::ObjectFactory(const std::string &pluginsDir) {
}

IObject::Ptr ObjectFactory::create(
    const std::string &name,
    const Graphics::Material::Ptr& material,
    const Math::Point3D &position,
    const ObjectProperty &property
) {
    return nullptr;
}

ObjectFactory::~ObjectFactory() = default;

ObjectFactory::Exception::Exception(std::string message): _message(std::move(message)) {}

const char *ObjectFactory::Exception::what() const noexcept {
    return _message.c_str();
}
