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
    hitPoint = Math::Point3D();
    normal = Math::Vector3D();
}
