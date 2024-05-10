/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PluginsManagerTests.cpp
*/

#include <gtest/gtest.h>
#include <filesystem>

#include "plugins/PluginsManager.hpp"

using namespace Raytracer::Core;

class PluginsManagerTests : public testing::Test {
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

TEST_F(PluginsManagerTests, LoadFromValidDirectory)
{
    PluginsManager pluginsManager;

    pluginsManager.load("./plugins");
    ASSERT_GE(pluginsManager.providers.size(), 1);
}

TEST_F(PluginsManagerTests, LoadFromInvalidDirectory)
{
    PluginsManager pluginsManager;

    ASSERT_THROW(pluginsManager.load("./invalid"), PluginsManager::InvalidPathException);
}

TEST_F(PluginsManagerTests, LoadFromEmptyFile)
{
    PluginsManager pluginsManager;

    ASSERT_THROW(pluginsManager.load("./.gitignore"), PluginsManager::InvalidPathException);
}

TEST_F(PluginsManagerTests, LoadFromInvalidFile)
{
    PluginsManager pluginsManager;

    ASSERT_THROW(pluginsManager.load("./.git"), PluginsManager::Exception);
}

TEST_F(PluginsManagerTests, LoadTwoPluginsWithSameName)
{
    PluginsManager pluginsManager;

    std::filesystem::copy("./plugins/raytracer_sphere.so", "./plugins/raytracer_sphere_copy.so");
    EXPECT_THROW(pluginsManager.load("./plugins"), PluginsManager::Exception);
    std::filesystem::remove("./plugins/raytracer_sphere_copy.so");
}

TEST_F(PluginsManagerTests, GetErrorMessageOfException)
{
    PluginsManager::Exception exception("Test");

    ASSERT_STREQ(exception.what(), "Test");
}

TEST_F(PluginsManagerTests, GetErrorMessageOfInvalidPathException)
{
    PluginsManager::InvalidPathException exception("./tests", PluginsManager::InvalidPathException::Reason::NOT_FOUND);

    ASSERT_STREQ(exception.what(), "Invalid path: ./tests");
}

TEST_F(PluginsManagerTests, GetPathOfInvalidPathException)
{
    PluginsManager::InvalidPathException exception("./invalid", PluginsManager::InvalidPathException::Reason::NOT_FOUND);

    ASSERT_STREQ(exception.path(), "./invalid");
}

TEST_F(PluginsManagerTests, GetReasonOfInvalidPathException)
{
    PluginsManager::InvalidPathException exception("./invalid", PluginsManager::InvalidPathException::Reason::NOT_FOUND);

    ASSERT_EQ(exception.reason(), PluginsManager::InvalidPathException::Reason::NOT_FOUND);
}
