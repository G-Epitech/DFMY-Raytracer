/*
** EPITECH PROJECT, 2024
** raytracer
** File description:
** PointsTests.cpp
*/

#include <gtest/gtest.h>
#include <filesystem>

#include "types/graphics/Image.hpp"

using namespace Raytracer::Core;

TEST(ImageTests, CreateSimpleImage) {
    Graphics::PixelArray array = std::make_unique<sf::Uint8[]>(32);
    Graphics::Image img(4, 8, array);

    ASSERT_EQ(img.width, 4);
    ASSERT_EQ(img.height, 8);
}

TEST(ImageTests, SaveImageWithoutExtension) {
    Graphics::PixelArray array = std::make_unique<sf::Uint8[]>(32);
    Graphics::Image img(4, 8, array);

    auto result = img.saveTo("test");
    auto fileExists = std::filesystem::exists("test");

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileExists, true);

    std::filesystem::remove("test");
}

TEST(ImageTests, SaveImageWithExtension) {
    Graphics::PixelArray array = std::make_unique<sf::Uint8[]>(32);
    Graphics::Image img(4, 8, array);

    auto result = img.saveTo("test.png");
    auto fileExists = std::filesystem::exists("test.png");

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileExists, true);

    std::filesystem::remove("test.png");
}

TEST(ImageTests, SaveImageWithInvalidExtension) {
    testing::internal::CaptureStderr();
    Graphics::PixelArray array = std::make_unique<sf::Uint8[]>(32);
    Graphics::Image img(4, 8, array);

    auto result = img.saveTo("test.txt");
    auto fileExists = std::filesystem::exists("test.txt");

    EXPECT_EQ(result, false);
    EXPECT_EQ(fileExists, false);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Failed to save image \"test.txt\"\n");
}

TEST(ImageTests, SaveImageWithExplicitPpmExtension)
{
    Graphics::PixelArray array = std::make_unique<sf::Uint8[]>(32);
    Graphics::Image img(4, 8, array);

    auto result = img.saveTo("test.ppm");
    auto fileExists = std::filesystem::exists("test.ppm");

    EXPECT_EQ(result, true);
    EXPECT_EQ(fileExists, true);

    std::filesystem::remove("test.ppm");
}

TEST(ImageTests, SaveFailDueToInvalidPath)
{
    Graphics::PixelArray array = std::make_unique<sf::Uint8[]>(32);
    Graphics::Image img(4, 8, array);

    auto result = img.saveTo("/test/");
    auto fileExists = std::filesystem::exists("/test/");

    EXPECT_EQ(result, false);
    EXPECT_EQ(fileExists, false);
}

TEST(ImageTests, SaveFailDueToInvalidPixels)
{
    testing::internal::CaptureStderr();
    Graphics::PixelArray array = nullptr;
    Graphics::Image img(4, 8, array);

    auto result = img.saveTo("test.ppm");
    auto fileExists = std::filesystem::exists("test.ppm");

    EXPECT_EQ(result, false);
    EXPECT_EQ(fileExists, false);
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(output, "Trying to access the pixels of an empty image\n");
}
