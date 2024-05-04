/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "types/math/Vector.hpp"
#include "types/rendering/Camera.hpp"

using namespace Raytracer::Common;
using namespace Raytracer::Core::Rendering;

int main()
{
    Camera::Config camConfig = {
            .name = "Main camera",
            .screen = {
                    .size = { .width = 1920, .height = 1080 },
                    .origin = Math::Point3D(0, 0, 0)
            },
            .position = Math::Point3D(0, 0, 540),
            .direction = Math::Vector3D(1, 0, -1),
            .fov = 10
    };
    Camera camera(camConfig);
    std::vector<Raytracer::Graphics::IObject> objects;

    camera.compute(COMPUTE_THREADS, objects);
    for (auto& thread : camera._threads) {
        thread.join();
    }
    return 0;
}
