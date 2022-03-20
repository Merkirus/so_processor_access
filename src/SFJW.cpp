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
        auto curr = v.front();
        auto match = dane.find(curr.getIndex());
        if (match != dane.end()) {
             match->second.push_back(curr.getOczekiwanie());
        } else {
            dane.insert(std::pair<int, std::vector<int>> (curr.getIndex(), std::vector{curr.getOczekiwanie()}));
        }
        while (v.front().getWaga() > 0) {
            v.front().setWaga();
            for_each(v.begin(), v.end(), [&](Proces& p) {p.setOczekiwanie(1);});
            v.front().zeroOczekiwanie();
            if (Random::guess() == 1) {
                v.push_back(Generator::generujProces());
                wagaAdd += v.back().getWaga();
                v.back().setIndex(rozmiar);
                ++rozmiar;
                auto temp = v.back();
                wagi.insert(std::pair<int,int> (temp.getIndex(), temp.getWaga()));
                dane.insert(std::pair<int,int> (temp.getIndex(), temp.getOczekiwanie()));
                sort(v.begin(), v.end(), [](Proces& p1, Proces& p2) -> bool {return p1.getWaga() < p2.getWaga();});
                if (temp.getIndex() == v.front().getIndex()) {
                	++kontekst;
                    ++count;
                    break;
                }
            }
            ++count;
        }
        auto end = std::remove_if(v.begin(), v.end(), [](Proces& p) {return p.getWaga() <= 0;});
        v.erase(end, v.end());
        ++kontekst;
	}
}

void SJFW::display() {
    std::cout << "DANE: " << dane.size() << " ROZMAIR: " << rozmiar << " WAGA: " << wagi.size() << '\n';
	std::cout << "Waga początkowych procesów: " << wagaInit << '\n';
	std::cout << "Waga dodatkowych procesów: " << wagaAdd << '\n';
	std::cout << "Średnia waga procesu: " << count/rozmiar << '\n';
    std::cout << "Całkowity czas wykonania: " << count+kontekst << '\n';
    std::cout << "Oczekiwanie poszczególnych procesów: " << '\n';
    int suma = 0;
    for (int i=0; i < rozmiar; ++i) {
        auto temp = dane.find(i);
        int sum = 0;
        for (int elem : temp->second) {
            std::cout << elem << '\n';
            sum+=elem;
        }
        int temp2 = sum/temp->second.size();
        suma += temp2;
        std::cout << "Index: " << temp->first << " Średni czas oczekiwania: " << temp2  << '\n';
    }
    std::cout << "Łączny średni czas oczekiwania: " << suma/rozmiar << '\n';
    if (!v.empty()) {
    	std::cout << "Procesy zagłodzone: " << '\n';
    	for (Proces p : v) {
    		std::cout << "Index: " << p.getIndex() << " Waga: " << p.getWaga() << '\n';
    	}
    }
}
