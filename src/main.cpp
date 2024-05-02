/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "types/math/Vector.hpp"

int main()
{
    Math::Vector3D u(1, 2, 3);
    Math::Vector3D v(4, 5, 6);

    auto dot = u.dot(v);

    std::cout << dot << std::endl;
    return 0;
}
