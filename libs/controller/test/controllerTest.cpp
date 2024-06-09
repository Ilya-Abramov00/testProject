#include "controller/controller.h"

#include "collector/collector.h"
#include "context/context.h"
#include "context/parsercontext.h"
#include "database/database.h"
#include "generator/generator.h"

#include <gtest/gtest.h>

class DataBaseTest : public testing::Test {
public:
    DataBaseTest() : fileName("params.xml"), parserContext(fileName) { }

    std::string fileName;
    Generator<int> generator;
    Params params;
    ParserContext parserContext;
    DataBase db;
};

TEST_F(DataBaseTest, System) {
    params = parserContext.parseFile();

    auto getterData = [this](int R, int generateTime) -> int {
        if(R != params.context.generateRangeValue && generateTime != params.generateValueTime) {
            throw std::runtime_error("проверка на корректность изменение параметров из другого потока не прошла");
        }

        return generator.getVar(R, generateTime);
    };

    auto getterParams = [this]() -> Params {
        params.context.generateRangeValue  = generator.getVar(100, 20);
        params.generateValueTime           = generator.getVar(30, 0);
        params.context.stopCounterValue    = generator.getVar(bufSize, 0);
        params.context.stopTimer           = generator.getVar(400, 0);
        params.context.stopCounterArray    = generator.getVar(bufCounter, 0);
        params.timeCheckModificationParams = generator.getVar(400, 0);

        std::cout << "\n\n\n       PARAMS MODIFICATION \n" << params << std::endl;
        return params;
    };

    auto dataWritter = [this](const char* data, Context context) {
        db.writeData(data, context);
    };

    auto checkerParamsModification = [this]() -> bool {
        return (6 > generator.getVar(150, 0)); // случайно изменяем параметры в случайный момент времени
    };

    Controller controller(std::move(getterData), std::move(getterParams), std::move(checkerParamsModification),
                          std::move(dataWritter));

    controller.start();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "SIGNAL STOP" << std::endl;
    controller.stop();
}

TEST_F(DataBaseTest, testSize) {
    auto getterData = [this](int R, int generateTime) -> int {
        if(R != params.context.generateRangeValue && generateTime != params.generateValueTime) {
            throw std::runtime_error("проверка на корректность изменение параметров из другого потока не прошла");
        }

        return generator.getVar(R, generateTime);
    };

    auto getterParams = [this]() -> Params {
        params.context.generateRangeValue  = generator.getVar(9, 20);
        params.generateValueTime           = generator.getVar(30, 0);
        params.context.stopCounterValue    = 5;
        params.context.stopTimer           = 5000;
        params.context.stopCounterArray    = 10;
        params.timeCheckModificationParams = generator.getVar(400, 0);

        std::cout << "\n\n\n       PARAMS MODIFICATION \n" << params << std::endl;
        return params;
    };

    auto dataWritter = [this](const char* data, Context context) {
        ASSERT_EQ(std::string(data).size(), params.context.stopCounterValue * 2);
        ASSERT_EQ(context.stopCounterArray, params.context.stopCounterArray);
        db.writeData(data, context);
    };

    auto checkerParamsModification = [this]() -> bool {
        return (3 > generator.getVar(150, 0)); // случайно изменяем параметры в случайный момент времени
    };

    Controller controller(std::move(getterData), std::move(getterParams), std::move(checkerParamsModification),
                          std::move(dataWritter));

    controller.start();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    std::cout << "SIGNAL STOP" << std::endl;
    controller.stop();
}