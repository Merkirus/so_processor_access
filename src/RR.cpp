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
        // Iteruje nowo dodane procesy
        if (add > 0) {
            int temp = add;
            add = 0;
            calculate(v.end()-temp, v.end());
        } else {
            calculate(v.begin(), v.end());
        }
        auto end = std::remove_if(v.begin(),
         v.end(),
         [](Proces& p) {return p.getWaga() <= 0;});
        v.erase(end, v.end());
        for (int i=0; i < add; ++i) {
            v.push_back(Generator::generujProces());
            v.at(v.size()-1).setIndex(rozmiar-add+i);
            wagaAdd += v.at(v.size()-1).getWaga();
        }
    }
}

RR::RR(std::vector<Proces> v, int interwal) :
v{v},
dane{},
rozmiar{static_cast<int>(v.size())},
count{0},
kontekst{0},
add{0},
interwal{interwal},
wagaInit{0},
wagaAdd{0} {
    int sum = 0;
    for_each(v.begin(), v.end(), [&](Proces& p) {sum+=p.getWaga();});
    wagaInit = sum;
}

void RR::calculate(std::__wrap_iter<Proces*> begin, std::__wrap_iter<Proces*> end) {
    for (auto it = begin; it != end; ++it) {
        int czas = it->getWaga();
        count += it->getWaga()>=interwal ? interwal : it->getWaga();
        it->setWaga(interwal);
        int zmienna = it->getWaga() >= interwal ? interwal : it->getWaga();
        for (int i = 0; i < zmienna; ++i) {
            if (Random::guess() == 1) {
                ++add;
                ++rozmiar;
            }
        }
        ++kontekst;
        auto match = dane.find(it->getIndex());
        if (match != dane.end()) {
            std::vector<int> temp;
            temp.reserve(match->second.size() + 1);
            temp.insert(temp.begin(), match->second.begin(), match->second.end());
            temp.push_back(it->getOczekiwanie());
            match->second = temp;
        } else {
            dane.insert(std::pair<int, std::vector<int>> (it->getIndex(), std::vector{it->getOczekiwanie()}));
        }
        for_each(v.begin(), v.end(), [&](Proces& p) {p.setOczekiwanie(czas);});
        it->zeroOczekiwanie();
    }
}

void RR::display() {
    std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
    std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
    std::cout << "Średnia waga procesu: " << count / rozmiar << '\n';
    std::cout << "Całkowity czas wykonania: " << count+kontekst << '\n';
    std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    for (int i=0; i < rozmiar; ++i) {
        auto temp = dane.find(i);
        int sum = 0;
        for (int elem : temp->second) {
            std::cout << elem << '\n';
            sum+=elem;
        }
        std::cout << "Index: " << temp->first << " Średni czas oczekiwania: " << sum/temp->second.size() << '\n';
    }
}
