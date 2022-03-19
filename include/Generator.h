//
// Created by Rafał Mielniczuk on 15/03/2022.
//

#ifndef SOLAB1_GENERATOR_H
#define SOLAB1_GENERATOR_H

#include <vector>
#include <random>
#include "Proces.h"

class Generator{
public:
    Generator()=default;
    ~Generator() = default;
    static std::vector<Proces> generujProcesy(int liczba);
    static Proces generujProces();
private:
    static std::default_random_engine generator;
    static std::normal_distribution<double> distribution;
    static double mean;
    static double dev;
    static double randomize();
};

#endif //SOLAB1_GENERATOR_H
