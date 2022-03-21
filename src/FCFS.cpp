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
        v.front().setWaga(0);
        count += czas;
        for (int i=0; i < czas; ++i) {
            if (Random::guess() == 1) {
                v.push_back(Generator::generujProces());
                wagaAdd += v.back().getWaga();
                ++rozmiar;
            }
        }
        dane.push_back(v.front().getOczekiwanie());
        v.erase(v.begin());
        for_each(v.begin(), v.end(), [&](Proces& p) {p.addOczekiwanie(czas);});
        ++kontekst;
    }
}

void FCFS::display() {
    std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
    std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
    std::cout << "Waga całkowita procesów: " << wagaAdd+wagaInit << '\n';
    std::cout << "Średnia waga procesu: " << (wagaAdd+wagaInit)/rozmiar << '\n';
    std::cout << "Całkowity czas wykonania: " << count+kontekst << '\n';
    double stosunek = (double)kontekst/(double)(count+kontekst);
    printf("Stosunek kontekstu do czasu wykonania %.2f%%\n", stosunek*100);
    // std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    int suma = 0;
    for (int i=0; i < dane.size(); ++i) {
        suma += dane.at(i);
        // std::cout << "Index: " << i << " Czas oczekiwania: " << dane.at(i) << '\n';
    }
    std::cout << "Łączny średni czas oczekiwania: " << suma/rozmiar << '\n';
}
