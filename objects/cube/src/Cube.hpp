/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cube
*/

#pragma once

#include <vector>
#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

using namespace Raytracer::Common::Math;

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

    /// @brief Radius of the cube
    float _radius;

    /// @brief Faces of the cube
    std::vector<std::tuple<Common::Math::Point3D, Common::Math::Point3D, Common::Math::Point3D>> _faces;

    /// @brief Faces normals of the cube
    std::vector<std::tuple<Common::Math::Vector3D, Common::Math::Vector3D, Common::Math::Vector3D>> _facesNormals;

    /**
     * @brief Set the radius of the cube bounding box
     */
    void _setRadius();

    /**
     * @brief Check if the ray hit the cube
     * @param ray Ray to check
     * @return true if the ray hit the cube
     * @return false if the ray didn't hit the cube
     */
    bool _hitBoundingBox(const Ray &ray);

    /**
     * @brief Check if the origin is inside the cube bounding box
     * @param point Point to check
     * @return true if the point is inside the bounding box
     * @return false if the point is outside the bounding box
     */
    bool _isInsideBoundingBox(const Point3D &point);

    /**
     * @brief Check if the ray hit the cube
     * @param hitInfo Hit info to fill
     * @param ray Ray to check
     * @param point1 First point of the face
     * @param point2 Second point of the face
     * @param point3 Third point of the face
     * @param normal1 First normal of the face
     * @param normal2 Second normal of the face
     * @param normal3 Third normal of the face
     * @return true if the ray hit the cube
     * @return false if the ray didn't hit the cube
     */
    bool _intersect(HitInfo &hitInfo, const Ray &ray,
            const Point3D &point1, const Point3D &point2, const Point3D &point3,
            const Vector3D &normal1, const Vector3D &normal2, const Vector3D &normal3);
};
