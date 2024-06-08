//
// Created by gts on 07.06.2024.
//
#pragma once

#include <cstddef>
#include <ostream>

constexpr size_t bufSize    = 1'000;
constexpr size_t bufCounter = 20;

struct Context {
public:
    int generateRangeValue{}; // R
    int generateValueTime{};

    int stopTimer{};           // T
    size_t stopCounterValue{}; // M

    size_t stopCounterArray{0}; // N
    int timeCheckModificationParams{};

    void validParams() const {
        if(stopCounterValue > bufSize) {
            throw std::runtime_error("very big rangeCounter");
        }
    }

private:
};
std::ostream& operator<<(std::ostream& os, Context const& m) {
    return os << "R = " << m.generateRangeValue << "\n"
              << "T = " << m.stopTimer << "\n"
              << "M = " << m.stopCounterValue << "\n"
              << "N = " << m.stopCounterArray << "\n"
              << "generateTime = " << m.generateValueTime << "\n"
              << "timeCheckModificationParams = " << m.timeCheckModificationParams << "\n"
              << std::endl;
}
