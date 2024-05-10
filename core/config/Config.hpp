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
#include "types/graphics/Color.hpp"
#include "factory/ObjectFactory.hpp"
#include "types/rendering/Scene.hpp"
#include "plugins/PluginsManager.hpp"
#include "types/graphics/Material.hpp"
#include "interfaces/IObjectProvider.hpp"
#include "config/ConfigUtils.hpp"

using namespace Raytracer::Common;
using namespace Raytracer::Core;

namespace Raytracer::Core {
    class Config {
    public:
        /// @brief Camera configuration
        typedef struct {
            /// @brief Name of the camera
            std::string name;
            /// @brief Screen configuration
            Raytracer::Common::Math::Size screenSize;
            /// @brief Camera position
            Common::Math::Point3D position;
            /// @brief Camera direction
            Common::Math::Vector3D direction;
            /// @brief Camera field of view
            float fov;
        } CameraConfig;

        /// @brief Material configuration
        typedef struct {
            /// @brief Material name
            std::string name;
            /// @brief Material color for the object
            Raytracer::Common::Graphics::Color objectColor;
            /// @brief Material light emission directions
            std::vector<Raytracer::Common::Graphics::Material::Emission> emissions;
            /// @brief Material index of reflectivity
            float reflectivity;
            /// @brief General emission strength of the object
            float emissionStrength;
            /// @brief Material color for the light emission
            Raytracer::Common::Graphics::Color emissionColor;
        } MaterialConfig;

        /// @brief Object configuration
        typedef struct {
            /// @brief Object name
            std::string name;
            /// @brief Object type (cube, sphere, etc.)
            std::string type;
            /// @brief The material name for the object
            std::string material;
            /// @brief Object origin
            Math::Point3D origin;
            /// @brief Object rotation
            Math::Vector3D rotation;
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
            std::vector<CameraConfig> cameras;
            /// @brief List of material configurations
            std::vector<MaterialConfig> materials;
            /// @brief List of object configurations
            std::vector<ObjectConfig> objects;
        } SceneConfig;

        explicit Config(PluginsManager &pluginsManager);

        ~Config() = default;

        /**
         * @brief Load a scene configuration from a string (useful for testing)
         * @param contents Contents of the configuration file
         */
        static Config loadFromString(const std::string &contents, PluginsManager &pluginsManager);

        /**
         * @brief Load a scene configuration from a file
         * @param path Path to the configuration file
         */
        static Config loadFromFile(const std::string &path, PluginsManager &pluginsManager);

        /**
         * @brief Convert a scene configuration to a Scene object
         * @return Scene::Ptr
        */
        Rendering::Scene::Ptr toScene();

        /**
         * @brief Get the scene configuration
         * @return SceneConfig
        */
        [[nodiscard]]
        SceneConfig getSceneConfig() const;

    private:
        /// @brief Contents of the configuration file
        std::string _contents;
        /// @brief Path to the configuration file
        std::string _path;
        /// @brief Scene configuration
        SceneConfig _sceneConfig;
        /// @brief Flag to indicate if the configuration was loaded from a string
        bool _fromString;
        /// @brief Linked plugin manager
        PluginsManager &_pluginsManager;

        /**
         * @brief Load a scene configuration from a file
        */
        void _load();

        /**
         * @brief Builds the cameras of the scene
         * @param scene Scene to build the cameras for
         */
        void _buildSceneCameras(const Rendering::Scene::Ptr &scene);

        /**
         * @brief Builds the materials of the scene
         * @param scene Scene to build the materials for
         */
        void _buildSceneMaterials(const Rendering::Scene::Ptr &scene);

        /**
         * @brief Builds the objects of the scene
         * @param scene Scene to build the objects for
         */
        void _buildSceneObjects(const Rendering::Scene::Ptr &scene, PluginsManager &pluginsManager);

        /**
         * @brief Load the name of the scene
         * @param path Path to the configuration file
         */
        std::string _loadName();

        /**
         * @brief Load the scene ambient light configuration
         * @param root Root setting of the configuration file
         */
        static AmbientConfig _loadAmbient(const libconfig::Setting &root);

        /**
         * @brief Load the scene cameras configuration
         * @param root Root setting of the configuration file
         */
        static std::vector<CameraConfig> _loadCameras(const libconfig::Setting &root);

        /**
         * @brief Load the scene materials configuration
         * @param root Root setting of the configuration file
         */
        static std::vector<MaterialConfig> _loadMaterials(const libconfig::Setting &root);

        /**
         * @brief Load the scene objects configuration
         * @param root Root setting of the configuration file
         */
        static std::vector<ObjectConfig> _loadObjects(const libconfig::Setting &root, PluginsManager &pluginsManager);

        /**
         * @brief Parse a material group from the configuration
         * @param setting Setting of the material group
         */
        static MaterialConfig _parseMaterial(const libconfig::Setting &setting);

        /**
         * @brief Parse an emission direction group from the configuration
         * @param setting Setting of the emission direction group
         */
        static std::vector<Raytracer::Common::Graphics::Material::Emission> _parseEmissions(
            const libconfig::Setting &setting);

        /**
         * @brief Parse an object group from the configuration
         * @param setting Setting of the object group
         */
        static ObjectConfig _parseObject(const libconfig::Setting &setting, PluginsManager &pluginsManager);
    };
}
