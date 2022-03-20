//
// Created by Rafał Mielniczuk on 19/03/2022.
//

#include <iostream>
#include "Random.h"
#include "FCFS.h"
#include "Generator.h"

FCFS::FCFS(std::vector<Proces> v) :
v{v},
dane{},
rozmiar{static_cast<int>(v.size())},
count{0},
kontekst{0},
wagaInit{0},
wagaAdd{0} {
    int sum = 0;
    for_each(v.begin(), v.end(), [&](Proces& p) {sum+=p.getWaga();});
    wagaInit = sum;
}

void FCFS::run() {
    while (!v.empty() && rozmiar != 200) {
        int czas = v.front().getWaga();
        while (v.front().getWaga()>0) {
            v.front().setWaga();
            if (Random::guess() == 1) {
                v.push_back(Generator::generujProces());
                wagaAdd += v.at(v.size()-1).getWaga();
                ++rozmiar;
            }
            ++count;
        }
        dane.push_back(v.front().getOczekiwanie());
        v.erase(v.begin());
        // Kontekst nie uwzględniony w oczekiwaniu procesu
        for_each(v.begin(), v.end(), [&](Proces& p) {p.setOczekiwanie(czas);});
        ++kontekst;
    }
}

void FCFS::display() {
    std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
    std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
    std::cout << "Średnia waga procesu: " << count/rozmiar << '\n';
    std::cout << "Całkowity czas: " << count+kontekst << '\n';
    std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    for (int i=0; i < dane.size(); ++i) {
        std::cout << "Index: " << i << " Czas oczekiwania: " << dane.at(i) << '\n';
    }
}
