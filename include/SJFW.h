//
// Created by Rafał Mielniczuk on 17/03/2022.
//

#ifndef SJFW_H
#define SJFW_H

#include <vector>
#include <map>
#include "Proces.h"

class SJFW {
public:
	SJFW(std::vector<Proces> v);
	void run();
	void display();
private:
	std::vector<Proces> v;
	std::map<int, long> dane;
	std::map<int, int> wagi;
	int rozmiar;
	int count;
	int kontekst;
	int add;
	int wagaInit;
	int wagaAdd;
};

#endif //SJFW_H
