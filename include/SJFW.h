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
	void runIt();
	void displayIt();
private:
	std::vector<Proces> v;
	std::map<int, int> dane;
	int rozmiar;
	int count;
	int kontekst;
	int add;
	int wagaInit;
	int wagaAdd;
};

#endif //SJFW_H
