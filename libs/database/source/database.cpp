//
// Created by gts on 07.06.2024.
//
#include "database/database.h"

#include "SQLiteCpp/SQLiteCppExport.h"
#include "context/context.h"

#include <vector>

DataBase::DataBase() : db("DataBase.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db.exec("DROP TABLE IF EXISTS Generator_Values");

    std::string counterСolumn("");
    std::string value = "value";
    for(size_t i = 0; i != bufSize; i++) {
        counterСolumn += "value INTEGER,";
    }
    counterСolumn += "value INTEGER)";

    std::string a("CREATE TABLE Generator_Values (");
    std::string res(a + counterСolumn);
    db.exec(res.c_str());
}
void DataBase::writeData() {
    // Begin transaction
    SQLite::Transaction transaction(db);

    // Prepare query
    SQLite::Statement query{db, "INSERT INTO Generator_Values (value) VALUES (?)"};

    // Collection to save in database
    std::vector<int> values{1, 2, 3};

    for(const auto& v : values) {
        query.bind(1, v);
        query.exec();
        query.reset();
    }

    // Commit transaction
    transaction.commit();
}
