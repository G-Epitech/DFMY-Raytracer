/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Cube
*/

#include <cmath>
#include <limits>
#include "Cube.hpp"

using namespace Raytracer::Objects;
using namespace Raytracer::Common;

const auto EPSILON = std::numeric_limits<float>::epsilon();

Cube::Cube(
    const std::string &name,
    Common::Graphics::Material::Ptr material,
    const Common::Math::Vector3D &rotation,
    const Common::Math::Point3D &position,
    const Common::ObjectProperty &property) :
    _name(name),
    _material(material),
    _rotation(rotation),
    _position(position)
{
    _size = std::get<Common::Math::Float3>(property);
    _radius = std::max(_size.x, std::max(_size.y, _size.z));

    _setRadius();

    auto widht = _size.x;
    auto depth = _size.y;
    auto height = _size.z;

    _faces.push_back(
        std::make_tuple(
            Math::Point3D(widht / 2.0, depth / 2.0, height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-widht / 2.0, -depth / 2.0, height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(widht / 2.0, depth / 2.0, -height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, -height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, -height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-widht / 2.0, -depth / 2.0, -height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, -height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, -height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(widht / 2.0, depth / 2.0, height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, height / 2.0),
            Math::Point3D(widht / 2.0, depth / 2.0, -height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(widht / 2.0, -depth / 2.0, -height / 2.0),
            Math::Point3D(widht / 2.0, depth / 2.0, -height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-widht / 2.0, depth / 2.0, height / 2.0),
            Math::Point3D(-widht / 2.0, -depth / 2.0, height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, -height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-widht / 2.0, -depth / 2.0, -height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, -height / 2.0),
            Math::Point3D(-widht / 2.0, -depth / 2.0, height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(widht / 2.0, depth / 2.0, height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, height / 2.0),
            Math::Point3D(widht / 2.0, depth / 2.0, -height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-widht / 2.0, depth / 2.0, -height / 2.0),
            Math::Point3D(widht / 2.0, depth / 2.0, -height / 2.0),
            Math::Point3D(-widht / 2.0, depth / 2.0, height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(widht / 2.0, -depth / 2.0, height / 2.0),
            Math::Point3D(-widht / 2.0, -depth / 2.0, height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, -height / 2.0)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-widht / 2.0, -depth / 2.0, -height / 2.0),
            Math::Point3D(widht / 2.0, -depth / 2.0, -height / 2.0),
            Math::Point3D(-widht / 2.0, -depth / 2.0, height / 2.0)
        )
    );

    for (auto &face : _faces) {
        auto &point1 = std::get<0>(face);
        auto &point2 = std::get<1>(face);
        auto &point3 = std::get<2>(face);

        point1.rotateX(rotation.x);
        point1.rotateY(rotation.y);
        point1.rotateZ(rotation.z);

        point1.x += position.x;
        point1.y += position.y;
        point1.z += position.z;

        point2.rotateX(rotation.x);
        point2.rotateY(rotation.y);
        point2.rotateZ(rotation.z);

        point2.x += position.x;
        point2.y += position.y;
        point2.z += position.z;

        point3.rotateX(rotation.x);
        point3.rotateY(rotation.y);
        point3.rotateZ(rotation.z);

        point3.x += position.x;
        point3.y += position.y;
        point3.z += position.z;

    }

    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, 0, 1),
            Math::Vector3D(0, 0, 1),
            Math::Vector3D(0, 0, 1)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, 0, 1),
            Math::Vector3D(0, 0, 1),
            Math::Vector3D(0, 0, 1)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, 0, -1),
            Math::Vector3D(0, 0, -1),
            Math::Vector3D(0, 0, -1)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, 0, -1),
            Math::Vector3D(0, 0, -1),
            Math::Vector3D(0, 0, -1)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(1, 0, 0),
            Math::Vector3D(1, 0, 0),
            Math::Vector3D(1, 0, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(1, 0, 0),
            Math::Vector3D(1, 0, 0),
            Math::Vector3D(1, 0, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(-1, 0, 0),
            Math::Vector3D(-1, 0, 0),
            Math::Vector3D(-1, 0, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(-1, 0, 0),
            Math::Vector3D(-1, 0, 0),
            Math::Vector3D(-1, 0, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, 1, 0),
            Math::Vector3D(0, 1, 0),
            Math::Vector3D(0, 1, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, 1, 0),
            Math::Vector3D(0, 1, 0),
            Math::Vector3D(0, 1, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, -1, 0),
            Math::Vector3D(0, -1, 0),
            Math::Vector3D(0, -1, 0)
        )
    );
    _facesNormals.push_back(
        std::make_tuple(
            Math::Vector3D(0, -1, 0),
            Math::Vector3D(0, -1, 0),
            Math::Vector3D(0, -1, 0)
        )
    );
}

void Cube::_setRadius()
{
    _radius = std::max(_size.x, std::max(_size.y, _size.z));
}

bool Cube::_intersect(HitInfo &hitInfo, const Ray &ray,
            const Point3D &point1, const Point3D &point2, const Point3D &point3,
            const Vector3D &normal1, const Vector3D &normal2, const Vector3D &normal3)
{
    Vector3D edge1(
        point2.x - point1.x,
        point2.y - point1.y,
        point2.z - point1.z
    );
    Vector3D edge2(
        point3.x - point1.x,
        point3.y - point1.y,
        point3.z - point1.z
    );

    auto normalVector = edge1.cross(edge2);
    auto determinant = -(ray.direction.dot(normalVector));

    if (std::abs(determinant) < EPSILON)
        return false;

    Vector3D ao(
        ray.origin.x - point1.x,
        ray.origin.y - point1.y,
        ray.origin.z - point1.z
    );

    auto dao = ao.cross(ray.direction);

    auto invDet = 1.0 / determinant;
    auto dst = ao.dot(normalVector) * invDet;

    if (dst < 0)
        return false;

    auto u = edge2.dot(dao) * invDet;
    if (u < 0) {
        return false;
    }

    auto v = (-(edge1.dot(dao))) * invDet;
    if (v < 0) {
        return false;
    }

    auto w = 1 - u - v;
    if (w < 0) {
        return false;
    }

    hitInfo.hitPoint.x = (ray.origin.x + (ray.direction.x * dst));
    hitInfo.hitPoint.y = (ray.origin.y + (ray.direction.y * dst));
    hitInfo.hitPoint.z = (ray.origin.z + (ray.direction.z * dst));

    if (std::abs(ray.origin.x - hitInfo.hitPoint.x) < 0.0001 &&
        std::abs(ray.origin.y - hitInfo.hitPoint.y) < 0.0001 &&
        std::abs(ray.origin.z - hitInfo.hitPoint.z) < 0.0001) {
            return false;
        }

    hitInfo.didHit = true;
    hitInfo.distance = dst;
    hitInfo.normal = (normal1 * w + normal2 * u + normal3 * v).normalize();

    return true;
}

Math::HitInfo Cube::computeCollision(const Math::Ray &ray)
{
    Math::HitInfo hitInfo;
    Math::HitInfo closestHitInfo;

    if (!_isInsideBoundingBox(ray.origin) && !_hitBoundingBox(ray))
        return closestHitInfo;
    for (int i = 0; i < _faces.size(); i++) {
        auto &face = _faces[i];
        auto &normal = _facesNormals[i];
        auto &point1 = std::get<0>(face);
        auto &point2 = std::get<1>(face);
        auto &point3 = std::get<2>(face);
        auto &normal1 = std::get<0>(normal);
        auto &normal2 = std::get<1>(normal);
        auto &normal3 = std::get<2>(normal);

        if (_intersect(hitInfo, ray, point1, point2, point3, normal1, normal2, normal3)) {
            if (!closestHitInfo.didHit || hitInfo.distance < closestHitInfo.distance) {
                closestHitInfo = hitInfo;
            }
        }
    }
    closestHitInfo.hitColor = {
        .color = _material->color,
        .emissionStrength = _material->emissionStrength,
        .emissionColor = _material->emissionColor,
        .reflectivity = _material->reflectivity,
    };

    return closestHitInfo;
}

bool Cube::_hitBoundingBox(const Ray &ray)
{
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

bool Cube::_isInsideBoundingBox(const Point3D &point)
{
    float distanceSquared = std::pow(point.x - _position.x, 2) +
                            std::pow(point.y - _position.y, 2) +
                            std::pow(point.z - _position.z, 2);
    float radiusSquared = std::pow(_radius, 2);
    return distanceSquared <= radiusSquared;
}

Graphics::Material::Ptr Cube::getMaterial()
{
    return _material;
}
