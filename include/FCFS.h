//
// Created by Rafał Mielniczuk on 19/03/2022.
//

#ifndef SOLAB1_FCFS_H
#define SOLAB1_FCFS_H

#include <vector>
#include "Proces.h"

class FCFS {
public:
    FCFS(std::vector<Proces> v);
    void run();
private:
    std::vector<Proces> v;
    std::vector<int> dane;
    int rozmiar;
    int count;
    int kontekst;
    int add;
};

#endif //SOLAB1_FCFS_H
