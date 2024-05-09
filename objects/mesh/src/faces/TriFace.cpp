/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** TriFace
*/

#include <limits>
#include "TriFace.hpp"

using namespace Raytracer::Objects::MeshFaces;
using namespace Raytracer::Common::Math;

TriFace::TriFace(const Tri &points)
{
    this->_data = points;
}

Raytracer::Common::Math::HitInfo TriFace::computeCollision(
    const Raytracer::Common::Math::Ray &ray)
{
    HitInfo hitInfo;

    auto& p1 = this->_data.points.p1;
    auto& p2 = this->_data.points.p2;
    auto& p3 = this->_data.points.p3;

    if (_computeFace(hitInfo, ray, {p1, p2, p3}))
        return hitInfo;
    if (_computeFace(hitInfo, ray, {p1, p3, p2}))
        return hitInfo;
    if (_computeFace(hitInfo, ray, {p2, p3, p1}))
        return hitInfo;
    if (_computeFace(hitInfo, ray, {p2, p1, p3}))
        return hitInfo;
    if (_computeFace(hitInfo, ray, {p3, p1, p2}))
        return hitInfo;
    if (_computeFace(hitInfo, ray, {p3, p2, p1}))
        return hitInfo;
    return hitInfo;
}

bool TriFace::_computeFace(Common::Math::HitInfo &hitInfo, const Common::Math::Ray &ray, const std::vector<Common::Math::Point3D> &points)
{
    auto pointEdge1 = points[1] - points[0];
    Vector3D edge1(pointEdge1.x, pointEdge1.y, pointEdge1.z);
    auto pointEdge2 = points[2] - points[0];
    Vector3D edge2(pointEdge2.x, pointEdge2.y, pointEdge2.z);
    auto normalVector = edge1.cross(edge2);

    auto determinant = -(ray.direction.dot(normalVector));

    auto pointAO = ray.origin - points[0];
    Vector3D ao(pointAO.x, pointAO.y, pointAO.z);
    auto dao = ao.cross(ray.direction);

    if (std::abs(determinant) < 1E-6)
        return false;
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
        // hitInfo.normal = (_data.normals.n1 * w + _data.normals.n2 * u + _data.normals.n3 * v).normalize();
        return true;
    }
    return false;
}
