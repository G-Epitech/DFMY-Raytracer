/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** Manifest
*/

#include "Manifest.hpp"

using namespace Raytracer::Common::Object;

Author::Author() : name(""), email(""), website("") {}

Author::Author(const std::string &name, const std::string &email, const std::string &website)
    : name(name), email(email), website(website) {}

Manifest::Manifest() : name(""), description(""), version(""), authors({}) {}

Manifest::Manifest(const std::string &name, const std::string &description, const std::string &version, const std::vector<Author> &authors)
    : name(name), description(description), version(version), authors(authors) {}
