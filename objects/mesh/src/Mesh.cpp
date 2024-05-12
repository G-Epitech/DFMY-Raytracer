/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** mesh
*/

#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <variant>
#include <tuple>
#include "Mesh.hpp"

using namespace Raytracer::Common;
using namespace Raytracer::Objects;
using namespace Math;

Point3D Mesh::_getObjectCenter() {
    Point3D center(0, 0, 0);

    for (auto &vertex: _vertices) {
        center.x += vertex.x;
        center.y += vertex.y;
        center.z += vertex.z;
    }
    center.x /= _vertices.size();
    center.y /= _vertices.size();
    center.z /= _vertices.size();
    return center;
}

void Mesh::_translateObject(const Point3D &translation) {
    for (auto &vertex: _vertices) {
        vertex.x -= translation.x;
        vertex.y -= translation.y;
        vertex.z -= translation.z;
    }
}

Mesh::Mesh(const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) :
        AObject(name, material, rotation, position)
{
    Raytracer::Common::MeshProperty prop = std::get<Raytracer::Common::MeshProperty>(property);
    auto filename = prop.filename;
    auto scale = prop.scale;

    _loadObj(filename);

    Point3D center = _getObjectCenter();
    _translateObject(center);
    for (auto &vertex : _vertices) {
        vertex.x *= scale;
        vertex.y *= scale;
        vertex.z *= scale;
        vertex.rotateX(_rotation.x);
        vertex.rotateY(_rotation.y);
        vertex.rotateZ(_rotation.z);
        vertex.x += _position.x;
        vertex.y += _position.y;
        vertex.z += _position.z;
    }
    Point3D invCenter(-center.x, -center.y, -center.z);
    _translateObject(invCenter);
    _setSphereRadius();

    _loadTriangles();
    _loadQuads();
}

void Mesh::_setSphereRadius() {
    for (auto &vertex: _vertices) {
        float distance = std::sqrt(std::pow(vertex.x, 2) + std::pow(vertex.y, 2) + std::pow(vertex.z, 2));
        if (distance > _radius)
            _radius = distance;
    }
}

HitInfo Mesh::computeCollision(const Ray &ray) {
    bool didHitOne = false;
    HitInfo hitInfo;
    HitInfo closesHitInfo;

    if (!_isInsideSphere(ray.origin) && !_collideSphere(ray))
        return closesHitInfo;
    for (auto &face: _faces) {
        face->computeCollision(ray, hitInfo);

        if (hitInfo.didHit) {
            if (!didHitOne) {
                closesHitInfo = hitInfo;
                didHitOne = true;
            } else if (hitInfo.distance < closesHitInfo.distance) {
                closesHitInfo = hitInfo;
            }
        }
    }
    closesHitInfo.hitColor = {
            .color = _material->color,
            .emissionStrength = _material->emissionStrength,
            .emissionColor = _material->emissionColor,
            .reflectivity = _material->reflectivity,
    };
    return closesHitInfo;
}

bool Mesh::_collideSphere(const Ray &ray) {
    Vector3D oc(
            ray.origin.x - _position.x,
            ray.origin.y - _position.y,
            ray.origin.z - _position.z
    );

    float a = ray.direction.dot(ray.direction);
    float b = 2.0 * oc.dot(ray.direction);
    float c = oc.dot(oc) - _radius * _radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    float distance = (-b - sqrt(discriminant)) / (2.0 * a);

    if (distance < 0)
        return false;
    return true;
}

bool Mesh::_isInsideSphere(const Point3D &point) {
    float distanceSquared = std::pow(point.x - _position.x, 2) +
                            std::pow(point.y - _position.y, 2) +
                            std::pow(point.z - _position.z, 2);
    float radiusSquared = std::pow(_radius, 2);
    return distanceSquared <= radiusSquared;
}

void Mesh::_loadObj(const std::string &filename) {
    std::string line;
    std::ifstream file(filename);

    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    while (std::getline(file, line)) {
        std::string type;
        std::istringstream iss(line);

        iss >> type;
        if (type == "v") {
            _loadVertex(iss);
        } else if (type == "f") {
            _loadFace(iss, line);
        } else if (type == "vn") {
            _loadNormal(iss);
        } else if (type == "vt") {
            _loadTextureCoordinate(iss);
        }
    }
}

void Mesh::_loadVertex(std::istringstream &iss) {
    Point3D vertex;

    iss >> vertex.x >> vertex.y >> vertex.z;
    _vertices.push_back(vertex);
}

void Mesh::_loadFace(std::istringstream &iss, std::string &line) {
    if (std::count(line.begin(), line.end(), ' ') == 3) {
        FacePoint point1, point2, point3;

        this->_loadFacePoint(iss, point1);
        this->_loadFacePoint(iss, point2);
        this->_loadFacePoint(iss, point3);

        _triFaces.push_back(std::make_tuple(point1, point2, point3));
    } else if (std::count(line.begin(), line.end(), ' ') == 4) {
        FacePoint point1, point2, point3, point4;

        this->_loadFacePoint(iss, point1);
        this->_loadFacePoint(iss, point2);
        this->_loadFacePoint(iss, point3);
        this->_loadFacePoint(iss, point4);

        _quadFaces.push_back(std::make_tuple(point1, point2, point3, point4));
    } else {
        std::cerr << "Invalid face: " << line << std::endl;
    }
}

void Mesh::_loadFacePoint(std::istringstream &iss, Mesh::FacePoint &point) {
    std::string pointStr;

    iss >> pointStr;
    std::replace(pointStr.begin(), pointStr.end(), '/', ' ');
    auto issPoint = std::istringstream(pointStr);
    issPoint >> std::get<0>(point) >> std::get<1>(point) >> std::get<2>(point);
    if (std::get<2>(point) == 0) {
        if (std::get<1>(point) == 0) {
            std::cerr << "Invalid face point: " << pointStr << std::endl;
            std::get<0>(point) = 0;
            std::get<1>(point) = 0;
            std::get<2>(point) = 0;
        } else {
            std::get<2>(point) = std::get<1>(point);
            std::get<1>(point) = 0;
        }
    }
}

void Mesh::_loadNormal(std::istringstream &iss) {
    Vector3D normal;

    iss >> normal.x >> normal.y >> normal.z;
    _normals.push_back(normal);
}

void Mesh::_loadTextureCoordinate(std::istringstream &iss) {
    Point2D textureCoord;

    iss >> textureCoord.x >> textureCoord.y;
    _textureCoordinates.push_back(textureCoord);
}

void Mesh::_loadTriangles() {
    for (auto &face: _triFaces) {

        if (!_checkFaceIndexes(face))
            continue;

        MeshFaces::TriFace::TriPoints points{
                _vertices[std::get<0>(std::get<0>(face)) - 1],
                _vertices[std::get<0>(std::get<1>(face)) - 1],
                _vertices[std::get<0>(std::get<2>(face)) - 1]
        };

        MeshFaces::TriFace::TriNormals normals{
                _normals[std::get<2>(std::get<0>(face)) - 1],
                _normals[std::get<2>(std::get<1>(face)) - 1],
                _normals[std::get<2>(std::get<2>(face)) - 1]
        };

        MeshFaces::TriFace::TriTextureCoordinates textureCoordinates;

        if (_allTexturesAreSet(face)) {
            textureCoordinates = {
                    _textureCoordinates[std::get<1>(std::get<0>(face)) - 1],
                    _textureCoordinates[std::get<1>(std::get<1>(face)) - 1],
                    _textureCoordinates[std::get<1>(std::get<2>(face)) - 1]
            };
        }

        MeshFaces::TriFace::Tri tri{
                points,
                normals,
                textureCoordinates
        };

        _faces.push_back(std::make_shared<MeshFaces::TriFace>(tri));
    }
}

void Mesh::_loadQuads() {
    for (auto &face: _quadFaces) {

        if (!_checkFaceIndexes(face))
            continue;

        MeshFaces::QuadFace::QuadPoints points{
                _vertices[std::get<0>(std::get<0>(face)) - 1],
                _vertices[std::get<0>(std::get<1>(face)) - 1],
                _vertices[std::get<0>(std::get<2>(face)) - 1],
                _vertices[std::get<0>(std::get<3>(face)) - 1]
        };

        MeshFaces::QuadFace::QuadNormals normals{
                _normals[std::get<2>(std::get<0>(face)) - 1],
                _normals[std::get<2>(std::get<1>(face)) - 1],
                _normals[std::get<2>(std::get<2>(face)) - 1],
                _normals[std::get<2>(std::get<3>(face)) - 1]
        };

        MeshFaces::QuadFace::QuadTextureCoordinates textureCoordinates;

        if (_allTexturesAreSet(face)) {
            textureCoordinates = {
                    _textureCoordinates[std::get<1>(std::get<0>(face)) - 1],
                    _textureCoordinates[std::get<1>(std::get<1>(face)) - 1],
                    _textureCoordinates[std::get<1>(std::get<2>(face)) - 1],
                    _textureCoordinates[std::get<1>(std::get<3>(face)) - 1]
            };
        }

        MeshFaces::QuadFace::Quad quad{
                points,
                normals,
                textureCoordinates
        };

        _faces.push_back(std::make_shared<MeshFaces::QuadFace>(quad));
    }
}

bool Mesh::_checkPointIndex(Mesh::FacePoint &point) {
    if (std::get<0>(point) <= 0 || std::get<0>(point) > _vertices.size())
        return false;
    if (std::get<1>(point) < 0 || std::get<1>(point) > _textureCoordinates.size())
        return false;
    if (std::get<2>(point) <= 0 || std::get<2>(point) > _normals.size())
        return false;
    return true;
}

bool Mesh::_checkFaceIndexes(Mesh::TriFace &points) {
    return _checkPointIndex(std::get<0>(points)) && _checkPointIndex(std::get<1>(points)) &&
           _checkPointIndex(std::get<2>(points));
}

bool Mesh::_checkFaceIndexes(Mesh::QuadFace &points) {
    return _checkPointIndex(std::get<0>(points)) && _checkPointIndex(std::get<1>(points)) &&
           _checkPointIndex(std::get<2>(points)) && _checkPointIndex(std::get<3>(points));
}

bool Mesh::_allTexturesAreSet(Mesh::TriFace &points) {
    return std::get<1>(std::get<0>(points)) > 0 && std::get<1>(std::get<1>(points)) > 0 &&
           std::get<1>(std::get<2>(points)) > 0;
}

bool Mesh::_allTexturesAreSet(Mesh::QuadFace &points) {
    return std::get<1>(std::get<0>(points)) > 0 && std::get<1>(std::get<1>(points)) > 0 &&
           std::get<1>(std::get<2>(points)) > 0 && std::get<1>(std::get<3>(points)) > 0;
}

const std::string Mesh::getType() noexcept
{
    return "Mesh";
}
