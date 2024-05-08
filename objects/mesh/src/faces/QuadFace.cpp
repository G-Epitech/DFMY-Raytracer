/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** QuadFace
*/

#include <cmath>
#include "QuadFace.hpp"

using namespace Raytracer::Objects::MeshFaces;
using namespace Raytracer::Common::Math;

QuadFace::QuadFace(const Quad &points)
{
    _data = points;
}

HitInfo QuadFace::computeCollision(const Ray &ray)
{
    HitInfo hitInfo;

    auto& p1 = _data.points.p1;
    auto& p2 = _data.points.p2;
    auto& p3 = _data.points.p3;
    auto& p4 = _data.points.p4;
    auto& n1 = _data.normals.n1;
    auto& n2 = _data.normals.n2;
    auto& n3 = _data.normals.n3;
    auto& n4 = _data.normals.n4;

    if (_computeCollisionWithTriangle(ray, hitInfo, {p1, p2, p3}, {n1, n2, n3}))
        return hitInfo;
    _computeCollisionWithTriangle(ray, hitInfo, {p1, p3, p4}, {n1, n3, n4});
    return hitInfo;
}

bool _computeCollisionWithTriangle(const Ray &ray, HitInfo &hitInfo, const std::vector<Point3D> &points, const std::vector<Vector3D> &normals)
{
    if (points.size() != 3 || normals.size() != 3)
        return false;

    auto pointEdge1 = points[1] - points[0];
    Vector3D edge1(pointEdge1.x, pointEdge1.y, pointEdge1.z);
    auto pointEdge2 = points[2] - points[0];
    Vector3D edge2(pointEdge2.x, pointEdge2.y, pointEdge2.z);
    auto normalVector = edge1.cross(edge2);
    auto pointAO = ray.origin - points[0];
    Vector3D ao(pointAO.x, pointAO.y, pointAO.z);
    auto dao = ao.cross(ray.direction);

    auto determinant = -ray.direction.dot(normalVector);
    auto invDot = 1.0 / determinant;

    auto dst = ao.dot(normalVector) * invDot;
    auto u = edge2.dot(dao) * invDot;
    auto v = -edge1.dot(dao) * invDot;
    auto w = 1 - u - v;

    if (determinant < std::numeric_limits<float>::epsilon() || u < 0 || v < 0 || w < 0)
        return false;

    hitInfo.didHit = true;
    hitInfo.distance = dst;
    auto vector = ray.direction * dst;
    hitInfo.hitPoint = ray.origin + Point3D(vector.x, vector.y, vector.z);
    hitInfo.normal = (normals[0] * w + normals[1] * u + normals[2] * v).normalize();

    return true;
}
