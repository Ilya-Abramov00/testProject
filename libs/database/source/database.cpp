//
// Created by gts on 07.06.2024.
//
#include "database/database.h"

#include <iostream>
#include <iterator>

DataBase::DataBase() : db("DataBase.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db.exec("DROP TABLE IF EXISTS generate");

    std::string typeData = "( value VARCHAR(" + std::to_string(bufSize)
        + "),  R INT , N INT , M INT ,T INT, recording_time CHARACTER(25) ) ";

    db.exec("CREATE TABLE generate " + typeData);
}
void DataBase::writeData(const char* data, Context context) {
    // Begin transaction
    SQLite::Transaction transaction(db);

    // Prepare query
    SQLite::Statement query{db, "INSERT INTO generate (value, R , N , M , T  , recording_time) VALUES (?,?,?,?,?,?)"};

    // Collection to save in database

    query.bind(1, data);
    query.bind(2, std::to_string(context.generateRangeValue));
    query.bind(2, std::to_string(context.stopCounterArray));
    query.bind(3, std::to_string(context.stopCounterValue));
    query.bind(3, std::to_string(context.stopTimer));

    time_t ttime = time(0);
    std::string time(ctime(&ttime));
    query.bind(4, time.c_str());

    query.exec();
    query.reset();
    // Commit transaction
    transaction.commit();

    std::cout << "WRITE BASE DATA " << ++id << std::endl;
}
