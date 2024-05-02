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
#include "types/math/Vector.hpp"
#include "types/math/Point.hpp"
#include "types/graphics/Color.hpp"

typedef enum {
    DIRECTIONAL,
    AMBIENT
} emitter_type_e;

typedef struct {
    std::pair<unsigned, unsigned> resolution;
    Math::Point3D position;
    Math::Vector3D rotation;
    float fov;
} camera_config_t;

typedef struct {
    float emission_strength;
    emitter_type_e emission_type;
} material_emitter_config_t;

typedef struct {
    float reflectivity;
} material_absorber_config_t;

typedef union {
    material_emitter_config_t emitter;
    material_absorber_config_t absorber;
} material_properties_t;

typedef struct {
    std::string type;
    std::string name;
    Graphics::Color color;
    material_properties_t properties;
} material_config_t;

typedef struct {
    std::list<camera_config_t> cameras;
    std::list<material_config_t> materials;
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

        material_config_t _parseMaterial(const libconfig::Setting &setting);
        material_absorber_config_t _parseMaterialAbsorber(const libconfig::Setting &setting);
        material_emitter_config_t _parseMaterialEmitter(const libconfig::Setting &setting);
        Math::Vector3D _parseVector3D(const libconfig::Setting &setting);
        Math::Point3D _parsePoint3D(const libconfig::Setting &setting);
        Graphics::Color _parseColor(const libconfig::Setting &setting);
};
