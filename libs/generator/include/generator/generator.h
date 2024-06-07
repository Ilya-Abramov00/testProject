//
// Created by gts on 07.06.2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <atomic>
#include <climits>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

#define log(s) std::cout << #s << " : " << s << std::endl;

constexpr size_t bufSize = 1'000'000;

class Generator {
public:
    Generator();

    void addNoise(int R, int T, int M);
    void writeBuf(int M, int var);
    void stop();

private:
    std::atomic_bool flagProcessing{true};
    std::unique_ptr<std::thread> thread;
    std::random_device rd;
    std::mt19937 gen;

    int data[bufSize];
    int counter{0};
};

#endif // GENERATOR_H
