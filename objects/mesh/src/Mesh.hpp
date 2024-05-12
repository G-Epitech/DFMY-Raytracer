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
#include "common/abstracts/AObject.hpp"
#include "common/interfaces/IObject.hpp"
#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class Mesh;
}

class Raytracer::Objects::Mesh : public Raytracer::Common::AObject {
public:

    /**
     * @brief Construct a new mesh object
     * @param name Name of the mest
     * @param material Material of the mesh
     * @param rotation Rotation of the mesh
     * @param position Position of the mesh
     * @param property Property of the mesh
     */
    Mesh(const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property);

    /**
     * @brief Destroy the mesh object
     */
    ~Mesh() = default;

    Common::Math::HitInfo computeCollision(const Common::Math::Ray &ray) override;

private:
    /// @brief Face point on the mesh. Can be a point of a triangle or a quadrilateral
    typedef std::tuple<int, int, int> FacePoint;

    /// @brief Triangle face
    typedef std::tuple<FacePoint, FacePoint, FacePoint> TriFace;

    /// @brief Quadrilateral face
    typedef std::tuple<FacePoint, FacePoint, FacePoint, FacePoint> QuadFace;

    /// @brief Array of vertices
    std::vector<Common::Math::Point3D> _vertices;

    /// @brief Array of normals
    std::vector<Common::Math::Vector3D> _normals;

    /// @brief Array of texture coordinates
    std::vector<Common::Math::Point2D> _textureCoordinates;

    /// @brief Array of faces
    std::vector<std::shared_ptr<MeshFaces::IFace>> _faces;

    /// @brief Array of trifaces
    std::vector<TriFace> _triFaces;

    /// @brief Array of quadfaces
    std::vector<QuadFace> _quadFaces;

    /// @brief Radius of the mesh
    float _radius;

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

    /**
     * @brief Load the triangles faces
     */
    void _loadTriangles();

    /**
     * @brief Load the quads faces
     */
    void _loadQuads();

    /**
     * @brief Check if the indexes are valid
     * @param point Point to check
     * @return true if the indexes are valid, false otherwise
     */
    bool _checkPointIndex(FacePoint &point);

    /**
     * @brief Check if the indexes of a triangle are valid
     * @param points Points of the triangle
     * @return true if the indexes are valid, false otherwise
     */
    bool _checkFaceIndexes(TriFace &points);

    /**
     * @brief Check if the indexes of a quadrilateral are valid
     * @param points Points of the quadrilateral
     * @return true if the indexes are valid, false otherwise
     */
    bool _checkFaceIndexes(QuadFace &points);

    /**
     * @brief Check if all the textures are set
     * @param points Points of the triangle
     * @return true if all the textures are set, false otherwise
     */
    bool _allTexturesAreSet(TriFace &points);

    /**
     * @brief Check if all the textures are set
     * @param points Points of the quadrilateral
     * @return true if all the textures are set, false otherwise
     */
    bool _allTexturesAreSet(QuadFace &points);

    /**
     * @brief Check if a ray collide with the mesh
     * @param ray Ray to check
     * @return true if the ray collide with the mesh, false otherwise
     */
    bool _collideSphere(const Raytracer::Common::Math::Ray &ray);

    /**
     * @brief Check if a point is inside the sphere
     * @param point Point to check
     * @return true if the point is inside the sphere, false otherwise
     */
    bool _isInsideSphere(const Raytracer::Common::Math::Point3D &point);

    /**
     * @brief Set the radius of the sphere
     */
    void _setSphereRadius();

    /**
     * @brief Get the center of the object
     * @return Center of the object
     */
    Point3D _getObjectCenter();

    /**
     * @brief Translate the object
     * @param translation Translation to apply
     */
    void _translateObject(const Point3D &translation);

};
