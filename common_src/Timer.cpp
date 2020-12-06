#include "Timer.h"

void Timer::start() {
    time1 = std::chrono::high_resolution_clock::now();
}

double Timer::getTime() {
    time2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> timeStep = time2 - time1;
    return timeStep.count();
}
