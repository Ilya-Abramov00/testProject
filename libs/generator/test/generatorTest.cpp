#include "generator.h"

#include <gtest/gtest.h>

class GeneratorTest : public testing::Test { };

TEST_F(GeneratorTest, start) {
    Generator<int> generator;
    for(size_t i = 0; i != 100; i++) {
        auto var = generator.getVar(20, 5);
        ASSERT_TRUE(var <= 20);
    }
}