/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Compute
*/

#pragma once

#include "common/types/math/Ray.hpp"
#include "common/types/math/HitInfo.hpp"

using namespace Raytracer::Common::Math;

namespace Raytracer::Objects::MeshFaces {
    class Compute {
    public:

        /**
         * @brief Computea triangle face
         * @param hitInfo Hit info to fill
         * @param ray Ray to compute
         * @return true if the face is computed
         * @return false if the face is not computed
         */
        static bool computeFace(HitInfo &hitInfo, const Ray &ray,
            const Point3D &point1, const Point3D &point2, const Point3D &point3,
            const Vector3D &normal1, const Vector3D &normal2, const Vector3D &normal3);
    };
}
