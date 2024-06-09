#include "context/parsercontext.h"

#include "parser/configuration.h"
#include "parser/xmlconfig.h"

#include <filesystem>
#include <format>
#include <iostream>

ParserContext::ParserContext(std::string filename) : filename(std::move(filename)) { }

Params ParserContext::parseFile() {
    XmlConfigSettings xmlConfig;
    ftime = std::filesystem::last_write_time(filename.c_str());

    auto cfg = xmlConfig.ConfigurationByFileName(filename.data());
    Configuration configuration(cfg);

    Params params;

    params.context.generateRangeValue  = configuration.getProperty<int>("R");
    params.context.stopCounterValue    = configuration.getProperty<size_t>("M");
    params.context.stopTimer           = configuration.getProperty<int>("T");
    params.context.stopCounterArray    = configuration.getProperty<size_t>("N");
    params.generateValueTime           = configuration.getProperty<int>("generateValueTime");
    params.timeCheckModificationParams = configuration.getProperty<int>("timeCheckModificationParams");
    return params;
}
bool ParserContext::fileIfModification() {
    if(ftime != std::filesystem::last_write_time(filename.c_str())) {
        std::cout << std::format("File has been changed ", ftime);
        return true;
    }

    return false;
}
