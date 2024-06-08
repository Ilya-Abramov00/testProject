//
// Created by gts on 07.06.2024.
//
#include "SQLiteCpp/SQLiteCpp.h"
#pragma once

class DataBase {
public:
    DataBase();

    void writeData();

private:
    SQLite::Database db;
};
