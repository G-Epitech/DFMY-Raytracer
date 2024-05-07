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
    std::cout << "Mesh loaded" << std::endl;
    for (auto &vertex : _vertices) {
        vertex.x += _position.x;
        vertex.y += _position.y;
        vertex.z += _position.z;
    }
    std::cout << "Mesh position set" << std::endl;
    for (auto &face : _triFaces) {
        std::cout << "Face" << std::endl;
        std::cout << std::get<0>(std::get<0>(face)) << " " << std::get<1>(std::get<0>(face)) << " " << std::get<2>(std::get<0>(face)) << std::endl;
        MeshFaces::TriFace::TriPoints points {
            _vertices[std::get<0>(std::get<0>(face)) - 1],
            _vertices[std::get<1>(std::get<0>(face)) - 1],
            _vertices[std::get<2>(std::get<0>(face)) - 1],
        };

        std::cout << points.p1 << " " << points.p2 << " " << points.p3 << std::endl;

        MeshFaces::TriFace::TriNormals normals {
            _normals[std::get<0>(std::get<1>(face)) - 1],
            _normals[std::get<1>(std::get<1>(face)) - 1],
            _normals[std::get<2>(std::get<1>(face)) - 1]
        };

        MeshFaces::TriFace::TriTextureCoordinates textureCoordinates {
            _textureCoordinates[std::get<0>(std::get<2>(face)) - 1],
            _textureCoordinates[std::get<1>(std::get<2>(face)) - 1],
            _textureCoordinates[std::get<2>(std::get<2>(face)) - 1]
        };

        MeshFaces::TriFace::Tri tri {
            points,
            normals,
            textureCoordinates
        };

        _faces.push_back(std::make_shared<MeshFaces::TriFace>(tri));
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
    std::ifstream file(filename);
    std::string
        line;
    std::vector<Common::Math::Point3D> vertices;
    std::vector<std::tuple<std::tuple<int, int, int>, std::tuple<int, int, int>, std::tuple<int, int, int>>> triFaces;
    std::vector<std::tuple<std::tuple<int, int, int>, std::tuple<int, int, int>, std::tuple<int, int, int>, std::tuple<int, int, int>>> quadFaces;
    std::vector<Common::Math::Vector3D> normals;
    std::vector<Common::Math::Point2D> textureCoords;

    if (!file.is_open())
        throw std::runtime_error("Could not open file: " + filename);

    while (std::getline(file, line)) {
        std::istringstream
            iss(line);
        std::string
            type;

        iss >> type;
        if (type == "v") {
            Common::Math::Point3D
                vertex;

            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (type == "f") {
            _loadFace(iss, line);
        } else if (type == "vn") {
            Common::Math::Vector3D
                normal;

            iss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if (type == "vt") {
            Common::Math::Point2D
                textureCoord;

            iss >> textureCoord.x >> textureCoord.y;
            textureCoords.push_back(textureCoord);
        }
    }

    _vertices = vertices;
    _triFaces = triFaces;
    _quadFaces = quadFaces;
    _normals = normals;
    _textureCoordinates = textureCoords;
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

        std::cout << std::get<0>(face1) << " " << std::get<1>(face1) << " " << std::get<2>(face1) << std::endl;
        std::cout << std::get<0>(face2) << " " << std::get<1>(face2) << " " << std::get<2>(face2) << std::endl;
        std::cout << std::get<0>(face3) << " " << std::get<1>(face3) << " " << std::get<2>(face3) << std::endl;
        std::cout << std::get<0>(face4) << " " << std::get<1>(face4) << " " << std::get<2>(face4) << std::endl;

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
}
