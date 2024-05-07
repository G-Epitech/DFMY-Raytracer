/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactory.cpp
*/

#include "ObjectFactory.hpp"

#include <utility>

using namespace Raytracer::Core;

ObjectFactory::ObjectFactory(PluginsManager &pluginsManager): _pluginsManager(pluginsManager) {}

ObjectFactory::~ObjectFactory() = default;

IObject::Ptr ObjectFactory::create(const std::string &name, const Graphics::Material::Ptr &material,
    const Math::Point3D &position, const ObjectProperty &property)
{
    auto provider = _pluginsManager.providers.find(name);

    if (provider == _pluginsManager.providers.end())
        throw Exception("Object provider not found for object: " + name + ".");
    try {
        return provider->second->create(material, position, property);
    } catch (const std::exception &e) {
        throw Exception("Error while creating object: " + name + " - " + e.what() + ".");
    }
}

ObjectFactory::Exception::Exception(std::string message): _message(std::move(message)) {}

const char *ObjectFactory::Exception::what() const noexcept {
    return _message.c_str();
}
