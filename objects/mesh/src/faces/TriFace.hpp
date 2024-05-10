/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** TriFace
*/

#pragma once

#include <vector>
#include "Compute.hpp"
#include "interfaces/IFace.hpp"

using namespace Raytracer::Common::Math;

namespace Raytracer::Objects::MeshFaces {
    /// @brief Representing a tri face
    class TriFace : public IFace {
    public:
        /// @brief Representing tri points
        typedef struct {
            /// @brief P1 point
            Common::Math::Point3D p1;
            /// @brief P2 point
            Common::Math::Point3D p2;
            /// @brief P3 point
            Common::Math::Point3D p3;
        } TriPoints;

        /// @brief Representing tri normals points
        typedef struct {
            /// @brief N1 point
            Common::Math::Vector3D n1;
            /// @brief N2 point
            Common::Math::Vector3D n2;
            /// @brief N3 point
            Common::Math::Vector3D n3;
        } TriNormals;

        /// @brief Representing tri texture coordinates
        typedef struct {
            /// @brief T1 point
            Common::Math::Point2D t1;
            /// @brief T2 point
            Common::Math::Point2D t2;
            /// @brief T3 point
            Common::Math::Point2D t3;
        } TriTextureCoordinates;

        /// @brief Representing a tri
        typedef struct {
            /// @brief Points of the tri
            TriPoints points;
            /// @brief Normals of the tri
            TriNormals normals;
            /// @brief Texture coordinates of the tri
            TriTextureCoordinates textureCoordinates;
        } Tri;

        /**
         * @brief Construct a new Tri Face object
         * @param points Points of the tri
         */
        TriFace(const Tri &points);

        /**
         * @brief Destroy the Tri Face object
         */
        ~TriFace() = default;

        void computeCollision(const Ray &ray, HitInfo &hitInfo) override;

    private:
        /// @brief Points of the triangle
        Tri _data;
    };
}