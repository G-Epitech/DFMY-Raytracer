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
    auto widht = _size.x;
    auto height = _size.y;
    auto depth = _size.z;

    _faces.push_back(
        std::make_tuple(
            Math::Point3D(10, 10, 10),
            Math::Point3D(-10, 10, 10),
            Math::Point3D(10, -10, 10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-10, -10, 10),
            Math::Point3D(10, -10, 10),
            Math::Point3D(-10, 10, 10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(10, 10, -10),
            Math::Point3D(-10, 10, -10),
            Math::Point3D(10, -10, -10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-10, -10, -10),
            Math::Point3D(10, -10, -10),
            Math::Point3D(-10, 10, -10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(10, 10, 10),
            Math::Point3D(10, -10, 10),
            Math::Point3D(10, 10, -10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(10, -10, -10),
            Math::Point3D(10, 10, -10),
            Math::Point3D(10, -10, 10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-10, 10, 10),
            Math::Point3D(-10, -10, 10),
            Math::Point3D(-10, 10, -10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-10, -10, -10),
            Math::Point3D(-10, 10, -10),
            Math::Point3D(-10, -10, 10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(10, 10, 10),
            Math::Point3D(-10, 10, 10),
            Math::Point3D(10, 10, -10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-10, 10, -10),
            Math::Point3D(10, 10, -10),
            Math::Point3D(-10, 10, 10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(10, -10, 10),
            Math::Point3D(-10, -10, 10),
            Math::Point3D(10, -10, -10)
        )
    );
    _faces.push_back(
        std::make_tuple(
            Math::Point3D(-10, -10, -10),
            Math::Point3D(10, -10, -10),
            Math::Point3D(-10, -10, 10)
        )
    );

    for (auto &face : _faces) {
        auto &point1 = std::get<0>(face);
        auto &point2 = std::get<1>(face);
        auto &point3 = std::get<2>(face);

        point1.x += position.x;
        point1.y += position.y;
        point1.z += position.z;

        point2.x += position.x;
        point2.y += position.y;
        point2.z += position.z;

        point3.x += position.x;
        point3.y += position.y;
        point3.z += position.z;

        // point1.x = point1.x * widht;
        // point1.y = point1.y * height;
        // point1.z = point1.z * depth;

        // point2.x = point2.x * widht;
        // point2.y = point2.y * height;
        // point2.z = point2.z * depth;

        // point3.x = point3.x * widht;
        // point3.y = point3.y * height;
        // point3.z = point3.z * depth;
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

bool intersect(HitInfo &hitInfo, const Ray &ray,
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

    hitInfo.didHit = true;
    hitInfo.distance = dst;
    hitInfo.hitPoint.x = ray.origin.x + (ray.direction.x * dst);
    hitInfo.hitPoint.y = ray.origin.y + (ray.direction.y * dst);
    hitInfo.hitPoint.z = ray.origin.z + (ray.direction.z * dst);
    hitInfo.normal = (normal1 * w + normal2 * u + normal3 * v).normalize();
    return true;
}

Math::Vector3D findNormal(const Math::Point3D &vmin, const Math::Point3D &vmax, const Math::Point3D &hitPoint)
{
    Math::Point3D c(
        (vmax.x + vmin.x) / 2,
        (vmax.y + vmin.y) / 2,
        (vmax.z + vmin.z) / 2
    );
    auto p = hitPoint - c;
    Math::Point3D d(
        (vmin.x - vmax.x) / 2,
        (vmin.y - vmax.y) / 2,
        (vmin.z - vmax.z) / 2
    );
    auto bias = 1.01;

    return Math::Vector3D(
        static_cast<float>(static_cast<int>(p.x / std::abs(d.x) * bias)),
        static_cast<float>(static_cast<int>(p.y / std::abs(d.y) * bias)),
        static_cast<float>(static_cast<int>(p.z / std::abs(d.z) * bias))
    ).normalize();
}

Math::HitInfo Cube::computeCollision(const Math::Ray &ray)
{
    Math::HitInfo hitInfo;

    auto invdir = Math::Vector3D(1.0f / ray.direction.x, 1.0f / ray.direction.y, 1.0f / ray.direction.z);
    auto rayOrigin = ray.origin - _position;

    auto tmin = (-_size.x - rayOrigin.x) * invdir.x;
    auto tmax = (_size.x - rayOrigin.x) * invdir.x;

    if (tmin > tmax)
        std::swap(tmin, tmax);

    auto tymin = (-_size.y - rayOrigin.y) * invdir.y;
    auto tymax = (_size.y - rayOrigin.y) * invdir.y;

    if (tymin > tymax)
        std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) {
        hitInfo.didHit = false;
        return hitInfo;
    }

    if (tymin > tmin)
        tmin = tymin;
    
    if (tymax < tmax)
        tmax = tymax;
    
    auto tzmin = (-_size.z - rayOrigin.z) * invdir.z;
    auto tzmax = (_size.z - rayOrigin.z) * invdir.z;

    if (tzmin > tzmax)
        std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return hitInfo;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;
    
    if (tmax < 0)
        return hitInfo;
    
    if (tmin < 0)
        return hitInfo;

    hitInfo.didHit = true;
    hitInfo.distance = tmin;
    hitInfo.hitPoint.x = (rayOrigin.x + (ray.direction.x * tmin));
    hitInfo.hitPoint.y = (rayOrigin.y + (ray.direction.y * tmin));
    hitInfo.hitPoint.z = (rayOrigin.z + (ray.direction.z * tmin));

    hitInfo.normal = findNormal(
        Math::Point3D(-_size.x, -_size.y, -_size.z),
        Math::Point3D(_size.x, _size.y, _size.z),
        hitInfo.hitPoint
    );
    hitInfo.hitColor = {
        .color = _material->color,
        .emissionStrength = _material->emissionStrength,
        .emissionColor = _material->emissionColor
    };

    return hitInfo;
}

Graphics::Material::Ptr Cube::getMaterial()
{
    return _material;
}
