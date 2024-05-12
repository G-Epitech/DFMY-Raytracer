/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** AObject
*/

#include "AObject.hpp"

using namespace Raytracer::Common;

AObject::AObject(
    const std::string &name,
    Common::Graphics::Material::Ptr material,
    const Common::Math::Vector3D &rotation,
    const Common::Math::Point3D &position) :
    _name(name),
    _material(material),
    _rotation(rotation),
    _position(position)
{
}

Graphics::Material::Ptr AObject::getMaterial()
{
    return _material;
}
