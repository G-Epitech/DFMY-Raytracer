/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
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
#include "types/rendering/Camera.hpp"
#include "ConfigException.hpp"

using namespace Raytracer::Common;
using namespace Raytracer::Core;

namespace Raytracer::Core {
    class Config;
};

class Raytracer::Core::Config {
    public:
        /// @brief Emission direction configuration
        typedef struct {
            /// @brief Light emission color
            Raytracer::Common::Graphics::Color color;
            /// @brief Light emission strength
            float strength;
            /// @brief Light emission direction
            Math::Vector3D direction;
        } EmissionConfig;

        /// @brief Material configuration
        typedef struct {
            /// @brief Material name
            std::string name;
            /// @brief Material color for the object
            Raytracer::Common::Graphics::Color color;
            /// @brief Material light emission directions
            std::vector<EmissionConfig> emissions;
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

        /// @brief Special properties configuration for an object
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
            Raytracer::Common::Graphics::Color color;
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
            std::list<Rendering::Camera::Config> cameras;
            /// @brief List of material configurations
            std::list<MaterialConfig> materials;
            /// @brief List of object configurations
            std::list<ObjectConfig> objects;
        } SceneConfig;

        Config() = default;
        ~Config() = default;

        /**
         * @brief Load a scene configuration from a file
         * @param path Path to the configuration file
         * @return SceneConfig
        */
        static SceneConfig load(const std::string &path);

    private:
        /**
         * @brief Load the name of the scene
         * @param path Path to the configuration file
         */
        static std::string _loadName(const std::string &path);
        /**
         * @brief Load the scene ambient light configuration
         * @param root Root setting of the configuration file
         */
        static AmbientConfig _loadAmbient(const libconfig::Setting &root);
        /**
         * @brief Load the scene cameras configuration
         * @param root Root setting of the configuration file
         */
        static std::list<Rendering::Camera::Config> _loadCameras(const libconfig::Setting &root);
        /**
         * @brief Load the scene materials configuration
         * @param root Root setting of the configuration file
         */
        static std::list<MaterialConfig> _loadMaterials(const libconfig::Setting &root);
        /**
         * @brief Load the scene objects configuration
         * @param root Root setting of the configuration file
         */
        static std::list<ObjectConfig> _loadObjects(const libconfig::Setting &root);

        /**
         * @brief Parse a camera group from the configuration
         * @param setting Setting of the camera group
         */
        static Rendering::Screen::Config _parseCameraScreen(const libconfig::Setting &setting);
        /**
         * @brief Parse a material group from the configuration
         * @param setting Setting of the material group
         */
        static MaterialConfig _parseMaterial(const libconfig::Setting &setting);
        /**
         * @brief Parse an emission direction group from the configuration
         * @param setting Setting of the emission direction group
         */
        static std::vector<EmissionConfig> _parseEmissions(const libconfig::Setting &setting);
        /**
         * @brief Parse an object group from the configuration
         * @param setting Setting of the object group
         */
        static ObjectConfig _parseObject(const libconfig::Setting &setting);
        /**
         * @brief Parse special properties of a sphere from the configuration
         * @param setting Setting of the sphere group
         */
        static SphereConfig _parseSphere(const libconfig::Setting &setting);
        /**
         * @brief Parse special properties of a cube from the configuration
         * @param setting Setting of the cube group
         */
        static CubeConfig _parseCube(const libconfig::Setting &setting);

        /**
         * @brief Parse a vector3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the vector3D group
         */
        static Math::Vector3D _parseVector3D(const std::string propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a point3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the point3D group
         */
        static Math::Point3D _parsePoint3D(const std::string propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a color group from the configuration
         * @param setting Setting of the color group
         */
        static Raytracer::Common::Graphics::Color _parseColor(const libconfig::Setting &setting);
        /**
         * @brief Parse a tuple of 3 floats from the configuration
         * @param prop Name of the property
         * @param setting Setting of the tuple group
         * @param keys List of keys to look for in the tuple
         */
        static std::tuple<float, float, float> _parseTuple3f(const std::string prop,
            const libconfig::Setting &setting, const std::vector<std::string> keys);

        /// @brief Check if a setting has valid keys
        static void _settingHasValidKeys(const std::string prop, const libconfig::Setting &setting,
            const std::vector<std::string> &keys);

        /// @brief Wrapper to lookup a value from a setting, and assign it to a variable,
        /// throws an exception if the value is not found or is of the wrong type
        template <typename T>
        static void _lookupValueWrapper(const std::string prop, const libconfig::Setting &setting, T &value);

        /// @brief Get the type name of a template variable
        /// Mainly used for debugging purposes and error messages
        template <typename T>
        static std::string _typeName(T &value);
};
