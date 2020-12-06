#ifndef WOLFENSTEIN3D_TIMER_H
#define WOLFENSTEIN3D_TIMER_H

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point time1{};
    std::chrono::high_resolution_clock::time_point time2{};

public:
    //Starts the timer
    void start();

    //Returns time passed since start in milliseconds
    double getTime();
};

#endif  // WOLFENSTEIN3D_TIMER_H
