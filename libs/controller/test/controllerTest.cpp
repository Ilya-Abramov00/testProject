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
    Context params;
    ParserContext parserContext;
    DataBase db;
};

TEST_F(DataBaseTest, System) {
    params = parserContext.parseFile();

    auto getterData = [this](int R, int generateTime) -> int {
        if(R != params.generateRangeValue && generateTime != params.generateValueTime) {
            throw std::runtime_error("проверка на корректность изменение параметров из другого потока не прошла");
        }

        return generator.getVar(R, generateTime);
    };

    auto getterParams = [this]() -> Context {
        params.generateRangeValue          = generator.getVar(100, 0);
        params.generateValueTime           = generator.getVar(25, 0);
        params.stopCounterValue            = generator.getVar(bufSize, 0);
        params.stopTimer                   = generator.getVar(500, 0);
        params.stopCounterArray            = generator.getVar(bufCounter, 0);
        params.timeCheckModificationParams = generator.getVar(600, 0);

        std::cout << "\n\n\n       PARAMS MODIFICATION \n" << params << std::endl;
        return params;
    };

    auto dataWritter = [this](std::string_view data) {
        db.writeData(data);
    };

    auto checkerParamsModification = [this]() -> bool {
        return (2 > generator.getVar(100, 0)); // случайно изменяем параметры в случайный момент времени
    };

    Controller controller(std::move(getterData), std::move(getterParams), std::move(checkerParamsModification),
                          std::move(dataWritter));

    controller.start();
    std::this_thread::sleep_for(std::chrono::seconds(15));
    std::cout << "SIGNAL STOP" << std::endl;
    controller.stop();
}