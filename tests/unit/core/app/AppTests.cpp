/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AppTests.cpp
*/

#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

#include "app/App.hpp"

using namespace Raytracer::Core;

#define TEST_STRINGIFY(X) #X

class AppTests : public testing::Test {
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

TEST_F(AppTests, AppRunWithBadOptions)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-a"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 3;

    optind = 1;
    opterr = 0;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
}

TEST_F(AppTests, AppRunWithHelpOption)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-h")
    };
    int argc = 2;

    optind = 1;
    redirectStdout();
    ASSERT_EQ(app.run(argc, argv), 0) << "Expected return code 0";
    ASSERT_GT(stdoutBuffer.str().length(), 0) << "Expected non-empty help message";
}

TEST_F(AppTests, AppRunWithNoSceneFile)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer")
    };
    int argc = 1;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, AppRunWithInexistantPluginsDir)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-p"),
        const_cast<char *>("invalid")
    };
    int argc = 3;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, AppRunWithFileSpecifiedForPluginsDir)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-p"),
        const_cast<char *>("./.gitignore"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, LoadSceneFail)
{
    App app;

    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("./tests/resources/scene/duplicated-camera.cfg")
    };
    int argc = 2;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyNegativeNumberOfThreads)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-t"),
        const_cast<char *>("-1"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyZeroNumberOfThreads)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-t"),
        const_cast<char *>("0"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyTooManyThreads)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-t"),
        const_cast<char *>("65"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyNumberOfThreadsOverMaxOfStorageType)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-t"),
        const_cast<char *>(TEST_STRINGIFY(SIZE_MAX)),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}


TEST_F(AppTests, SpecifyOddNumberOfThreads)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-t"),
        const_cast<char *>("3"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    ASSERT_EQ(app.run(argc, argv), 0) << "Expected return code 0";
}

TEST_F(AppTests, SpecifyInvalidOutputFormat)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-f"),
        const_cast<char *>("invalid"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, InvalidPlugin)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 2;

    optind = 1;
    redirectStderr();
    std::ofstream file("./plugins/raytracer_sphere_tests.so");

    EXPECT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    EXPECT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
    file.close();
    std::filesystem::remove("./plugins/raytracer_sphere_tests.so");
}

TEST_F(AppTests, SpecifyInvalidRaysPerPixel)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-r"),
        const_cast<char *>("-1"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyInvalidBounce)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-b"),
        const_cast<char *>("-1"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyInvalidFrames)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-F"),
        const_cast<char *>("-1"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 84";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}

TEST_F(AppTests, SpecifyZeroBounce)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-b"),
        const_cast<char *>("0"),
        const_cast<char *>("./tests/resources/scenes/empty.cfg")
    };
    int argc = 4;

    optind = 1;
    redirectStderr();
    ASSERT_EQ(app.run(argc, argv), 84) << "Expected return code 0";
    ASSERT_GT(stderrBuffer.str().length(), 0) << "Expected error message";
}
