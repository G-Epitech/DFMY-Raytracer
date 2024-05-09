/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** ObjectFactoryTests.cpp
*/

#include <gtest/gtest.h>

#include "factory/ObjectFactory.hpp"

using namespace Raytracer::Core;

class ObjectFactoryTests : public testing::Test {
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

TEST_F(ObjectFactoryTests, AppRunWithBadOptions)
{
    //ObjectFactory objectFactory()

}
