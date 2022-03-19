//
// Created by Rafał Mielniczuk on 15/03/2022.
//

#ifndef SOLAB1_PROCES_H
#define SOLAB1_PROCES_H

class Proces {
public:
    Proces(int waga);
    int getWaga() const;
    void setWaga();
    void setWaga(int interwal);
    int getOczekiwanie () const;
    void setOczekiwanie(int czas);
private:
    int waga;
    int oczekiwanie;
};

#endif //SOLAB1_PROCES_H
