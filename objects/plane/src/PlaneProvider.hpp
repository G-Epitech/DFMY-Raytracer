/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PlaneProvider
*/

#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class PlaneProvider;
}

class Raytracer::Objects::PlaneProvider : public Raytracer::Common::IObjectProvider {
public:
    /// @brief Default constructor
    PlaneProvider() = default;
    /// @brief Default destructor
    ~PlaneProvider() override = default;

    std::shared_ptr<Common::IObject> create(
        Common::Graphics::Material::Ptr material,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) override;

    Common::Object::Manifest getManifest() override;
};
