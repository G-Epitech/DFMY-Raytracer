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
    auto pointEdge1 = point2 - point1;
    Vector3D edge1(pointEdge1.x, pointEdge1.y, pointEdge1.z);
    auto pointEdge2 = point3 - point1;
    Vector3D edge2(pointEdge2.x, pointEdge2.y, pointEdge2.z);

    auto normalVector = edge1.cross(edge2);
    auto determinant = -(ray.direction.dot(normalVector));

    if (std::abs(determinant) < EPSILON)
        return false;

    auto pointAO = ray.origin - point1;
    Vector3D ao(pointAO.x, pointAO.y, pointAO.z);

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
    if (v < 0)
        return false;
    auto w = 1 - u - v;
    if (w < 0)
        return false;

    hitInfo.didHit = true;
    hitInfo.distance = dst;
    auto vector = ray.direction * dst;
    hitInfo.hitPoint.x = ray.origin.x + vector.x;
    hitInfo.hitPoint.y = ray.origin.y + vector.y;
    hitInfo.hitPoint.z = ray.origin.z + vector.z;
    hitInfo.normal = (normal1 * w + normal2 * u + normal3 * v).normalize();
    return true;
}
