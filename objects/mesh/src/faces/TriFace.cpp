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
    auto& n1 = this->_data.normals.n1;
    auto& n2 = this->_data.normals.n2;
    auto& n3 = this->_data.normals.n3;

    if (Compute::computeFace(hitInfo, ray, p1, p2, p3, n1, n2, n3))
        return hitInfo;
    if (Compute::computeFace(hitInfo, ray, p1, p3, p2, n1, n3, n2))
        return hitInfo;
    if (Compute::computeFace(hitInfo, ray, p2, p3, p1, n2, n3, n1))
        return hitInfo;
    if (Compute::computeFace(hitInfo, ray, p2, p1, p3, n2, n1, n3))
        return hitInfo;
    if (Compute::computeFace(hitInfo, ray, p3, p1, p2, n3, n1, n2))
        return hitInfo;
    if (Compute::computeFace(hitInfo, ray, p3, p2, p1, n3, n2, n1))
        return hitInfo;
    return hitInfo;
}
