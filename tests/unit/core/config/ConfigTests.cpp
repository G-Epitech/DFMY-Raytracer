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
}
