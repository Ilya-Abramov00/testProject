//
// Created by gts on 07.06.2024.
//
#pragma once

#include "context.h"

#include <filesystem>
#include <memory>
#include <string>

class ParserContext {
public:
    explicit ParserContext(std::string filename);

     Context parseFile();
    bool fileIfModification();

private:
    std::string filename;
    std::filesystem::file_time_type ftime;
};
