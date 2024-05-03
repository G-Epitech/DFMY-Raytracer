/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** SphereProvider
*/

#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class SphereProvider;
}

class Raytracer::Objects::SphereProvider : public Raytracer::Common::IObjectProvider {
public:
    /// @brief Default constructor
    SphereProvider() = default;
    /// @brief Default destructor
    ~SphereProvider() = default;

    /// @brief Create a new object
    std::shared_ptr<Raytracer::Common::IObject> create() override;
    /// @brief Get the manifest of the object
    Raytracer::Common::Object::Manifest getManifest() override;
};
