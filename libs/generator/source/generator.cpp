//
// Created by gts on 07.06.2024.
//

#include "generator.h"

Generator::Generator() : rd(), gen(rd()) { }

void Generator::addNoise(int R, int T, int M) {
    thread = std::make_unique<std::thread>([R, T, M, this]() {
        std::uniform_int_distribution<> distrVar(0, R);
        std::uniform_int_distribution<> distrTime(0, T);
        while(flagProcessing) {
            int var = distrVar(gen);
            writeBuf(M,var);
            std::this_thread::sleep_for(std::chrono::milliseconds(distrTime(gen)));
        }
    });
}

void Generator::writeBuf(int M, int var) {
    log(var);
    data[counter] = var;
    if(M == ++counter) {
        counter = 0;
        //
    };
}

void Generator::stop() {
    flagProcessing = false;
    thread->join();
}