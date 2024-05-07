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

    auto pointEdge1 = _data.points.p2 - _data.points.p1;
    Vector3D edge1(pointEdge1.x, pointEdge1.y, pointEdge1.z);
    auto pointEdge2 = _data.points.p3 - _data.points.p1;
    Vector3D edge2(pointEdge2.x, pointEdge2.y, pointEdge2.z);
    auto normalVector = edge1.cross(edge2);
    auto pointAO = ray.origin - _data.points.p1;
    Vector3D ao(pointAO.x, pointAO.y, pointAO.z);
    auto dao = ao.cross(ray.direction);

    auto determinant = -ray.direction.dot(normalVector);
    auto invDot = 1.0 / determinant;

    auto dst = ao.dot(normalVector) * invDot;
    auto u = edge2.dot(dao) * invDot;
    auto v = -edge1.dot(dao) * invDot;
    auto w = 1 - u - v;

    if (determinant < std::numeric_limits<float>::epsilon() || u < 0 || v < 0 || w < 0)
        return hitInfo;

    hitInfo.didHit = true;
    hitInfo.distance = dst;
    auto vector = ray.direction * dst;
    hitInfo.hitPoint = ray.origin + Point3D(vector.x, vector.y, vector.z);
    hitInfo.normal = (_data.normals.n1 * w + _data.normals.n2 * u + _data.normals.n3 * v).normalize();

    return hitInfo;
}
