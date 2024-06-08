#include "controller/controller.h"

#include "context/context.h"
#include "context/parsercontext.h"
#include "generator/generator.h"

#include <gtest/gtest.h>

#define logQ(s) std::cout << #s << " : " << s << std::endl;

class DataBaseTest : public testing::Test {
public:
    DataBaseTest() : fileName("params.xml"), parserContext(fileName) { }

public:
    Generator<int> generator;
    Context params;
    std::string fileName;
    ParserContext parserContext;
};

TEST_F(DataBaseTest, start) {
    params = parserContext.parseFile();

    auto getterData = [this](int, int) {
        auto value = generator.getVar(params.generateRangeValue, params.generateTime);
        logQ(value);
        return value;
    };

    auto getterParams = [this]() -> Context {
        std::cout << params;
        return params;
    };

    auto dataWritter = [this](int*, size_t M) {
        ASSERT_EQ(params.stopCounterValue, M);
    };

    auto checkerParamsModification = []() -> bool {
        return false;
    };

    Controller controller(std::move(getterData), std::move(getterParams), std::move(checkerParamsModification),
                        std::move(dataWritter));

    controller.start();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    controller.stop();
}