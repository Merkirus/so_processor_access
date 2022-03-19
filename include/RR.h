//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#ifndef SOLAB1_RR_H
#define SOLAB1_RR_H

#include <vector>
#include "Proces.h"

class RR {
public:
    RR(std::vector<Proces> v, int interwal);
    void calculate(std::__wrap_iter<Proces*> begin, std::__wrap_iter<Proces*> end);
    void run();
private:
    std::vector<Proces> v;
    int rozmiar;
    int count;
    int kontekst;
    int add;
    int interwal;
};

#endif //SOLAB1_RR_H
