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
        while (v.front().getWaga()>0) {
            v.front().setWaga();
            auto match = dane.find(v.front().getIndex());
            if (match != dane.end()) {
                match->second += v.front().getOczekiwanie();
            } else {
                dane.insert(std::pair<int,int> (v.front().getIndex(), v.front().getOczekiwanie()));
            }
            for_each(v.begin(), v.end(), [&](Proces& p) {p.setOczekiwanie(1);});
            v.front().zeroOczekiwanie();
            if (Random::guess() == 1) {
                v.push_back(Generator::generujProces());
                wagaAdd += v.at(v.size()-1).getWaga();
                ++rozmiar;
                v.at(v.size()-1).setIndex(rozmiar-1);
                auto temp = v.at(v.size()-1);
                wagi.insert(std::pair<int,int> (temp.getIndex(), temp.getWaga()));
                sort(v.begin(), v.end(), [](Proces& p1, Proces& p2) -> bool {return p1.getWaga() < p2.getWaga();});
                if (temp == v.front()) {
                	++kontekst;
                }
            }
            ++count;
            if (v.front().getWaga() <= 0) {
                v.erase(v.begin());
            }
        }
        ++kontekst;
	}
}

void SJFW::display() {
	std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
	std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
	std::cout << "Średnia waga procesu: " << count/rozmiar << '\n';
    std::cout << "Całkowity czas wykonania: " << count+kontekst << '\n';
    std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    for (int i=0; i < dane.size(); ++i) {
    	std::cout << "Index: " << i << " Waga: " << wagi.at(i)  << " Czas oczekiwania: " << dane.at(i) << '\n';
    }
    if (!v.empty()) {
    	std::cout << "Procesy zagłodzone: " << '\n';
    	for (Proces p : v) {
    		std::cout << "Index: " << p.getIndex() << " Waga: " << p.getWaga() << '\n';
    	}
    }
}
