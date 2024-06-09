//
// Created by gts on 07.06.2024.
//
#include "database/database.h"

#include "context/context.h"

#include <iostream>
#include <iterator>

DataBase::DataBase() : db("DataBase.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db.exec("DROP TABLE IF EXISTS generate");

    std::string typeData = "( value VARCHAR(" + std::to_string(bufSize) + std::string("))");

    db.exec("CREATE TABLE generate " + typeData);
}
void DataBase::writeData(std::string_view data) {
    // Begin transaction
    SQLite::Transaction transaction(db);

    // Prepare query
    SQLite::Statement query{db, "INSERT INTO generate (value) VALUES (?)"};

    // Collection to save in database

    query.bind(1, data.data());
    query.exec();
    query.reset();

    // Commit transaction
    transaction.commit();

    std::cout << "WRITE BASE DATA " << ++id << std::endl;
}
