#include "generator.h"

#include <gtest/gtest.h>

class GeneratorTest : public testing::Test { };

TEST_F(GeneratorTest, start) {
    Generator generator;
    generator.addNoise(25, 20, 6);
    std::this_thread::sleep_for(std::chrono::seconds(3));
    generator.stop();
}