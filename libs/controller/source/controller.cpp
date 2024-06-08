//
// Created by gts on 07.06.2024.
//
#include "controller/controller.h"

#include <cstring>

Controller::Controller(std::function<int(int, int)>&& _getterData, std::function<Context()>&& _getterParams,
                       std::function<bool()>&& _checkerModificationData,
                       std::function<void(int*, size_t)>&& senderData) :
    getterData(std::move(_getterData)),
    getterParams(std::move(_getterParams)), checkerModificationParams(std::move(_checkerModificationData)),
    senderData(std::move(senderData)), params(getterParams()) {
    validParams();
}

void Controller::validParams() const {
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
    generateRangaValue = params.generateRangeValue;
    generateTime       = params.generateValueTime;

    threadWriteBuf = std::make_unique<std::thread>([this]() {
        while(flagProcessing) {
            writeBuf();
        }
    });
}

void Controller::writeBuf() {
    bufDataGetter[counter++] = getterData(generateRangaValue, generateTime);

    std::lock_guard<std::mutex> a(mutex);
    generateRangaValue = params.generateRangeValue;
    generateTime       = params.generateValueTime;

    if(params.stopCounterValue == counter) {
        senderData(bufDataGetter, counter);
        counter = 0;
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
                std::this_thread::sleep_for(std::chrono::milliseconds(params.timeCheckModificationParams));
            }
        } catch(std::runtime_error& er) {
            std::cerr << "invalid Params " << er.what();
        }
    });
}
