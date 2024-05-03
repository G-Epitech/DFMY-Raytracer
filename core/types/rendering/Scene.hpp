/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Scene.hpp
*/

#pragma once

#include <map>
#include <vector>

#include "Camera.hpp"
#include "common/interfaces/IObject.hpp"

namespace Raytracer::Core::Rendering {
    class Scene {
    public:
        /// @brief Map of cameras
        typedef std::map<std::string, Camera::Ptr> CamerasMap;

        /// @brief Map of cameras
        typedef std::map<std::string, Common::Graphics::Material::Ptr> MaterialsMap;

        /// @brief Vector of objects of vector
        typedef std::vector<Common::IObject::Ptr> ObjectsVector;

        /// @brief Shared pointer to a scene
        typedef std::shared_ptr<Scene> Ptr;

        /**
         * @brief Construct a new Scene object
         * @param camera Camera object reference
         * @param objects Objects vector reference
         */
        explicit Scene(std::string name);

        /**
         * @brief Destroy the Scene object
         */
        ~Scene() = default;

        /// @brief Camera object
        CamerasMap cameras;

        /// @brief Materials object
        MaterialsMap materials;

        /// @brief Objects vector
        ObjectsVector objects;

        /// @brief Name of the scene
        const std::string name;
    };
}
