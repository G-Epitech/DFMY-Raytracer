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
#include <tuple>
#include "Mesh.hpp"

using namespace Raytracer::Objects;

Mesh::Mesh(
    const Raytracer::Common::Graphics::Material::Ptr material,
    const Common::Math::Point3D &position,
    const Raytracer::Common::ObjectProperty &property) : _material(material), _position(position)
{
    auto filename = std::get<std::string>(property);

    std::cout << "Loading mesh: " << filename << std::endl;
    _loadObj(filename);
    for (auto &vertex : _vertices) {
        vertex.x += _position.x;
        vertex.y += _position.y;
        vertex.z += _position.z;
    }
    for (auto &face : _triFaces) {
        MeshFaces::TriFace::TriPoints points {
            _vertices[std::get<0>(std::get<0>(face)) - 1],
            _vertices[std::get<0>(std::get<1>(face)) - 1],
            _vertices[std::get<0>(std::get<2>(face)) - 1]
        };

        MeshFaces::TriFace::TriNormals normals {
            _normals[std::get<2>(std::get<0>(face)) - 1],
            _normals[std::get<2>(std::get<1>(face)) - 1],
            _normals[std::get<2>(std::get<2>(face)) - 1]
        };

        MeshFaces::TriFace::TriTextureCoordinates textureCoordinates {
            _textureCoordinates[std::get<1>(std::get<0>(face)) - 1],
            _textureCoordinates[std::get<1>(std::get<1>(face)) - 1],
            _textureCoordinates[std::get<1>(std::get<2>(face)) - 1]
        };

        MeshFaces::TriFace::Tri tri {
            points,
            normals,
            textureCoordinates
        };

        _faces.push_back(std::make_shared<MeshFaces::TriFace>(tri));
    }

    for (auto &face : _quadFaces) {
        MeshFaces::QuadFace::QuadPoints points {
            _vertices[std::get<0>(std::get<0>(face)) - 1],
            _vertices[std::get<0>(std::get<1>(face)) - 1],
            _vertices[std::get<0>(std::get<2>(face)) - 1],
            _vertices[std::get<0>(std::get<3>(face)) - 1]
        };

        MeshFaces::QuadFace::QuadNormals normals {
            _normals[std::get<2>(std::get<0>(face)) - 1],
            _normals[std::get<2>(std::get<1>(face)) - 1],
            _normals[std::get<2>(std::get<2>(face)) - 1],
            _normals[std::get<2>(std::get<3>(face)) - 1]
        };

        MeshFaces::QuadFace::QuadTextureCoordinates textureCoordinates {
            _textureCoordinates[std::get<1>(std::get<0>(face)) - 1],
            _textureCoordinates[std::get<1>(std::get<1>(face)) - 1],
            _textureCoordinates[std::get<1>(std::get<2>(face)) - 1],
            _textureCoordinates[std::get<1>(std::get<3>(face)) - 1]
        };

        MeshFaces::QuadFace::Quad quad {
            points,
            normals,
            textureCoordinates
        };

        _faces.push_back(std::make_shared<MeshFaces::QuadFace>(quad));
    }
}

Raytracer::Common::Math::HitInfo Mesh::computeCollision(const Raytracer::Common::Math::Ray &ray)
{
    Common::Math::HitInfo hitInfo;

    return hitInfo;
}

Raytracer::Common::Graphics::Material::Ptr Mesh::getMaterial()
{
    return _material;
}

void Mesh::_loadObj(const std::string &filename)
{
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

void Mesh::_loadVertex(std::istringstream &iss)
{
    Common::Math::Point3D vertex;

    iss >> vertex.x >> vertex.y >> vertex.z;
    _vertices.push_back(vertex);
}

void Mesh::_loadFace(std::istringstream &iss, std::string &line)
{
    if (std::count(line.begin(), line.end(), ' ') == 3) {
        std::tuple<int, int, int> face1, face2, face3;

        this->_loadFacePoint(iss, face1);
        this->_loadFacePoint(iss, face2);
        this->_loadFacePoint(iss, face3);

        _triFaces.push_back(std::make_tuple(face1, face2, face3));
    } else if (std::count(line.begin(), line.end(), ' ') == 4) {
        std::tuple<int, int, int> face1, face2, face3, face4;

        this->_loadFacePoint(iss, face1);
        this->_loadFacePoint(iss, face2);
        this->_loadFacePoint(iss, face3);
        this->_loadFacePoint(iss, face4);

        _quadFaces.push_back(std::make_tuple(face1, face2, face3, face4));
    } else {
        std::cerr << "Invalid face: " << line << std::endl;
    }
}

void Mesh::_loadFacePoint(std::istringstream &iss, std::tuple<int, int, int> &point)
{
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

void Mesh::_loadNormal(std::istringstream &iss)
{
    Common::Math::Vector3D normal;

    iss >> normal.x >> normal.y >> normal.z;
    _normals.push_back(normal);
}

void Mesh::_loadTextureCoordinate(std::istringstream &iss)
{
    Common::Math::Point2D textureCoord;

    iss >> textureCoord.x >> textureCoord.y;
    _textureCoordinates.push_back(textureCoord);
}
