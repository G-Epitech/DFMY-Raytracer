/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** QuadFace
*/

#include "QuadFace.hpp"

using namespace Raytracer::Objects::Mesh;

QuadFace::QuadFace(const Quad &points)
{
    _points = points;
}

Raytracer::Common::Math::HitInfo QuadFace::computeCollision(
    const Raytracer::Common::Math::Ray &ray)
{
    Raytracer::Common::Math::HitInfo hitInfo;
    Raytracer::Common::Math::Point3D e1P = _points.points.p2 - _points.points.p1;
    Raytracer::Common::Math::Vector3D e1 = Raytracer::Common::Math::Vector3D(e1P.x, e1P.y, e1P.z);
    Raytracer::Common::Math::Point3D e2P = _points.points.p3 - _points.points.p1;
    Raytracer::Common::Math::Vector3D e2 = Raytracer::Common::Math::Vector3D(e2P.x, e2P.y, e2P.z);
    Raytracer::Common::Math::Vector3D h = ray.direction.cross(e2);

    double a = e1.dot(h);

    if (a > -0.00001 && a < 0.00001)
        return hitInfo;

    double f = 1 / a;

    Raytracer::Common::Math::Point3D sP = ray.origin - _points.points.p1;
    Raytracer::Common::Math::Vector3D s = Raytracer::Common::Math::Vector3D(sP.x, sP.y, sP.z);

    double u = f * s.dot(h);

    if (u < 0.0 || u > 1.0)
        return hitInfo;

    Raytracer::Common::Math::Vector3D q = s.cross(e1);

    double v = f * ray.direction.dot(q);

    if (v < 0.0 || u + v > 1.0)
        return hitInfo;

    double t = f * e2.dot(q);

    if (t > 0.00001) {
        hitInfo.didHit = true;
        hitInfo.distance = t;
        hitInfo.normal = _points.normals.n1;
        auto intersectionNormal = ray.direction * t;
        Raytracer::Common::Math::Point3D hitPointData(intersectionNormal.x, intersectionNormal.y, intersectionNormal.z);
        hitInfo.hitPoint = ray.origin + hitPointData;
        // hitInfo.textureCoordinates = _points.textureCoordinates.t1;
    }
    return hitInfo;
}