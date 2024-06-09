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
    explicit Collector(std::function<void(std::string_view)>&& _senderData, size_t sizeStopArray) ;

    void collectionData(int* data, size_t sizeData, size_t sizeCollector);

    void start() ;
    void stop() ;
    ~Collector();

private:
    void convertToString(int* data, size_t sizeData) ;

    std::function<void(std::string_view)> senderData;
    size_t sizeStopCollector{0};

    std::vector<std::string> buffer;

    std::queue<std::string_view> collector;

    bool flag = true;
    std::mutex mtx;
    std::condition_variable cv;
};
