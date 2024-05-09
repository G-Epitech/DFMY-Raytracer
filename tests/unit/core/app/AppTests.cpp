/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** AppTests.cpp
*/

#include <gtest/gtest.h>

#include "app/App.hpp"

using namespace Raytracer::Core;

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

TEST_F(AppTests, SimpleAppRun)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("scenes/test2.cfg")
    };
    int argc = 2;

    ASSERT_EQ(app.run(argc, argv), 0) << "Expected return code 0";
}

TEST_F(AppTests, AppRunWithBadOptions)
{
    App app;
    char *argv[] = {
        const_cast<char *>("./raytracer"),
        const_cast<char *>("-a"),
        const_cast<char *>("scenes/test2.cfg")
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
