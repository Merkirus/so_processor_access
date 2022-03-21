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
   this->waga -= 1;
}

void Proces::setWaga(int waga) {
    this->waga = waga;
}

int Proces::getOczekiwanie() const {
    return oczekiwanie;
}

void Proces::addOczekiwanie(int czas) {
    this->oczekiwanie += czas;
}

void Proces::zeroOczekiwanie() {
    this->oczekiwanie = 0;
}

void Proces::setIndex(int indeks) {
    this->index = indeks;
}

int Proces::getIndex() const {
    return index;
}

bool Proces::operator==(const Proces& p) {
    return (this == &p);
}

