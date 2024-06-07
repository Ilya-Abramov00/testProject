//
// Created by gts on 07.06.2024.
//

#include "database/database.h"
constexpr size_t timeGenerate = 100;

DataBase::DataBase(std::function<int(int, int)>&& _getterData) : getterData(std::move(_getterData)) { }

void DataBase::addNoise(int R, int M) {
    thread = std::make_unique<std::thread>([R, M, this]() {
        while(flagProcessing) {
            writeBuf(M, 0);
        }
    });
}

void DataBase::writeBuf(int M, int var) {
    log(var);
    data[counter] = var;
    if(M == ++counter) {
        counter = 0;
        // callback();
    };
}

void DataBase::stop() {
    flagProcessing = false;
    thread->join();
}