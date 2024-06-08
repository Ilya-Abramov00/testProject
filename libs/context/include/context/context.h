//
// Created by gts on 07.06.2024.
//
#pragma once

#include <cstddef>
#include <ostream>

struct Context {
public:
    int generateRangeValue{}; // R
    int generateValueTime{};

    int stopTimer{};           // T
    size_t stopCounterValue{}; // M

    int timeCheckModificationParams{};

private:
};
std::ostream& operator<<(std::ostream& os, Context const& m) {
    return os << "R = " << m.generateRangeValue << "\n"
              << "T = " << m.stopTimer << "\n"
              << "M = " << m.stopCounterValue << "\n"
              << "generateTime = " << m.generateValueTime << "\n"
              << "timeCheckModificationParams = " << m.timeCheckModificationParams << "\n"
              << std::endl;
}
