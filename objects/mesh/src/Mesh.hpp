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
#include <sstream>
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

    /**
     * @brief Load a vertex
     * @param iss Input string stream
     */
    void _loadVertex(std::istringstream &iss);

    /**
     * @brief Load a face
     * @param iss Input string stream
     * @param line Line of the face
     */
    void _loadFace(std::istringstream &iss, std::string &line);

    /**
     * @brief Load a face point. Points are represented as tuples of 3 integers
     * @param iss 
     * @param point 
     */
    void _loadFacePoint(std::istringstream &iss, std::tuple<int, int, int> &point);

    /**
     * @brief Load a normal
     * @param iss Input string stream
     */
    void _loadNormal(std::istringstream &iss);

    /**
     * @brief Load a texture coordinate
     * @param iss Input string stream
     */
    void _loadTextureCoordinate(std::istringstream &iss);
};
