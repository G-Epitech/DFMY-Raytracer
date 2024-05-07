/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** mesh
*/

#pragma once

#include <map>
#include <vector>
#include <memory>
#include "interfaces/IFace.hpp"
#include "faces/TriFace.hpp"
#include "faces/QuadFace.hpp"
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

private:
    /// @brief Material of the mesh
    Common::Graphics::Material::Ptr _material;

    /// @brief Position of the mesh
    const Common::Math::Point3D _position;

    /// @brief Array of vertices
    std::vector<Common::Math::Point3D> _vertices;

    /// @brief Array of trifaces
    std::vector<std::tuple<std::tuple<int, int, int>, std::tuple<int, int, int>, std::tuple<int, int, int>>> _triFaces;

    /// @brief Array of quadfaces
    std::vector<std::tuple<std::tuple<int, int, int>, std::tuple<int, int, int>, std::tuple<int, int, int>, std::tuple<int, int, int>>> _quadFaces;

    /// @brief Array of normals
    std::vector<Common::Math::Vector3D> _normals;

    /// @brief Array of texture coordinates
    std::vector<Common::Math::Point2D> _textureCoordinates;

    /// @brief Array of faces
    std::vector<std::shared_ptr<MeshFaces::IFace>> _faces;

    /**
     * @brief Load the obj file
     * @param filename Filename of the obj file
     */
    void _loadObj(const std::string &filename);

};
