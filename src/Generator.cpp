//
// Created by Rafał Mielniczuk on 15/03/2022.
//

#include "Generator.h"
#include <random>
#include <vector>

std::vector<Proces> Generator::generujProcesy(int liczba) {
    std::vector<Proces> v;
    v.reserve(liczba);
    for (int i=0; i < liczba; i++) {
        v.push_back(generujProces());
        v.at(i).setIndex(i);
    }
    return v;
}

Proces Generator::generujProces() {
    return Proces(randomize());
}

double Generator::randomize() {
    return distribution(generator);
}

double Generator::mean = 50.0;
double Generator::dev = 15.0;

std::default_random_engine Generator::generator = std::default_random_engine();

std::normal_distribution<double> Generator::distribution = std::normal_distribution(mean, dev);
