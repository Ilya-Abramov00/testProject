#include "database/database.h"

#include <gtest/gtest.h>

#define logQ(s) std::cout << #s << " : " << s << std::endl;

class DataBaseTest : public testing::Test {
public:
};

TEST_F(DataBaseTest, start) { }