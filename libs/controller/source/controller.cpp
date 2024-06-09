//
// Created by gts on 07.06.2024.
//
#include "controller/controller.h"

#include <cstring>

Controller::Controller(std::function<int(int, int)>&& _getterData, std::function<Params()>&& _getterParams,
                       std::function<bool()>&& _checkerModificationData,
                       std::function<void(const char*, Context)>&& _senderData) :
    getterData(std::move(_getterData)),
    getterParams(std::move(_getterParams)), checkerModificationParams(std::move(_checkerModificationData)),
    params(getterParams()), collector(std::move(_senderData), params.context) {
    bufDataGetter.reserve(bufCounter);
    params.context.validParams();
}

void Controller::start() {
    flagProcessing = true;
    processingGetParams();
    processingWriteBuf();
    processingSenderData();
}
void Controller::stop() {
    flagProcessing = false;
    collector.stop();
    threadGetParams->join();
    threadWriteBuf->join();
    threadSenderData->join();
}

void Controller::processingWriteBuf() {
    generateRangaValue = params.context.generateRangeValue;
    generateTime       = params.generateValueTime;
    startTime          = std::chrono::system_clock::now();

    threadWriteBuf = std::make_unique<std::thread>([this]() {
        while(flagProcessing) {
            writeBuf();
        }
    });
}

void Controller::writeBuf() {
    bufDataGetter.emplace_back(getterData(generateRangaValue, generateTime));

    std::lock_guard<std::mutex> a(mutex);
    generateRangaValue = params.context.generateRangeValue;
    generateTime       = params.generateValueTime;

    auto time
        = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime).count();
    if(params.context.stopCounterValue == bufDataGetter.size()
       || (time > params.context.stopTimer && bufDataGetter.size())) {
        collector.collectionData(bufDataGetter.data(), bufDataGetter.size(), params.context);
        bufDataGetter.resize(0);
        startTime = std::chrono::system_clock::now();
    };
}

void Controller::processingGetParams() {
    threadGetParams = std::make_unique<std::thread>([this]() {
        try {
            while(flagProcessing) {
                if(checkerModificationParams()) {
                    std::lock_guard<std::mutex> a(mutex);
                    params = getterParams();
                    params.context.validParams();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(params.timeCheckModificationParams));
            }
        } catch(std::runtime_error& er) {
            std::cerr << "invalid Params " << er.what();
        }
    });
}
void Controller::processingSenderData() {
    threadSenderData = std::make_unique<std::thread>([this]() { collector.start(); });
}
