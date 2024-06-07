//
// Created by gts on 07.06.2024.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <random>
#include <thread>

#define log(s) std::cout << #s << " : " << s << std::endl;

template<typename type>
class Generator {
public:
    Generator() : gen(rd()) { }

    type getVar(int R, int timeGenerate) {
        std::uniform_int_distribution<type> distrVar(0, R);
        std::uniform_int_distribution distrTime(0, timeGenerate);

        int var = distrVar(gen);
        log(var);
        std::this_thread::sleep_for(std::chrono::milliseconds(distrTime(gen)));
        return var;
    }

private:
    std::random_device rd;
    std::mt19937 gen;
};

#endif // GENERATOR_H
