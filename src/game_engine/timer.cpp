#include "timer.hpp"

std::chrono::duration<double, std::milli> Timer::tick(const double fps) {
    std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double, std::milli>> origTimepoint = timePoint;
    std::chrono::duration<double, std::milli> timeBetweenFrames(1000. / fps);
    timePoint += timeBetweenFrames;
    if (timePoint < std::chrono::steady_clock::now()) timePoint = std::chrono::steady_clock::now();
    else std::this_thread::sleep_until(timePoint);
    return timePoint - origTimepoint;
}