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

    if (Compute::computeFace(hitInfo, ray, p1, p2, p3, n1, n2, n3))
        return hitInfo;
    Compute::computeFace(hitInfo, ray, p1, p3, p4, n1, n3, n4);
    return hitInfo;
}
