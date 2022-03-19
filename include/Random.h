//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#ifndef SOLAB1_RANDOM_H
#define SOLAB1_RANDOM_H

#include <random>

class Random {
public:
    Random()=default;
    static int guess();
private:
    static std::random_device rd;
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> guessNumber;
};

#endif //SOLAB1_RANDOM_H
