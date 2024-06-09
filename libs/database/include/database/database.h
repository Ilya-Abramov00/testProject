//
// Created by gts on 07.06.2024.
//
#include "SQLiteCpp/SQLiteCpp.h"
#include "context/context.h"
#pragma once

class DataBase {
public:
    DataBase();

    void writeData(const char* data, Context context);

private:
    SQLite::Database db;
    size_t id = 0;
};
