/*
** EPITECH PROJECT, 2024
** DFMY-Raytracer
** File description:
** ConfigTests
*/

#include <gtest/gtest.h>

#include "config/Config.hpp"

using namespace Raytracer::Core;
using namespace Raytracer::Common;

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
    auto config = Raytracer::Core::Config::loadFromFile("scenes/test.cfg");
    Raytracer::Core::Config::SceneConfig sceneConfig = config.getSceneConfig();
    auto ambient = sceneConfig.ambient.color.toPixel();
    auto materialColor = sceneConfig.materials[0].objectColor.toPixel();

    ASSERT_EQ(sceneConfig.name, "test") << "Expected scene name to be 'test2'";
    ASSERT_EQ(sceneConfig.cameras.size(), 1) << "Expected 1 camera";
    ASSERT_EQ(sceneConfig.materials.size(), 1) << "Expected 1 material";
    ASSERT_EQ(sceneConfig.objects.size(), 1) << "Expected 1 object";
    ASSERT_EQ(ambient.r, 1) << "Expected ambient color to be 1";
    ASSERT_EQ(ambient.g, 2) << "Expected ambient color to be 2";
    ASSERT_EQ(ambient.b, 3) << "Expected ambient color to be 3";
    ASSERT_EQ(ambient.a, 4) << "Expected ambient color to be 4";
    ASSERT_EQ(sceneConfig.ambient.strength, 0.1f) << "Expected ambient light to be 0.1f";
    ASSERT_EQ(sceneConfig.cameras[0].name, "camera1") << "Expected camera name to be 'camera1'";
    ASSERT_EQ(sceneConfig.cameras[0].position.x, 1.0f) << "Expected camera position to be 1";
    ASSERT_EQ(sceneConfig.cameras[0].position.y, 2.0f) << "Expected camera position to be 2";
    ASSERT_EQ(sceneConfig.cameras[0].position.z, 3.0f) << "Expected camera position to be 3";
    ASSERT_EQ(sceneConfig.cameras[0].direction.x, 2.0f) << "Expected camera direction to be 4";
    ASSERT_EQ(sceneConfig.cameras[0].direction.y, 3.0f) << "Expected camera direction to be 5";
    ASSERT_EQ(sceneConfig.cameras[0].direction.z, 4.0f) << "Expected camera direction to be 6";
    ASSERT_EQ(sceneConfig.cameras[0].fov, 60.0f) << "Expected camera fov to be 90";
    ASSERT_EQ(sceneConfig.cameras[0].screenSize.width, 800) << "Expected camera screen width to be 800";
    ASSERT_EQ(sceneConfig.cameras[0].screenSize.height, 600) << "Expected camera screen height to be 600";
    ASSERT_EQ(sceneConfig.materials[0].name, "red") << "Expected material name to be 'red'";
    ASSERT_EQ(materialColor.r, 1) << "Expected material color to be 1";
    ASSERT_EQ(materialColor.g, 0) << "Expected material color to be 0";
    ASSERT_EQ(materialColor.b, 0) << "Expected material color to be 0";
    ASSERT_EQ(materialColor.a, 1) << "Expected material color to be 1";
    ASSERT_EQ(sceneConfig.materials[0].reflectivity, 0.5f) << "Expected material reflectivity to be 0.5f";
    ASSERT_EQ(sceneConfig.materials[0].emissions[0].strength, 1.0);
    ASSERT_EQ(sceneConfig.objects[0].type, "sphere") << "Expected object type to be 'sphere'";
    ASSERT_EQ(sceneConfig.objects[0].material, "red") << "Expected object material to be 'sphere'";
    ASSERT_EQ(sceneConfig.objects[0].origin.x, 1.0f) << "Expected object origin to be 1";
    ASSERT_EQ(sceneConfig.objects[0].origin.y, 2.0f) << "Expected object origin to be 2";
    ASSERT_EQ(sceneConfig.objects[0].origin.z, 3.0f) << "Expected object position to be 3";
}



TEST_F(ConfigTests, UnknownFile)
{
    ASSERT_THROW(Raytracer::Core::Config::loadFromFile("wow"), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidFileSyntax)
{
    ASSERT_THROW(Raytracer::Core::Config::loadFromFile("tests/unit/core/config/invalid_file.cfg"), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidAmbientFormat)
{
    std::string configFileContents = "ambient = []\n"
                                     "cameras = []\n"
                                     "materials = []\n"
                                     "objects = []\n";

    ASSERT_THROW( Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
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

    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidMaterialsFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = 32\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidMaterialsElementFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (23)\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidMaterialsElementEmissionsFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                    "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = 23\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                    "    }\n"
                                    ")\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}


TEST_F(ConfigTests, InvalidMaterialsElementEmissionElementFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = (23)\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}


TEST_F(ConfigTests, InvalidObjectsFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = ()\n"
                                     "objects = 3\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidObjectElementFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = ()\n"
                                     "objects = (4)\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidObjectSphereFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = ()\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = (\n"
                                     "    {\n"
                                     "        type = \"sphere\",\n"
                                     "        material = \"red\",\n"
                                     "        origin = {x=1.0, y=2.0, z=3.0},\n"
                                     "        properties = 4\n"
                                     "    }\n"
                                     ")\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, ValidSphereFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = ()\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = (\n"
                                     "    {\n"
                                     "        type = \"sphere\",\n"
                                     "        material = \"red\",\n"
                                     "        origin = {x=1.0, y=2.0, z=3.0},\n"
                                     "        properties = {\n"
                                     "            radius = 1.0\n"
                                     "        }\n"
                                     "    }\n"
                                     ")\n";
    Config config = Raytracer::Core::Config::loadFromString(configFileContents);
    Raytracer::Core::Config::SceneConfig sceneCfg = config.getSceneConfig();

    ASSERT_EQ(sceneCfg.objects[0].type, "sphere") << "Expected object type to be SPHERE";
    ASSERT_EQ(sceneCfg.objects[0].material, "red") << "Expected object material to be 'red'";
    ASSERT_EQ(sceneCfg.objects[0].origin.x, 1.0f) << "Expected object origin to be 1";
    ASSERT_EQ(sceneCfg.objects[0].origin.y, 2.0f) << "Expected object origin to be 2";
    ASSERT_EQ(sceneCfg.objects[0].origin.z, 3.0f) << "Expected object origin to be 3";
    ASSERT_EQ(std::get<float>(sceneCfg.objects[0].property), 1.0f) << "Expected object radius to be 1";
}

TEST_F(ConfigTests, ValidCubeFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = ()\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = (\n"
                                     "    {\n"
                                     "        type = \"cube\",\n"
                                     "        material = \"red\",\n"
                                     "        origin = {x=1.0, y=2.0, z=3.0},\n"
                                     "        properties = {\n"
                                     "            size = {width=1.0, height=2.0, depth=3.0}\n"
                                     "        }\n"
                                     "    }\n"
                                     ")\n";
    Config config = Raytracer::Core::Config::loadFromString(configFileContents);
    Raytracer::Core::Config::SceneConfig sceneCfg = config.getSceneConfig();
    Math::Float3 size = std::get<Math::Float3>(sceneCfg.objects[0].property);

    ASSERT_EQ(sceneCfg.objects[0].type, "cube") << "Expected object type to be SPHERE";
    ASSERT_EQ(sceneCfg.objects[0].material, "red") << "Expected object material to be 'red'";
    ASSERT_EQ(sceneCfg.objects[0].origin.x, 1.0f) << "Expected object origin to be 1";
    ASSERT_EQ(sceneCfg.objects[0].origin.y, 2.0f) << "Expected object origin to be 2";
    ASSERT_EQ(sceneCfg.objects[0].origin.z, 3.0f) << "Expected object origin to be 3";
    ASSERT_EQ(size.x, 1.0f) << "Expected cube size to be 1";
    ASSERT_EQ(size.y, 2.0f) << "Expected cube size to be 2";
    ASSERT_EQ(size.z, 3.0f) << "Expected cube size to be 3";
}

TEST_F(ConfigTests, InvalidCubeSizeFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = ()\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = (\n"
                                     "    {\n"
                                     "        type = \"cube\",\n"
                                     "        material = \"red\",\n"
                                     "        origin = {x=1.0, y=2.0, z=3.0},\n"
                                     "        properties = {\n"
                                     "            size = 3\n"
                                     "        }\n"
                                     "    }\n"
                                     ")\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidCubePropertiesFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = ()\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = (\n"
                                     "    {\n"
                                     "        type = \"cube\",\n"
                                     "        material = \"red\",\n"
                                     "        origin = {x=1.0, y=2.0, z=3.0},\n"
                                     "        properties = 3"
                                     "    }\n"
                                     ")\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidCubePropertiesKeys)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = (\n"
                                     "    {\n"
                                     "        name = \"red\",\n"
                                     "        objectColor = {r=1, g=0, b=0, a=1},\n"
                                     "        emissions = ()\n"
                                     "        reflectivity = 0.5,\n"
                                     "        emissionStrength = 0.5,\n"
                                     "        emissionColor = {r=1, g=0, b=0, a=1}\n"
                                     "    }\n"
                                     ")\n"
                                     "objects = (\n"
                                     "    {\n"
                                     "        type = \"cube\",\n"
                                     "        material = \"red\",\n"
                                     "        origin = {x=1.0, y=2.0, z=3.0},\n"
                                     "        properties = {\n"
                                     "            size = {width=1.0, height=2.0}\n"
                                     "        }\n"
                                     "    }\n"
                                     ")\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidPoint3DProps)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = (\n"
                                     "    {\n"
                                     "        name = \"camera1\",\n"
                                     "        screen = {width=800, height=600}\n"
                                     "        position = {x=1.0, y=2.0}\n"
                                     "        direction = {x=2.0, y=3.0, z=4.0},\n"
                                     "        fieldOfView = 60.0,\n"
                                     "        resolution = {width=800, height=600},\n"
                                     "    }\n"
                                     ")\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidPoint3DFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = (\n"
                                     "    {\n"
                                     "        name = \"camera1\",\n"
                                     "        size = {width=800, height=600}\n"
                                     "        position = 32,\n"
                                     "        direction = {x=2.0, y=3.0, z=4.0},\n"
                                     "        fieldOfView = 60.0,\n"
                                     "        resolution = {width=800, height=600},\n"
                                     "    }\n"
                                     ")\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidVector3DProps)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = {r=1, g=2, b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = (\n"
                                     "    {\n"
                                     "        name = \"camera1\",\n"
                                     "        size = {width=800, height=600}\n"
                                     "        position = {x=1.0, y=2.0, z=3.0},\n"
                                     "        direction = 3,\n"
                                     "        fieldOfView = 60.0,\n"
                                     "        resolution = {width=800, height=600},\n"
                                     "    }\n"
                                     ")\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidColorFormat)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color = 32\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, InvalidType)
{
    std::string configFileContents = "ambient = {\n"
                                     "    color =  {r=1, g=3.2 b=3, a=4}\n"
                                     "    strength = 0.1\n"
                                     "}\n"
                                     "cameras = ()\n"
                                     "materials = ()\n"
                                     "objects = ()\n";
    ASSERT_THROW(Raytracer::Core::Config::loadFromString(configFileContents), Raytracer::Core::ConfigException);
}

TEST_F(ConfigTests, ConfigToScene)
{
    PluginsManager pluginsManager;
    pluginsManager.load("./plugins");


    auto config = Config::loadFromFile("scenes/test.cfg");
    Config::SceneConfig sceneConfig = config.getSceneConfig();
    auto scene = config.toScene(pluginsManager);

    ASSERT_EQ(scene->cameras.size(), 1) << "Expect to have 1 camera";
    ASSERT_EQ(scene->materials.size(), 1) << "Expect to have 1 material";
    ASSERT_EQ(scene->objects.size(), 1) << "Expect to have 1 object";
}
