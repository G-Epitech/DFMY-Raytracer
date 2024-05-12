/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** CubeProvider
*/

#include "common/interfaces/IObjectProvider.hpp"

namespace Raytracer::Objects {
    class CubeProvider;
}

class Raytracer::Objects::CubeProvider : public Raytracer::Common::IObjectProvider {
public:
    /// @brief Default constructor
    CubeProvider() = default;
    /// @brief Default destructor
    ~CubeProvider() override = default;

    std::shared_ptr<Common::IObject> create(
        const std::string &name,
        Common::Graphics::Material::Ptr material,
        const Common::Math::Vector3D &rotation,
        const Common::Math::Point3D &position,
        const Common::ObjectProperty &property) override;

    Common::Object::Manifest getManifest() override;

    Common::ObjectProperty parseProperty(const libconfig::Setting &setting) override;
};
