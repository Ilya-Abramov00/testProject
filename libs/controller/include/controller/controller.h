//
// Created by gts on 07.06.2024.
//

#pragma once

#include "collector.h"
#include "context/context.h"

#include <array>
#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

class Controller {
public:
    Controller(std::function<int(int, int)>&& getterData, std::function<Context()>&& getterParams,
               std::function<bool()>&& checkerModificationData, std::function<void(std::string_view)>&& senderData);

    void start();
    void stop();

private:
    void processingWriteBuf();
    void processingGetParams();
    void processingSenderData();

    void writeBuf();

    std::function<int(int, int)> getterData;
    std::function<Context()> getterParams;
    std::function<bool()> checkerModificationParams;

    Context params;
    Collector collector;

    bool flagProcessing{true};
    std::unique_ptr<std::thread> threadWriteBuf;
    std::unique_ptr<std::thread> threadGetParams;
    std::unique_ptr<std::thread> threadSenderData;

    std::vector<int> bufDataGetter;

    int counter{0};

    std::mutex mutex;

    int generateRangaValue;
    int generateTime;

    std ::chrono::system_clock::time_point startTime;
};
