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
    typedef struct Author {
        /// @brief Constructor
        Author();
        /// @brief Create a new author
        Author(const std::string &name, const std::string &email, const std::string &website);
        /// @brief Name of the author
        const std::string name;
        /// @brief Public contact email
        const std::string email;
        /// @brief Website of the author (`github`, `gitlab`, etc.)
        const std::string website;
    } Author;

    /// @brief Manifest of the object
    typedef struct Manifest {
        /// @brief Constructor
        Manifest();
        /// @brief Create a new manifest
        Manifest(const std::string &name, const std::string &description, const std::string &version, const std::vector<Author> &authors);
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
