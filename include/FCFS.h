//
// Created by Rafał Mielniczuk on 19/03/2022.
//

#ifndef FCFS_H
#define FCFS_H

#include <vector>
#include "Proces.h"

class FCFS {
public:
    FCFS(std::vector<Proces> v);
    void run();
    void display();
private:
    std::vector<Proces> v;
    std::vector<int> dane;
    int rozmiar;
    int count;
    int kontekst;
    int wagaInit;
    int wagaAdd;
};

#endif //FCFS_H
