//
// Created by Rafał Mielniczuk on 15/03/2022.
//

#include "Proces.h"
#include <cmath>

Proces::Proces(int waga) : waga{abs(waga) == 0 ? 1 : abs(waga)}, oczekiwanie{0}, index{0} {}

int Proces::getWaga() const {
    return waga;
}

void Proces::setWaga() {
    --waga;
}

void Proces::setWaga(int interwal) {
    waga -= interwal;
}

int Proces::getOczekiwanie() const {
    return oczekiwanie;
}

void Proces::setOczekiwanie(int czas) {
    oczekiwanie += czas;
}

void Proces::zeroOczekiwanie() {
    oczekiwanie = 0;
}

void Proces::setIndex(int indeks) {
    index = indeks;
}

int Proces::getIndex() const {
    return index;
}

bool Proces::operator==(const Proces& p) {
    return (this == &p);
}

