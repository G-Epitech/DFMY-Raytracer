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
#include "types/rendering/Screen.hpp"

using namespace Raytracer::Common;
using namespace Raytracer::Core;

namespace Raytracer::Core {
    class Config;
};

class Raytracer::Core::Config {
    public:
        /// @brief Camera configuration
        typedef struct {
            /// @brief Camera name
            std::string name;
            /// @brief Camera position
            Math::Point3D position;
            /// @brief Camera direction
            Math::Vector3D direction;
            /// @brief Camera field of view
            float fov;
            /// @brief Camera screen (already initialized)
            Rendering::Screen::Config screen;
        } CameraConfig;

        /// @brief Emission direction configuration
        typedef struct {
            /// @brief Light emission color
            Graphics::Color color;
            /// @brief Light emission strength
            float strength;
            /// @brief Light emission direction
            Math::Vector3D vector;
        } EmissionDirectionConfig;

        /// @brief Material configuration
        typedef struct {
            /// @brief Material name
            std::string name;
            /// @brief Material color for the object
            Graphics::Color color;
            /// @brief Material light emission directions
            std::vector<EmissionDirectionConfig> emissionDirections;
            /// @brief Material index of reflectivity
            float reflectivity;
        } MaterialConfig;

        /// @brief Configuration for a sphere object special properties
        typedef struct {
            /// @brief Sphere radius
            float radius;
        } SphereConfig;

        /// @brief Configuration for a cube object special properties
        typedef struct {
            /// @brief Cube size
            std::tuple<float, float, float> size;
        } CubeConfig;

        typedef std::variant<CubeConfig, SphereConfig> ObjectPropertiesConfig;

        /// @brief Object configuration
        typedef struct {
            /// @brief Object type (cube, sphere, etc.)
            std::string type;
            /// @brief The material name for the object
            std::string material;
            /// @brief Object origin
            Math::Vector3D origin;
            /// @brief Object special properties (cube, sphere, etc.)
            ObjectPropertiesConfig properties;
        } ObjectConfig;

        /// @brief Ambient light configuration
        typedef struct {
            /// @brief Ambient light color
            Graphics::Color color;
            /// @brief Ambient light strength
            float strength;
        } AmbientConfig;

        /// @brief Scene configuration
        typedef struct {
            /// @brief Scene name
            std::string name;
            /// @brief Ambient light configuration
            AmbientConfig ambient;
            /// @brief List of camera configurations
            std::list<CameraConfig> cameras;
            /// @brief List of material configurations
            std::list<MaterialConfig> materials;
            /// @brief List of object configurations
            std::list<ObjectConfig> objects;
        } SceneConfig;

        Config();
        ~Config() = default;

        /**
         * @brief Load a scene configuration from a file
         * @param path Path to the configuration file
         * @return SceneConfig
        */
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
        /**
         * @brief Load the name of the scene
         * @param path Path to the configuration file
         */
        std::string _loadName(const std::string &path);
        /**
         * @brief Load the scene ambient light configuration
         * @param root Root setting of the configuration file
         */
        AmbientConfig _loadAmbient(const libconfig::Setting &root);
        /**
         * @brief Load the scene cameras configuration
         * @param root Root setting of the configuration file
         */
        std::list<CameraConfig> _loadCameras(const libconfig::Setting &root);
        /**
         * @brief Load the scene materials configuration
         * @param root Root setting of the configuration file
         */
        std::list<MaterialConfig> _loadMaterials(const libconfig::Setting &root);
        /**
         * @brief Load the scene objects configuration
         * @param root Root setting of the configuration file
         */
        std::list<ObjectConfig> _loadObjects(const libconfig::Setting &root);

        /**
         * @brief Parse a camera group from the configuration
         * @param setting Setting of the camera group
         */
        Rendering::Screen::Config _parseCameraScreen(const libconfig::Setting &setting);
        /**
         * @brief Parse a material group from the configuration
         * @param setting Setting of the material group
         */
        MaterialConfig _parseMaterial(const libconfig::Setting &setting);
        /**
         * @brief Parse an emission direction group from the configuration
         * @param setting Setting of the emission direction group
         */
        std::vector<EmissionDirectionConfig> _parseEmissionDirections(const libconfig::Setting &setting);
        /**
         * @brief Parse an object group from the configuration
         * @param setting Setting of the object group
         */
        ObjectConfig _parseObject(const libconfig::Setting &setting);
        /**
         * @brief Parse special properties of a sphere from the configuration
         * @param setting Setting of the sphere group
         */
        SphereConfig _parseSphere(const libconfig::Setting &setting);
        /**
         * @brief Parse special properties of a cube from the configuration
         * @param setting Setting of the cube group
         */
        CubeConfig _parseCube(const libconfig::Setting &setting);

        /**
         * @brief Parse a vector3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the vector3D group
         */
        Math::Vector3D _parseVector3D(const std::string propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a point3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the point3D group
         */
        Math::Point3D _parsePoint3D(const std::string propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a color group from the configuration
         * @param setting Setting of the color group
         */
        Graphics::Color _parseColor(const libconfig::Setting &setting);
        /**
         * @brief Parse a tuple of 3 floats from the configuration
         * @param prop Name of the property
         * @param setting Setting of the tuple group
         * @param keys List of keys to look for in the tuple
         */
        std::tuple<float, float, float> _parseTuple3f(const std::string prop,
            const libconfig::Setting &setting, const std::vector<std::string> keys);

        /// @brief Check if a setting has valid keys
        void _settingHasValidKeys(const std::string prop, const libconfig::Setting &setting,
            const std::vector<std::string> &keys);

        /// @brief Wrapper to lookup a value from a setting, and assign it to a variable,
        /// throws an exception if the value is not found or is of the wrong type
        template <typename T>
        void _lookupValueWrapper(const std::string prop, const libconfig::Setting &setting, T &value);

        /// @brief Get the type name of a template variable
        /// Mainly used for debugging purposes and error messages
        template <typename T>
        std::string _typeName(T &value);
};
