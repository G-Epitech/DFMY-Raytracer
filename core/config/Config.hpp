/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** Config
*/

#pragma once

#include <libconfig.h++>
#include <iostream>
#include <list>
#include <tuple>
#include <vector>
#include <variant>
#include "types/math/Vector.hpp"
#include "types/math/Point.hpp"
#include "types/graphics/Color.hpp"

using namespace Raytracer::Common;

typedef struct {
    std::pair<unsigned, unsigned> resolution;
    Math::Point3D position;
    Math::Vector3D rotation;
    float fov;
} camera_config_t;

typedef struct {
    std::string name;
    Graphics::Color objectColor;
    Graphics::Color emissionColor;
    Graphics::Color specularColor;
    float reflectivity;
    float emissionStrength;
} material_config_t;

typedef struct {
    float radius;
} object_sphere_config_t;

typedef struct {
    std::tuple<float, float, float> size;
} object_cube_config_t;

using object_properties_t = std::variant<object_cube_config_t, object_sphere_config_t>;

typedef struct {
    std::string type;
    std::string material;
    Math::Vector3D origin;
    object_properties_t properties;
} object_config_t;

typedef struct {
    std::list<camera_config_t> cameras;
    std::list<material_config_t> materials;
    std::list<object_config_t> objects;
} scene_config_t;

class Config {
    public:
        Config();
        ~Config() = default;

        scene_config_t load(const std::string &path);

        class Exception : public std::exception {
            public:
                explicit Exception(std::string const &message)
                    : _message(message) {}

                const char *what() const noexcept override {
                    return _message.c_str();
                }
                const std::string &getMessage() const {
                    return _message;
                }
            private:
                std::string _message;
        };
    private:
        std::list<camera_config_t> _loadCameras(const libconfig::Setting &root);
        std::list<material_config_t> _loadMaterials(const libconfig::Setting &root);
        std::list<object_config_t> _loadObjects(const libconfig::Setting &root);

        material_config_t _parseMaterial(const libconfig::Setting &setting);
        object_config_t _parseObject(const libconfig::Setting &setting);
        object_sphere_config_t _parseSphere(const libconfig::Setting &setting);
        object_cube_config_t _parseCube(const libconfig::Setting &setting);
        Math::Vector3D _parseVector3D(const libconfig::Setting &setting);
        Math::Point3D _parsePoint3D(const libconfig::Setting &setting);
        Graphics::Color _parseColor(const libconfig::Setting &setting);
        std::tuple<float, float, float> _parseTuple3f(const libconfig::Setting &setting, const std::string (&keys)[3]);

        void _settingHasValidKeys(const std::string &prop, const libconfig::Setting &setting,
            const std::vector<std::string> &keys);
};
