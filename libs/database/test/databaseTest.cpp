#include "database/database.h"

#include "context/context.h"
#include "generator/generator.h"

#include <gtest/gtest.h>

#define logQ(s) std::cout << #s << " : " << s << std::endl;

class DataBaseTest : public testing::Test {
public:
    Generator<int> generator;
    Context params;
};

TEST_F(DataBaseTest, start) {
    params.generateRangeValue = 30;
    params.generateTime       = 100;
    params.stopCounterValue   = 50;
    params.stopTimer          = 500;

    auto getterData = [this](int, int) {
        auto value = generator.getVar(params.generateRangeValue, params.generateTime);
        logQ(value);
        return value;
    };
    auto getterParams = [this]() -> const Context& {
        return params;
    };
    auto dataWritter = [](int*, size_t) {
    };
    DataBase controller(std::move(getterData), std::move(getterParams), std::move(dataWritter));
    controller.processing();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    controller.stop();
}