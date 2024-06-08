#include "context/parsercontext.h"

#include "parser/configuration.h"
#include "parser/xmlconfig.h"

ParserContext::ParserContext(std::string filename) : filename(std::move(filename)) { }

const Context& ParserContext::parseFile() {
    XmlConfigSettings xmlConfig;

    auto cfg = xmlConfig.ConfigurationByFileName(filename.data());
    Configuration configuration(cfg);

    params.generateRangeValue = configuration.getProperty<int>("R");
    params.stopCounterValue   = configuration.getProperty<int>("M");
    params.stopTimer          = configuration.getProperty<int>("T");
    params.generateTime       = configuration.getProperty<int>("generateTime");
    return params;
}
const Context& ParserContext::parseFileIfModification(size_t timeChecker) {
    return parseFile();
}
