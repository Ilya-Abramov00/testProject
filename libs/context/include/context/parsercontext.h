//
// Created by gts on 07.06.2024.
//
#pragma once

#include "context.h"

#include <memory>
#include <string>

class ParserContext {
public:
    explicit ParserContext(std::string filename);

    const Context& parseFile();

    const Context& parseFileIfModification(size_t timeChecker);

private:
    std::string filename;
    Context params;
};
