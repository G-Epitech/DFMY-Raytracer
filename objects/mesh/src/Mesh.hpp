/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** mesh
*/

#pragma once

#include <map>
#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Mesh;
}

class Raytracer::Objects::Mesh : public Raytracer::Common::IObject {
public:

    /**
     * @brief Construct a new mesh object
     * @param material Material of the mesh
     * @param position Position of the mesh
     * @param property Property of the mesh
     */
    Mesh(const Common::Graphics::Material::Ptr material, const Common::Math::Point3D &position, const Common::ObjectProperty &property);

    /**
     * @brief Destroy the mesh object
     */
    ~Mesh() = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

    Common::Graphics::Material::Ptr getMaterial() override;

    /// @brief Representing quad points
    typedef struct {
        /// @brief P1 point
        Common::Math::Point3D p1;
        /// @brief P2 point
        Common::Math::Point3D p2;
        /// @brief P3 point
        Common::Math::Point3D p3;
        /// @brief P4 point
        Common::Math::Point3D p4;
    } QuadPoints;

    /// @brief Representing quad normals points
    typedef struct {
        /// @brief N1 point
        Common::Math::Vector3D n1;
        /// @brief N2 point
        Common::Math::Vector3D n2;
        /// @brief N3 point
        Common::Math::Vector3D n3;
        /// @brief N4 point
        Common::Math::Vector3D n4;
    } QuadNormals;

    /// @brief Representing quad texture coordinates
    typedef struct {
        /// @brief T1 point
        Common::Math::Point2D t1;
        /// @brief T2 point
        Common::Math::Point2D t2;
        /// @brief T3 point
        Common::Math::Point2D t3;
        /// @brief T4 point
        Common::Math::Point2D t4;
    } QuadTextureCoordinates;

    /// @brief Representing a quad
    typedef struct {
        /// @brief Points of the quad
        QuadPoints points;
        /// @brief Normals of the quad
        QuadNormals normals;
        /// @brief Texture coordinates of the quad
        QuadTextureCoordinates textureCoordinates;
    } Quad;

private:
    Common::Graphics::Material::Ptr _material;
    const Common::Math::Point3D _position;
};
