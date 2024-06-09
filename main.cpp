#include "collector/collector.h"
#include "context/context.h"
#include "context/parsercontext.h"
#include "controller/controller.h"
#include "database/database.h"
#include "generator/generator.h"

int main(int argc, char** argv) {
    Generator<int> generator;
    ParserContext parserContext("../../../config/params.xml");
    DataBase db;

    auto getterData = [&generator](int R, int generateTime) -> int {
        return generator.getVar(R, generateTime);
    };

    auto getterParams = [&parserContext]() -> Params {
        auto params = parserContext.parseFile();
        std::cout << "\n\n\n          PARAMS  \n" << params << std::endl;
        return params;
    };

    auto dataWritter = [&db](const char* data, Context context) {
        db.writeData(data, context);
    };

    auto checkerParamsModification = [&parserContext]() -> bool {
        return parserContext.fileIfModification();
    };

    Controller controller(std::move(getterData), std::move(getterParams), std::move(checkerParamsModification),
                          std::move(dataWritter));

    controller.start();

    char c;
    while((c = getchar()) != 'a') { }
    std::cerr << "STOP";
    controller.stop();

}
