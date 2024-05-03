/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Manifest
*/

#pragma once

#include <string>
#include <vector>

namespace Raytracer::Common::Object {
    /// @brief Author of the object
    typedef struct {
        /// @brief Name of the author
        std::string name;
        /// @brief Public contact email
        std::string email;
        /// @brief Website of the author (`github`, `gitlab`, etc.)
        std::string website;
    } Author;

    /// @brief Manifest of the object
    typedef struct {
        /// @brief Name of the object
        const std::string name;
        /// @brief Description of the object
        const std::string description;
        /// @brief Version of the object
        const std::string version;
        /// @brief List of authors of the object
        const std::vector<Author> authors;
    } Manifest;
}
