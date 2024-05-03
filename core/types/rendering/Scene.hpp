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
#include "common/interfaces/graphics/IObject.hpp"

namespace Raytracer::Core::Rendering {
    class Scene {
    public:
        /// @brief Map of cameras
        typedef std::map<std::string, Camera::Ptr> CamerasMap;
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

        /// @brief Objects vector
        std::vector<Graphics::IObject::Ptr> objects;

        /// @brief Name of the scene
        const std::string name;
    };
}
