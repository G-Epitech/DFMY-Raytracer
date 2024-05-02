/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Hit
*/

#include "Hit.hpp"

Graphics::HitInfo::HitInfo()
{
    didHit = false;
    distance = 0;
    hitPoint = Math::Point3D();
    normal = Math::Vector3D();
}
