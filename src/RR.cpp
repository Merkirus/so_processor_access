//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#include <iostream>
#include <algorithm>
#include "Random.h"
#include "RR.h"
#include "Generator.h"

void RR::run() {
    while (!v.empty() && rozmiar != 200) {
        add = 0;
        while (add != -1) {
            calculate(add);
        }
        auto end = std::remove_if(v.begin(),
         v.end(),
         [](Proces& p) {return p.getWaga() <= 0;});
        v.erase(end, v.end());
    }
}

RR::RR(std::vector<Proces> v, int interwal) :
v{v},
dane{},
rozmiar{static_cast<int>(v.size())},
count{0},
kontekst{0},
add{0},
nowyProces{false},
interwal{interwal},
wagaInit{0},
wagaAdd{0} {
    int sum = 0;
    for_each(v.begin(), v.end(), [&](Proces& p) {sum+=p.getWaga();});
    wagaInit = sum;
}

void RR::calculate(int shift) {
    for (int i=shift; i < v.size(); ++i) {
        ++add;
        int zmienna = v.at(i).getWaga() >= interwal ? interwal : v.at(i).getWaga();
        v.at(i).setWaga(v.at(i).getWaga()-zmienna);
        count += zmienna;
        for (int j=0; j < zmienna; ++j) {
            if (Random::guess() == 1) {
                nowyProces = true;
                v.push_back(Generator::generujProces());
                v.back().setIndex(rozmiar);
                wagaAdd += v.back().getWaga();
                ++rozmiar;
            }
        }
        auto match = dane.find(i);
        if  (match != dane.end()) {
            match->second.push_back(v.at(i).getOczekiwanie());
        } else {
            dane.insert(std::pair<int, std::vector<int>> (i, std::vector{v.at(i).getOczekiwanie()}));
        }
        for_each(v.begin(), v.end(), [&](Proces& p) {p.addOczekiwanie(zmienna);});
        v.at(i).zeroOczekiwanie();
        if (nowyProces) {
            nowyProces = false;
            ++kontekst;
            return;
        }
        ++kontekst;
    }
    add = -1;
}

void RR::display() {
    std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
    std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
    std::cout << "Waga całkowita procesów: " << wagaAdd+wagaInit << '\n';
    std::cout << "Średnia waga procesu: " << (wagaAdd+wagaInit)/rozmiar << '\n';
    std::cout << "Całkowity czas wykonania: " << count+kontekst << '\n';
    double stosunek = (double)kontekst/(double)(count+kontekst);
    printf("Stosunek kontekstu do czasu wykonania %.2f%%\n", stosunek*100);
    // std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    int suma = 0;
    for (int i=0; i < rozmiar; ++i) {
        auto temp = dane.find(i);
        if (temp != dane.end()) {
            int sum = 0;
            for (int elem : temp->second) {
                sum+=elem;
            }
            int temp2 = sum/temp->second.size();
            suma += temp2;
            // std::cout << "Index: " << temp->first << " Średni czas oczekiwania: " << temp2  << '\n';
        }
    }
    std::cout << "Łączny średni czas oczekiwania: " << suma/rozmiar << '\n';
}
