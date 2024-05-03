/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** main
*/

#include <variant>
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
    std::cout << "-----" << std::endl;
    for (auto material : scene_config.materials) {
        std::cout << "Material name: " << material.name << std::endl;
        std::cout << "Material color: " << material.objectColor.r << ", " << material.objectColor.g << ", " << material.objectColor.b << std::endl;
        std::cout << "Material reflectivity: " << material.reflectivity << std::endl;
        for (auto emission : material.emissionDirections) {
            std::cout << "Emission direction color: " << emission.color.r << ", " << emission.color.g << ", " << emission.color.b << std::endl;
            std::cout << "Emission direction strength: " << emission.strength << std::endl;
            std::cout << "Emission direction vector: " << emission.vector.x << ", " << emission.vector.y << ", " << emission.vector.z << std::endl;
        }
    }
    std::cout << "-----" << std::endl;
    for (auto object : scene_config.objects) {
        std::cout << "Object type: " << object.type << std::endl;
        std::cout << "Object material: " << object.material << std::endl;
        std::cout << "Object origin: " << object.origin.x << ", " << object.origin.y << ", " << object.origin.z << std::endl;
        if (object.type == "cube") {
            auto cube = std::get<object_cube_config_t>(object.properties);
            std::cout << "Cube size: " << std::get<0>(cube.size) << ", " << std::get<1>(cube.size) << ", " << std::get<2>(cube.size)  <<std::endl;
        } else if (object.type == "sphere") {
            auto sphere = std::get<object_sphere_config_t>(object.properties);
            std::cout << "Sphere radius: " << sphere.radius << std::endl;
        }
        std::cout << "--" << std::endl;
    }
    return 0;
}
