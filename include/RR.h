//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#ifndef RR_H
#define RR_H

#include <vector>
#include <map>
#include "Proces.h"

class RR {
public:
    RR(std::vector<Proces> v, int interwal);
    void calculate(int shift);
    void run();
    void display();
private:
    std::vector<Proces> v;
    std::map<int, std::vector<int>> dane;
    int rozmiar;
    int count;
    int kontekst;
    int add;
    bool nowyProces;
    int interwal;
    int wagaInit;
    int wagaAdd;
};

#endif //RR_H
