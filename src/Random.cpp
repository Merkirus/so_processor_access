//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#include "Random.h"

int Random::guess() {
    guessNumber = std::uniform_int_distribution<int>(1,200);
    return guessNumber(mt);
}

int Random::guess(int mnoznik) {
    int temp = 200/mnoznik;
    guessNumber = std::uniform_int_distribution<int>(1,temp);
    return guessNumber(mt);
}

std::random_device Random::rd = std::random_device();
std::mt19937 Random::mt = std::mt19937(rd());
std::uniform_int_distribution<int> Random::guessNumber;
