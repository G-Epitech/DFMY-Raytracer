/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** meshProvider
*/

#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class MeshProvider;
}

class Raytracer::Objects::MeshProvider : public Raytracer::Common::IObjectProvider {
public:
    /// @brief Default constructor
    MeshProvider() = default;
    /// @brief Default destructor
    ~MeshProvider() = default;

    std::shared_ptr<Common::IObject> create(
        const Common::Graphics::Material::Ptr material,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) override;

    Common::Object::Manifest getManifest() override;
};
