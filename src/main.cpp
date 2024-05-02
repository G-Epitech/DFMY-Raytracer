/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "config/Config.hpp"

int main(int ac, char **av)
{
    Config config;
    scene_config_t scene_config;

    try {
        scene_config = config.load(av[1]);
    } catch (Config::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    for (auto camera : scene_config.cameras) {
        std::cout << "Camera resolution: " << camera.resolution.first << "x" << camera.resolution.second << std::endl;
        std::cout << "Camera position: " << std::get<0>(camera.position) << ", " << std::get<1>(camera.position) << ", " << std::get<2>(camera.position) << std::endl;
        std::cout << "Camera rotation: " << std::get<0>(camera.rotation) << ", " << std::get<1>(camera.rotation) << ", " << std::get<2>(camera.rotation) << std::endl;
        std::cout << "Camera fov: " << camera.fov << std::endl;
    }
    return 0;
}
