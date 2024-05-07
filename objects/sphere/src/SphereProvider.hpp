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
    ~SphereProvider() override = default;

    std::shared_ptr<Common::IObject> create(
        Common::Graphics::Material::Ptr material,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) override;

    Common::Object::Manifest getManifest() override;
};
