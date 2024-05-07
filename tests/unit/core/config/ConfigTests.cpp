/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer [WSL: Ubuntu-22.04]
** File description:
** ConfigTests
*/

#include <gtest/gtest.h>

#include "config/Config.hpp"

using namespace Raytracer::Core;

class ConfigTests : public ::testing::Test {
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

TEST_F(ConfigTests, ValidConfiguration)
{
    Raytracer::Core::Config config("scenes/test2.cfg");
    config.load();
    Raytracer::Core::Config::SceneConfig sceneConfig = config.getSceneConfig();

    ASSERT_EQ(sceneConfig.name, "test2") << "Expected scene name to be 'test2'";
    ASSERT_EQ(sceneConfig.cameras.size(), 1) << "Expected 1 camera";
    ASSERT_EQ(sceneConfig.materials.size(), 1) << "Expected 1 material";
    ASSERT_EQ(sceneConfig.objects.size(), 0) << "Expected 1 object";
    ASSERT_EQ(sceneConfig.ambient.color.r, 1) << "Expected ambient light to be 1";
    ASSERT_EQ(sceneConfig.ambient.color.g, 2) << "Expected ambient light to be 2";
    ASSERT_EQ(sceneConfig.ambient.color.b, 3) << "Expected ambient light to be 3";
    ASSERT_EQ(sceneConfig.ambient.color.a, 4) << "Expected ambient light to be 4";
    ASSERT_EQ(sceneConfig.ambient.strength, 0.1f) << "Expected ambient light to be 0.1f";
    ASSERT_EQ(sceneConfig.cameras[0].name, "camera1") << "Expected camera name to be 'camera1'";
    ASSERT_EQ(sceneConfig.cameras[0].position.x, 1.0f) << "Expected camera position to be 1";
    ASSERT_EQ(sceneConfig.cameras[0].position.y, 2.0f) << "Expected camera position to be 2";
    ASSERT_EQ(sceneConfig.cameras[0].position.z, 3.0f) << "Expected camera position to be 3";
    ASSERT_EQ(sceneConfig.cameras[0].direction.x, 2.0f) << "Expected camera direction to be 4";
    ASSERT_EQ(sceneConfig.cameras[0].direction.y, 3.0f) << "Expected camera direction to be 5";
    ASSERT_EQ(sceneConfig.cameras[0].direction.z, 4.0f) << "Expected camera direction to be 6";
    ASSERT_EQ(sceneConfig.cameras[0].fov, 60.0f) << "Expected camera fov to be 90";
    ASSERT_EQ(sceneConfig.materials[0].name, "red") << "Expected material name to be 'red'";
    ASSERT_EQ(sceneConfig.materials[0].color.r, 1) << "Expected material color to be 1";
    ASSERT_EQ(sceneConfig.materials[0].color.g, 0) << "Expected material color to be 2";
    ASSERT_EQ(sceneConfig.materials[0].color.b, 0) << "Expected material color to be 3";
    ASSERT_EQ(sceneConfig.materials[0].color.a, 1) << "Expected material color to be 4";
    ASSERT_EQ(sceneConfig.materials[0].reflectivity, 0.5f) << "Expected material reflectivity to be 0.5f";
}

TEST_F(ConfigTests, InvalidConfigurationMembers)
{
    std::string configFileContents = "ambient = {}\n"
                                     "cameras = []\n"
                                     "materials = []\n";
    Raytracer::Core::Config config(configFileContents, true);
    ASSERT_THROW(config.load(), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidAmbientFormat)
{
    std::string configFileContents = "ambient = []\n"
                                     "cameras = []\n"
                                     "materials = []\n"
                                     "objects = []\n";
    Raytracer::Core::Config config(configFileContents, true);
    ASSERT_THROW(config.load(), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidCamerasFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = {}\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    Raytracer::Core::Config config(configFileContents, true);
    ASSERT_THROW(config.load(), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidCamerasResolutionFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = (\n"
                                     "    {\n"
                                     "        name = \"camera1\"\n"
                                     "        screen = {\n"
                                     "            size = {width=800, height=600},\n"
                                     "            origin = {x=20.0, y=10.0, z=40.0},\n"
                                     "        }\n"
                                     "        position = {x=1.0 y=2.0, z=3.0}\n"
                                     "        direction = {x=2.0, y=3.0, z=4.0}\n"
                                     "        fieldOfView = 60.0\n"
                                     "        resolution = ()\n"
                                     "    }\n"
                                     ")\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    Raytracer::Core::Config config(configFileContents, true);
    ASSERT_THROW(config.load(), Raytracer::Core::ConfigException);
}
