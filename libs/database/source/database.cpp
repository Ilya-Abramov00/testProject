//
// Created by gts on 07.06.2024.
//
#include "database/database.h"

#include "context/context.h"

constexpr int timeGenerate = 100;
#define logQ(s) std::cout << #s << " : " << s << std::endl;

DataBase::DataBase(std::function<int(int, int)>&& _getterData, std::function<const Context&()>&& getterParams,
                   std::function<void(int*, size_t)>&& _dataWriter) :
    getterData(std::move(_getterData)),
    dataWriter(std::move(_dataWriter)), params(getterParams()) { }

void DataBase::processing() {
    thread = std::make_unique<std::thread>([this]() {
        try {
            while(flagProcessing) {
                checkParams();
                writeBuf();
            }
        } catch(std::runtime_error& er) {
            std::cerr << "invalid Params " << er.what();
        }
    });
}

void DataBase::writeBuf() {
    data[counter] = getterData(params.generateRangeValue, timeGenerate);
    if(params.generateRangeValue == ++counter) {
        counter = 0;
        dataWriter(data, params.stopCounterValue);
    };
}

void DataBase::stop() {
    flagProcessing = false;
    thread->join();
}

void DataBase::checkParams() {
    if(params.stopCounterValue > bufSize) {
        throw std::runtime_error("very big rangeCounter");
    }
}
