#pragma once
#include <chrono>
#include <random>

namespace {
    int64_t seed { 0 };
    std::default_random_engine* generator { nullptr };
};

template<typename T> T randomBetween(T a, T b) {
    if (!generator) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator = new std::default_random_engine(seed);
    }
    std::uniform_int_distribution<T> distribution(a,b);

    return distribution(*generator);
}
