/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "types/math/Vector.hpp"

using namespace Raytracer::Common;

int main()
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);

    auto dot = u.dot(v);

    std::cout << dot + 10 << std::endl;
    return 0;
}
