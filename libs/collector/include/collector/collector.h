//
// Created by gts on 07.06.2024.
//
#pragma once

#include "context/context.h"

#include <array>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>

struct Collector {
public:
    explicit Collector(std::function<void(const char*, Context)>&& _senderData, Context context);

    void collectionData(const int* data, size_t sizeData, Context context);

    void start();
    void stop();

private:
    std::function<void(const char*, Context)> senderData;
    Context context;

    std::vector<std::string> buffer;

    std::queue<const char*> collector;

    bool flag = true;
    std::mutex mtx;
    std::condition_variable cv;
    size_t counter{0};
};
