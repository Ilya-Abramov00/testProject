//
// Created by gts on 07.06.2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <atomic>
#include <functional>
#include <iostream>
#include <memory>
#include <thread>

#define log(s) std::cout << #s << " : " << s << std::endl;

constexpr size_t bufSize = 1'000'000;

class DataBase {
public:
   DataBase(std::function<int(int, int)>&& getter_data) ;

    void addNoise(int R, int M);
    void writeBuf(int M, int var);
    void stop();

private:
    std::function<int(int, int)> getterData;

    std::atomic_bool flagProcessing{true};
    std::unique_ptr<std::thread> thread;

    int data[bufSize];
    int counter{0};
};

#endif // GENERATOR_H
