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
        std::cout << "Camera position: " << camera.position.x << ", " << camera.position.y << ", " << camera.position.z << std::endl;
        std::cout << "Camera rotation: " << camera.rotation.x << ", " << camera.rotation.y << ", " << camera.rotation.z << std::endl;
        std::cout << "Camera fov: " << camera.fov << std::endl;
    }
    for (auto material : scene_config.materials) {
        std::cout << "Material name: " << material.name << std::endl;
        std::cout << "Material color: " << material.objectColor.r << ", " << material.objectColor.g << ", " << material.objectColor.b << std::endl;
        std::cout << "Material emission color: " << material.emissionColor.r << ", " << material.emissionColor.g << ", " << material.emissionColor.b << std::endl;
        std::cout << "Material specular color: " << material.specularColor.r << ", " << material.specularColor.g << ", " << material.specularColor.b << std::endl;
        std::cout << "Material reflectivity: " << material.reflectivity << std::endl;
        std::cout << "Material emission strength: " << material.emissionStrength << std::endl;
    }
    return 0;
}
