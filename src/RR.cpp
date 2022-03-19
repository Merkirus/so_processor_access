//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#include <iostream>
#include "Random.h"
#include "RR.h"
#include "Generator.h"

void RR::run() {
    while (!v.empty() && rozmiar<=250) {
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
        }
    }
    std::cout << "Średni czas: " << (count+kontekst)/rozmiar << '\n';
}

RR::RR(std::vector<Proces> v, int interwal) : v{v}, rozmiar{static_cast<int>(v.size())}, count{0}, kontekst{0}, add{0}, interwal{interwal} {}

void RR::calculate(std::__wrap_iter<Proces*> begin, std::__wrap_iter<Proces*> end) {
    for (auto it = begin; it != end; ++it) {
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
    }
}
