/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Hit
*/

#include "HitInfo.hpp"

Math::HitInfo::HitInfo()
{
    didHit = false;
    distance = 0;
    hitPoint = Point3D(0, 0, 0);
    normal = Vector3D(0, 0, 0);
}
