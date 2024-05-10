/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cube
*/

#pragma once

#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Cube;
}

class Raytracer::Objects::Cube : public Raytracer::Common::IObject {
public:

    /**
     * @brief Construct a new Cube object
     * @param name Name of the cube
     * @param material Material of the cube
     * @param rotation Rotation of the cube
     * @param position Position of the cube
     * @param property Property of the cube
     */
    Cube(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property);
    
    /**
     * @brief Destroy the Cube object
     */
    ~Cube() override = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

private:
    /// @brief Name of the cube
    const std::string &_name;

    /// @brief Material of the cube
    Common::Graphics::Material::Ptr _material;

    /// @brief Position of the cube
    const Common::Math::Point3D _position;

    /// @brief Rotation of the cube
    Common::Math::Vector3D _rotation;

    /// @brief Property of the cube
    Common::Math::Float3 _size;
};
