#include <algorithm>
#include <iostream>
#include "SJFW.h"
#include "Generator.h"
#include "Random.h"

SJFW::SJFW(std::vector<Proces> v) :
v{v},
dane{},
wagi{},
rozmiar{static_cast<int>(v.size())},
count{0},
kontekst{0},
add{0},
wagaInit{0},
wagaAdd{0} {
	int sum = 0;
	for_each(v.begin(), v.end(), [&](Proces& p) {sum+=p.getWaga();});
	wagaInit = sum;

	sort(v.begin(), v.end(), [](Proces& p1, Proces& p2) -> bool {return p1.getWaga() < p2.getWaga();});

    for_each(v.begin(), v.end(), [&](Proces& p) -> void {wagi.insert(std::pair<int,int> (p.getIndex(), p.getWaga()));});
}

void SJFW::run() {
    while (!v.empty() && rozmiar != 200) {
        bool changed = false;
        if (v.front().getWaga() > 0) {
            v.front().setWaga();
            ++count;
            if (Random::guess() == 1) {
                v.push_back(Generator::generujProces());
                v.back().setIndex(rozmiar);
                wagaAdd += v.back().getWaga();
                ++rozmiar;
                wagi.insert(std::pair<int,int> (v.back().getIndex(), v.back().getWaga()));
                changed = true;
            }
            auto curr = v.front();
            auto match = dane.find(curr.getIndex());
            if (match != dane.end()) {
                 match->second += curr.getOczekiwanie();
            } else {
                dane.insert(std::pair<int,long> (curr.getIndex(), curr.getOczekiwanie()));
            }
            for_each(v.begin(), v.end(), [&](Proces& p) {p.addOczekiwanie(1);});
            v.front().zeroOczekiwanie();
            if (changed) {
                sort(v.begin(), v.end(), [](Proces& p1, Proces& p2) -> bool {return p1.getWaga() < p2.getWaga();});
                v.front().zeroOczekiwanie();
                if (curr.getIndex() != v.front().getIndex()) {
                    ++kontekst;
                }
            }
        } else {
            v.erase(v.begin());
            ++kontekst;
        }
    }
}

void SJFW::display() {
	std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
	std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
    std::cout << "Waga całkowita procesów: " << wagaAdd+wagaInit << '\n';
	std::cout << "Średnia waga procesu: " << (wagaAdd+wagaInit)/rozmiar << '\n';
    std::cout << "Całkowity czas wykonania: " << count+kontekst << '\n';
    double stosunek = (double)kontekst/(double)(count+kontekst);
    printf("Stosunek kontekstu do czasu wykonania %.2f%%\n", stosunek*100);
    //std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    int suma = 0;
    for (int i=0; i < rozmiar; ++i) {
        auto match = dane.find(i);
        if (match != dane.end()) {
            suma += match->second;
            // std::cout << "Index: " << match->first  << " Średni czas oczekiwania: " << match->second << " Waga: " << wagi.at(match->first)  << '\n'; 
        }
    }
    std::cout << "Łączny średni czas oczekiwania: " << suma/rozmiar << '\n';
    if (!v.empty()) {
    	std::cout << "Procesy zagłodzone: " << '\n';
    	for (Proces p : v) {
            auto match = wagi.find(p.getIndex());
            if (match != wagi.end()) {
                if (match->second == p.getWaga() && rozmiar-p.getIndex() > rozmiar/10) {
    		      std::cout << "Index: " << p.getIndex() << " Waga: " << p.getWaga() << '\n';
                }
            }
    	}
    }
}
