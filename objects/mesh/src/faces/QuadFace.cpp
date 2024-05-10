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
    std::vector<Point3D> pointsTriangle1 = {p1, p2, p3};
    std::vector<Point3D> pointsTriangle2 = {p1, p3, p4};
    std::vector<Vector3D> normalsTriangle1 = {n1, n2, n3};
    std::vector<Vector3D> normalsTriangle2 = {n1, n3, n4};

    if (_computeCollisionWithTriangle(ray, hitInfo, pointsTriangle1, normalsTriangle1))
        return hitInfo;
    _computeCollisionWithTriangle(ray, hitInfo, pointsTriangle2, normalsTriangle2);
    return hitInfo;
}

bool QuadFace::_computeCollisionWithTriangle(const Ray &ray, HitInfo &hitInfo, const std::vector<Point3D> &points, const std::vector<Vector3D> &normals)
{
    // if (points.size() != 3 || normals.size() != 3)
    //     return false;

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
        hitInfo.normal = (_data.normals.n1 * w + _data.normals.n2 * u + _data.normals.n3 * v).normalize();
        return true;
    }
    return false;
}
