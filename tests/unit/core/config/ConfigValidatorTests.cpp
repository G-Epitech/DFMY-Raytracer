/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** ConfigValidatorTests
*/

#include <gtest/gtest.h>

#include "config/Config.hpp"
#include "config/ConfigValidator.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

class ConfigValidatorTests : public ::testing::Test {
    protected:

    void SetUp() override {
        stdoutBuf = std::cout.rdbuf();
        stderrBuf = std::cerr.rdbuf();
    }

    void TearDown() override {
        std::cout.rdbuf(stdoutBuf);
        std::cerr.rdbuf(stderrBuf);
    }

    void redirectStdout() {
        std::cout.rdbuf(stdoutBuffer.rdbuf());
    }

    void redirectStderr() {
        std::cerr.rdbuf(stderrBuffer.rdbuf());
    }

    std::stringstream stdoutBuffer;
    std::stringstream stderrBuffer;
    std::streambuf *stdoutBuf = nullptr;
    std::streambuf *stderrBuf = nullptr;
};

TEST_F(ConfigValidatorTests, InvalidMaterialReflectivity)
{
    Config::SceneConfig cfg;
    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = -0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}

TEST_F(ConfigValidatorTests, DuplicateMaterials)
{
    Config::SceneConfig cfg;
    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}

TEST_F(ConfigValidatorTests, InvalidCameraFOV)
{
    Config::SceneConfig cfg;
    Config::CameraConfig cam;
    Math::Point3D pt(0, 0, 0);
    Math::Vector3D vec(0, 0, 0);

    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    cam.name = "camera1";
    cam.fov = -200;
    cam.position = pt;
    cam.direction = vec;
    cfg.cameras.push_back(cam);
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}

TEST_F(ConfigValidatorTests, DuplicateCameras)
{
    Config::SceneConfig cfg;
    Config::CameraConfig cam;
    Math::Point3D pt(0, 0, 0);
    Math::Vector3D vec(0, 0, 0);

    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    cam.name = "camera1";
    cam.fov = 10;
    cam.position = pt;
    cam.direction = vec;
    cfg.cameras.push_back(cam);
    cfg.cameras.push_back(cam);
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}

TEST_F(ConfigValidatorTests, MissingObjectMaterial)
{
    Config::SceneConfig cfg;
    Config::ObjectConfig obj;

    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    obj.material = "";
    cfg.objects.push_back(obj);
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}

TEST_F(ConfigValidatorTests, InvalidObjectMaterial)
{
    Config::SceneConfig cfg;
    Config::ObjectConfig obj;

    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    obj.material = "material2";
    cfg.objects.push_back(obj);
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}

TEST_F(ConfigValidatorTests, InvalidSphereRadius)
{
    Config::SceneConfig cfg;
    Config::ObjectConfig obj;

    cfg.materials.push_back({
        .name = "material1",
        .objectColor = {255, 255, 255},
        .emissions = {},
        .reflectivity = 0.5,
        .emissionStrength = 0.5,
        .emissionColor = {255, 255, 255}
    });
    obj.material = "material1";
    obj.type = "sphere";
    obj.property = -10.0f;
    cfg.objects.push_back(obj);
    ASSERT_THROW(ConfigValidator::valid(cfg), ConfigException);
}
