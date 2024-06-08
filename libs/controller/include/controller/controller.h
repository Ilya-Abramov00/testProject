//
// Created by gts on 07.06.2024.
//

#pragma once

#include "context/context.h"

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

constexpr size_t bufSize     = 1'000'000;
constexpr size_t timeCheckMs = 500;

class Controller {
public:
    Controller(std::function<int(int, int)>&& getterData, std::function<Context()>&& getterParams,
             std::function<bool()>&& checkerModificationData, std::function<void(int*, size_t)>&& dataWriter);

    void start();
    void stop();

private:
    void processingWriteBuf();
    void processingGetParams();

    void writeBuf();
    void validParams();

    std::function<int(int, int)> getterData;
    std::function<Context()> getterParams;
    std::function<bool()> checkerModificationParams;
    std::function<void(int*, size_t)> dataWriter;

    Context params;

    std::atomic_bool flagProcessing{true};
    std::unique_ptr<std::thread> threadWriteBuf;
    std::unique_ptr<std::thread> threadGetParams;

    int data[bufSize];
    int counter{0};

    std::mutex mutex;
};
