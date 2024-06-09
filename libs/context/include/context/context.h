//
// Created by gts on 07.06.2024.
//
#pragma once

#include <cstddef>
#include <ostream>

constexpr size_t bufSize    = 50;
constexpr size_t bufCounter = 100;

struct Context {
public:
    size_t generateRangeValue{}; // R
    size_t stopTimer{};          // T
    size_t stopCounterValue{};   // M

    size_t stopCounterArray{}; // N
    void validParams() const {
        if(stopCounterValue > bufSize || (stopCounterArray > bufCounter)) {
            throw std::runtime_error("very big rangeCounter");
        }
    }
};
struct Params {
    Context context;
    int generateValueTime{};
    int timeCheckModificationParams{};
};

std::ostream& operator<<(std::ostream& os, Params const& m) {
    return os << "R = " << m.context.generateRangeValue << "\n"
              << "T = " << m.context.stopTimer << "\n"
              << "M = " << m.context.stopCounterValue << "\n"
              << "N = " << m.context.stopCounterArray << "\n"
              << "generateTime = " << m.generateValueTime << "\n"
              << "timeCheckModificationParams = " << m.timeCheckModificationParams << "\n"
              << std::endl;
}
