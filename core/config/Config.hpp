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
#include <cstdlib>
#include <cxxabi.h>
#include "types/math/Vector.hpp"
#include "types/math/Point.hpp"
#include "types/graphics/Color.hpp"

using namespace Raytracer::Common;

typedef struct {
    std::pair<unsigned, unsigned> resolution;
    Math::Point3D position;
    Math::Vector3D rotation;
    float fov;
} CameraConfig;

typedef struct {
    Graphics::Color color;
    float strength;
    Math::Vector3D vector;
} EmissionDirectionConfig;

typedef struct {
    std::string name;
    Graphics::Color objectColor;
    std::vector<EmissionDirectionConfig> emissionDirections;
    float reflectivity;
} MaterialConfig;

typedef struct {
    float radius;
} SphereConfig;

typedef struct {
    std::tuple<float, float, float> size;
} CubeConfig;

using ObjectPropertiesConfig = std::variant<CubeConfig, SphereConfig>;

typedef struct {
    std::string type;
    std::string material;
    Math::Vector3D origin;
    ObjectPropertiesConfig properties;
} ObjectConfig;

typedef struct {
    std::list<CameraConfig> cameras;
    std::list<MaterialConfig> materials;
    std::list<ObjectConfig> objects;
} SceneConfig;

class Config {
    public:
        Config();
        ~Config() = default;

        SceneConfig load(const std::string &path);

        class Exception : public std::exception {
            public:
                explicit Exception(std::string const &message)
                    : _message("Config error: " + message) {}

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
        std::list<CameraConfig> _loadCameras(const libconfig::Setting &root);
        std::list<MaterialConfig> _loadMaterials(const libconfig::Setting &root);
        std::list<ObjectConfig> _loadObjects(const libconfig::Setting &root);

        MaterialConfig _parseMaterial(const libconfig::Setting &setting);
        std::vector<EmissionDirectionConfig> _parseEmissionDirections(const libconfig::Setting &setting);
        ObjectConfig _parseObject(const libconfig::Setting &setting);
        SphereConfig _parseSphere(const libconfig::Setting &setting);
        CubeConfig _parseCube(const libconfig::Setting &setting);
        Math::Vector3D _parseVector3D(const std::string propName, const libconfig::Setting &setting);
        Math::Point3D _parsePoint3D(const std::string propName, const libconfig::Setting &setting);
        Graphics::Color _parseColor(const libconfig::Setting &setting);
        std::tuple<float, float, float> _parseTuple3f(const std::string prop, const libconfig::Setting &setting, const std::vector<std::string> keys);

        void _settingHasValidKeys(const std::string prop, const libconfig::Setting &setting,
            const std::vector<std::string> &keys);

        template <typename T>
        void _lookupValueWrapper(const std::string prop, const libconfig::Setting &setting, T &value);

        template <typename T>
        std::string _typeName(T &value);
};
