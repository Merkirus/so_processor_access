//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
public:
    Random()=default;
    static int guess();
    static int guess(int mnoznik);
private:
    static std::random_device rd;
    static std::mt19937 mt;
    static std::uniform_int_distribution<int> guessNumber;
};

#endif //RANDOM_H
