//
// Created by Rafał Mielniczuk on 15/03/2022.
//

#ifndef PROCES_H
#define PROCES_H

class Proces {
public:
    Proces(int waga);
    int getWaga() const;
    void setWaga();
    void setWaga(int interwal);
    int getOczekiwanie() const;
    void addOczekiwanie(int czas);
    void zeroOczekiwanie();
    void setIndex(int indeks);
    int getIndex() const;
    bool operator==(const Proces& p);
private:
    int waga;
    int oczekiwanie;
    int index;
};

#endif //PROCES_H
