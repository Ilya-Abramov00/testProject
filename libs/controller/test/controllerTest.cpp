#include "controller/controller.h"

#include "context/context.h"
#include "context/parsercontext.h"
#include "generator/generator.h"

#include <gtest/gtest.h>

#define logQ(s) std::cout << #s << " : " << s << std::endl;

class DataBaseTest : public testing::Test {
public:
    DataBaseTest() : fileName("params.xml"), parserContext(fileName) { }

    Generator<int> generator;
    Context params;
    std::string fileName;
    ParserContext parserContext;
};

TEST_F(DataBaseTest, start) {
    params = parserContext.parseFile();

    auto getterData = [this](int R, int generateTime) -> int {
        if(R != params.generateRangeValue && generateTime != params.generateValueTime) {
            throw "проверка на корректность изменение параметров из другого потока не прошла";
        }

        auto value = generator.getVar(R, generateTime);

        logQ(value);
        return value;
    };

    auto getterParams = [this]() -> Context {
        params.generateRangeValue = generator.getVar(500, 10);
        params.generateValueTime  = generator.getVar(50, 10);
        params.stopCounterValue   = generator.getVar(500, 10);
        params.stopTimer          = generator.getVar(1000, 10);

        std::cout << "\n\n\n       PARAMS MODIFICATION \n" << params << std::endl;
        return params;
    };

    auto dataWritter = [this](int*, size_t M) {
    };

    auto checkerParamsModification = [this]() -> bool {
        return (10 > generator.getVar(50, 10)); // случайно изменяем параметры в случайный момент времени
    };
    Controller controller(std::move(getterData), std::move(getterParams), std::move(checkerParamsModification),
                          std::move(dataWritter));

    controller.start();
    std::this_thread::sleep_for(std::chrono::seconds(15));
    controller.stop();
}