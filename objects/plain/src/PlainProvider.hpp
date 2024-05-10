/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PlainProvider
*/

#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class PlainProvider;
}

class Raytracer::Objects::PlainProvider : public Raytracer::Common::IObjectProvider {
public:
    /// @brief Default constructor
    PlainProvider() = default;
    /// @brief Default destructor
    ~PlainProvider() override = default;

    std::shared_ptr<Common::IObject> create(
        Common::Graphics::Material::Ptr material,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) override;

    Common::Object::Manifest getManifest() override;
};
