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
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) override;

    Common::Object::Manifest getManifest() override;

    Common::ObjectProperty parseProperty(const libconfig::Setting &setting) override;
};
