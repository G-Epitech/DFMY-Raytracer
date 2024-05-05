/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include "config/Config.hpp"

int main(int ac, char **av)
{
    Raytracer::Core::Config::SceneConfig scene_config;

    try {
        scene_config = Raytracer::Core::Config::load(av[1]);
    } catch (Raytracer::Core::Config::Exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
