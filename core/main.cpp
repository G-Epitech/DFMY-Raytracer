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
        std::cout << "Material type: " << material.type << std::endl;
        std::cout << "Material name: " << material.name << std::endl;
        std::cout << "Material color: " << static_cast<int>(material.color.r) << ", " << static_cast<int>(material.color.g) << ", " << static_cast<int>(material.color.b) << ", " << static_cast<int>(material.color.a) << std::endl;
        if (material.type == "emitter") {
            std::cout << "Material emission strength: " << material.properties.emitter.emission_strength << std::endl;
            std::cout << "Material emission type: " << material.properties.emitter.emission_type << std::endl;
        } else {
            std::cout << "Material reflectivity: " << material.properties.absorber.reflectivity << std::endl;
        }
    }
    return 0;
}
