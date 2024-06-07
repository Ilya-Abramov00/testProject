//
// Created by gts on 07.06.2024.
//

#pragma once

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

constexpr size_t bufSize = 1'000'000;
struct Context;

class DataBase {
public:
    DataBase(std::function<int(int, int)>&& getterData, std::function<const Context&()>&& getterParams,
             std::function<void(int*, size_t)>&& dataWriter);

    void processing();
    void stop();

private:
    void writeBuf();
    void checkParams();

    std::function<int(int, int)> getterData;
    std::function<const Context&()> getterParams;
    std::function<void(int*, size_t)> dataWriter;
    const Context& params;

    std::atomic_bool flagProcessing{true};
    std::unique_ptr<std::thread> thread;

    int data[bufSize];
    int counter{0};
};
