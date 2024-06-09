//
// Created by gts on 07.06.2024.
//
#include "SQLiteCpp/SQLiteCpp.h"
#pragma once

class DataBase {
public:
    DataBase();

    void writeData(std::string_view data);

private:
    SQLite::Database db;
    size_t id = 0;
};
