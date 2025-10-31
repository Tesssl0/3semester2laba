#include "util.h"
#include <iostream>

Array* RandomGenerator::generateRandomNumbers(int count, int minVal, int maxVal) {
    Array* numbers = new Array;
    init(*numbers);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(minVal, maxVal);

    for (int i = 0; i < count; ++i) {
        add(*numbers, std::to_string(dis(gen)));
    }

    return numbers;
}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

long long Timer::elapsedMillis() const {
    auto endTime = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}  