#include <random>
#include "Variables.h"

template <typename T>
void swap(T& a, T& b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

int getRandom(int min, int max) {
    if (min > max)
        swap(min, max);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}