/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** Config
*/

#pragma once

#include <list>
#include <tuple>
#include <vector>
#include <variant>
#include <cstdlib>
#include <cxxabi.h>
#include <iostream>
#include <libconfig.h++>
#include "ConfigException.hpp"
#include "types/math/Point.hpp"
#include "types/math/Vector.hpp"
#include "interfaces/IObjectProvider.hpp"
#include "types/graphics/Color.hpp"
#include "factory/ObjectFactory.hpp"
#include "types/rendering/Scene.hpp"
#include "plugins/PluginsManager.hpp"
#include "types/graphics/Material.hpp"

using namespace Raytracer::Common;
using namespace Raytracer::Core;

namespace Raytracer::Core {
    class Config;
};

class Raytracer::Core::Config {
    public:
        /// @brief Screen configuration
        typedef struct {
            /// @brief Screen size
            Raytracer::Core::Rendering::Screen::Size size;
            /// @brief Screen origin
            Common::Math::Point3D origin;
        } ScreenConfig;

        /// @brief Camera configuration
        typedef struct {
            /// @brief Name of the camera
            std::string name;
            /// @brief Screen configuration
            ScreenConfig screen;
            /// @brief Camera position
            Common::Math::Point3D position;
            /// @brief Camera direction
            Common::Math::Vector3D direction;
            /// @brief Camera field of view
            float fov;
        } CameraConfig;

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
            Math::Point3D origin;
            /// @brief Object special properties (cube, sphere, etc.)
            Raytracer::Common::ObjectProperty property;
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
            std::list<CameraConfig> cameras;
            /// @brief List of material configurations
            std::list<MaterialConfig> materials;
            /// @brief List of object configurations
            std::list<ObjectConfig> objects;
        } SceneConfig;

        Config(const std::string &path);
        ~Config() = default;

        /**
         * @brief Load a scene configuration from a file
         * @param path Path to the configuration file
         * @return SceneConfig
        */
        void load();

        Rendering::Scene::Ptr toScene(PluginsManager &pluginsManager);

    private:
        std::string _path;
        SceneConfig _sceneConfig;

        void _debugPrintSceneConfig();

        void _buildSceneCameras(Rendering::Scene::Ptr scene);

        void _buildSceneMaterials(Rendering::Scene::Ptr scene);

        void _buildSceneObjects(Rendering::Scene::Ptr scene, PluginsManager &pluginsManager);

        /**
         * @brief Load the name of the scene
         * @param path Path to the configuration file
         */
        std::string _loadName();
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
        ScreenConfig _parseCameraScreen(const libconfig::Setting &setting);
        /**
         * @brief Parse a material group from the configuration
         * @param setting Setting of the material group
         */
        MaterialConfig _parseMaterial(const libconfig::Setting &setting);
        /**
         * @brief Parse an emission direction group from the configuration
         * @param setting Setting of the emission direction group
         */
        std::vector<EmissionConfig> _parseEmissions(const libconfig::Setting &setting);
        /**
         * @brief Parse an object group from the configuration
         * @param setting Setting of the object group
         */
        ObjectConfig _parseObject(const libconfig::Setting &setting);
        /**
         * @brief Parse special properties of a sphere from the configuration
         * @param setting Setting of the sphere group
         */
        float _parseSphere(const libconfig::Setting &setting);
        /**
         * @brief Parse special properties of a cube from the configuration
         * @param setting Setting of the cube group
         */
        Math::Float3 _parseCube(const libconfig::Setting &setting);

        /**
         * @brief Parse a vector3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the vector3D group
         */
        Math::Vector3D _parseVector3D(const std::string& propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a point3D group from the configuration
         * @param propName Name of the property
         * @param setting Setting of the point3D group
         */
        Math::Point3D _parsePoint3D(const std::string& propName, const libconfig::Setting &setting);
        /**
         * @brief Parse a color group from the configuration
         * @param setting Setting of the color group
         */
        Raytracer::Common::Graphics::Color _parseColor(const libconfig::Setting &setting);
        /**
         * @brief Parse a tuple of 3 floats from the configuration
         * @param prop Name of the property
         * @param setting Setting of the tuple group
         * @param keys List of keys to look for in the tuple
         */
        std::tuple<float, float, float> _parseTuple3f(const std::string& prop,
            const libconfig::Setting &setting, const std::vector<std::string>& keys);

        /// @brief Check if a setting has valid keys
        void _settingHasValidKeys(const std::string& prop, const libconfig::Setting &setting,
            const std::vector<std::string> &keys);

        /// @brief Wrapper to lookup a value from a setting, and assign it to a variable,
        /// throws an exception if the value is not found or is of the wrong type
        template <typename T>
        void _lookupValueWrapper(const std::string prop, const libconfig::Setting &setting, T &value)
        {
            if (setting.lookupValue(prop, value) == false) {
                throw Raytracer::Core::ConfigException(prop + " must be a " + _typeName(value));
            }
        }

        /// @brief Get the type name of a template variable
        /// Mainly used for debugging purposes and error messages
        template <typename T>
        std::string _typeName(T &value)
        {
            int status = 0;
            std::string tname = typeid(T).name();
            char *demangled = abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);

            if (status == 0) {
                tname = demangled;
                free(demangled);
            } else {
                tname = "unknown";
            }
            return tname;
        }
};
