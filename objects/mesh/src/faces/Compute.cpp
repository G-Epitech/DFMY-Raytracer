/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Compute
*/

#include "Compute.hpp"

using namespace Raytracer::Objects::MeshFaces;

bool Compute::_computeFace(HitInfo &hitInfo, const Ray &ray, const std::vector<Point3D> &points, const std::vector<Vector3D> &normals)
{
    auto pointEdge1 = points[1] - points[0];
    Vector3D edge1(pointEdge1.x, pointEdge1.y, pointEdge1.z);
    auto pointEdge2 = points[2] - points[0];
    Vector3D edge2(pointEdge2.x, pointEdge2.y, pointEdge2.z);

    auto normalVector = edge1.cross(edge2);
    auto determinant = -(ray.direction.dot(normalVector));

    if (std::abs(determinant) < 1E-6)
        return false;

    auto pointAO = ray.origin - points[0];
    Vector3D ao(pointAO.x, pointAO.y, pointAO.z);

    auto dao = ao.cross(ray.direction);

    auto invDet = 1.0 / determinant;
    auto dst = ao.dot(normalVector) * invDet;

    if (dst < 0)
        return false;

    auto u = edge2.dot(dao) * invDet;
    auto v = (-(edge1.dot(dao))) * invDet;
    auto w = 1 - u - v;

    if (u >= 0 && v >= 0 && w >= 0) {
        hitInfo.didHit = true;
        hitInfo.distance = dst;
        auto vector = ray.direction * dst;
        hitInfo.hitPoint = ray.origin + Point3D(vector.x, vector.y, vector.z);
        hitInfo.normal = (normals[0] * w + normals[1] * u + normals[2] * v).normalize();
        return true;
    }
    return false;
}
