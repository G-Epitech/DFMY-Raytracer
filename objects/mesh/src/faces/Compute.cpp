/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Compute
*/

#include <limits>
#include "Compute.hpp"

using namespace Raytracer::Objects::MeshFaces;

const auto EPSILON = std::numeric_limits<float>::epsilon();

bool Compute::computeFace(HitInfo &hitInfo, const Ray &ray,
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

    auto rayOrigin = ray.origin;

    rayOrigin.x *= 1.0001;
    rayOrigin.y *= 1.0001;
    rayOrigin.z *= 1.0001;

    auto normalVector = edge1.cross(edge2);
    auto determinant = -(ray.direction.dot(normalVector));

    if (std::abs(determinant) < EPSILON)
        return false;

    Vector3D ao(
        rayOrigin.x - point1.x,
        rayOrigin.y - point1.y,
        rayOrigin.z - point1.z
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

    hitInfo.hitPoint.x = rayOrigin.x + (ray.direction.x * dst);
    hitInfo.hitPoint.y = rayOrigin.y + (ray.direction.y * dst);
    hitInfo.hitPoint.z = rayOrigin.z + (ray.direction.z * dst);
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
