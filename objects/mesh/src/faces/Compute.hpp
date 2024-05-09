/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Compute
*/

#pragma once

#include <vector>
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
         * @param points Points of the face
         * @param normals Normals of the face
         * @return true if the face is computed
         * @return false if the face is not computed
         */
        static bool _computeFace(HitInfo &hitInfo, const Ray &ray, const std::vector<Point3D> &points, const std::vector<Vector3D> &normals);
    };
}
