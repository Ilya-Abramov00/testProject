//
// Created by gts on 07.06.2024.
//
#pragma once

#include "context/context.h"

#include <array>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <queue>

struct Collector {
public:
    explicit Collector(std::function<void(int*, size_t)>&& _senderData) :
        senderData(std::move(_senderData)), flag(flag) { }

    void collectionData(int* data, size_t sizeData, const size_t sizeCollector) {
        std::unique_lock<std::mutex> lk(mtx);
        std::memcpy(buffer[counter], data, sizeData);
        collector.push({buffer[counter], sizeData});

        ++counter %= bufCounter;

        lk.unlock();
        cv.notify_one();
    }

    void start() {
        while(flag) {
            std::unique_lock<std::mutex> lk(mtx);
            cv.wait(lk, [this] { return (sizeStopCollector > collector.size()); });
            auto data = collector.back();
            senderData(data.pointer, data.size);
        }
    }
    void stop() {
        flag = false;
    }

private:
    std::function<void(int*, size_t)> senderData;

    int buffer[bufCounter][bufSize];
    struct Data {
        int* pointer;
        size_t size;
    };
    std::queue<Data> collector;

    size_t counter{0};
    size_t sizeStopCollector{0};
    bool flag = true;
    std::mutex mtx;
    std::condition_variable cv;
};
