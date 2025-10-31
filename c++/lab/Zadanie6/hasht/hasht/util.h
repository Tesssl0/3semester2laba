#ifndef UTIL_H
#define UTIL_H

#include <random>
#include <chrono>
#include "array.h"

class RandomGenerator {
public:
    static Array* generateRandomNumbers(int count, int minVal = 0, int maxVal = 1000000);
};

class Timer {
private:
    std::chrono::high_resolution_clock::time_point startTime;

public:
    void start();
    long long elapsedMillis() const;
};

#endif