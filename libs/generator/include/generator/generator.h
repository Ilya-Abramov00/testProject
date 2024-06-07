//
// Created by gts on 07.06.2024.
//
#pragma once

#include <random>
#include <thread>

template<typename type>
class Generator {
public:
    Generator() : gen(rd()) { }

    type getVar(int R, int timeGenerate) {
        std::uniform_int_distribution<type> distrValue(0, R);
        std::uniform_int_distribution distrTime(0, timeGenerate);
        std::this_thread::sleep_for(std::chrono::milliseconds(distrTime(gen)));

        return distrValue(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
};
