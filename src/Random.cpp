//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#include "Random.h"

int Random::guess() {
    return guessNumber(mt);
}

std::random_device Random::rd = std::random_device();
std::mt19937 Random::mt = std::mt19937(rd());
std::uniform_int_distribution<int> Random::guessNumber = std::uniform_int_distribution<int>(1,20);
