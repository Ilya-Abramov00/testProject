//
// Created by gts on 07.06.2024.
//
#include "controller/controller.h"

constexpr int timeGenerate = 100;
#define logQ(s) std::cout << #s << " : " << s << std::endl;

Controller::Controller(std::function<int(int, int)>&& _getterData, std::function<Context()>&& _getterParams,
                   std::function<bool()>&& _checkerModificationData, std::function<void(int*, size_t)>&& _dataWriter) :
    getterData(std::move(_getterData)),
    getterParams(std::move(_getterParams)), checkerModificationParams(std::move(_checkerModificationData)),
    dataWriter(std::move(_dataWriter)), params(getterParams()) {
    validParams();
}

void Controller::validParams() {
    if(params.stopCounterValue > bufSize) {
        throw std::runtime_error("very big rangeCounter");
    }
}
void Controller::start() {
    processingGetParams();
    processingWriteBuf();
}
void Controller::stop() {
    flagProcessing = false;
    threadGetParams->join();
    threadWriteBuf->join();
}

void Controller::processingWriteBuf() {
    threadWriteBuf = std::make_unique<std::thread>([this]() {
        while(flagProcessing) {
            writeBuf();
        }
    });
}

void Controller::writeBuf() {
    data[counter] = getterData(params.generateRangeValue, timeGenerate);
    if(params.generateRangeValue == ++counter) {
        counter = 0;
        dataWriter(data, params.stopCounterValue);
    };
}

void Controller::processingGetParams() {
    threadGetParams = std::make_unique<std::thread>([this]() {
        try {
            while(flagProcessing) {
                if(checkerModificationParams()) {
                    std::lock_guard<std::mutex> a(mutex);
                    params = getterParams();
                    validParams();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(timeCheckMs));
            }
        } catch(std::runtime_error& er) {
            std::cerr << "invalid Params " << er.what();
        }
    });
}
