#pragma once
#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <thread>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double, std::milli>> timePoint;
public:
    Timer() :
        timePoint{ std::chrono::steady_clock::now() } {
    };
    std::chrono::duration<double, std::milli> tick(const double fps);
};

#endif