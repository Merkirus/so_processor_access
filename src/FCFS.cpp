//
// Created by Rafał Mielniczuk on 19/03/2022.
//

#include <iostream>
#include "Random.h"
#include "FCFS.h"
#include "Generator.h"

FCFS::FCFS(std::vector<Proces> v) : v{v}, dane{}, rozmiar{static_cast<int>(v.size())}, count{0}, kontekst{0}, add{0} {}

void FCFS::run() {

    while (!v.empty() && rozmiar != 20000) {
        int czas = v.front().getWaga();
        while (v.front().getWaga()>0) {
            v.front().setWaga();
            if (Random::guess() == 1) {
                v.push_back(Generator::generujProces());
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

    std::cout << "Średni czas: " << (count+kontekst) / rozmiar << '\n';
    std::cout << "Oczekiwanie" << '\n';
    for (int i=0; i < dane.size(); ++i) {
        std::cout << "Index: " << i << " Czas: " << dane.at(i) << '\n';
    }
}
