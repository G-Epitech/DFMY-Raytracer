/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** TriFace
*/

#include "TriFace.hpp"

using namespace Raytracer::Objects::MeshFaces;

TriFace::TriFace(const Tri &points)
{
    this->points = points;
}

Raytracer::Common::Math::HitInfo TriFace::computeCollision(
    const Raytracer::Common::Math::Ray &ray)
{
    Raytracer::Common::Math::HitInfo hitInfo;
    // Raytracer::Common::Math::Vector3D edge1 = this->points.p2 - this->points.p1;
    // Raytracer::Common::Math::Vector3D edge2 = this->points.p3 - this->points.p1;
    // Raytracer::Common::Math::Vector3D h = ray.direction.crossProduct(edge2);
    // float a = edge1.dotProduct(h);
    // if (a > -0.00001 && a < 0.00001)
    //     return hitInfo;
    // float f = 1 / a;
    // Raytracer::Common::Math::Vector3D s = ray.origin - this->points.p1;
    // float u = f * s.dotProduct(h);
    // if (u < 0 || u > 1)
    //     return hitInfo;
    // Raytracer::Common::Math::Vector3D q = s.crossProduct(edge1);
    // float v = f * ray.direction.dotProduct(q);
    // if (v < 0 || u + v > 1)
    //     return hitInfo;
    // float t = f * edge2.dotProduct(q);
    // if (t > 0.00001) {
    //     hitInfo.hit = true;
    //     hitInfo.t = t;
    //     hitInfo.hitPoint = ray.origin + ray.direction * t;
    //     hitInfo.normal = edge1.crossProduct(edge2).normalize();
    // }
    return hitInfo;
}
