//
// Created by Alina on 07/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_SORTARECOPIIDUPAVARSTA_H
#define CLUBUL_COPIILOR_FERICITI_SORTARECOPIIDUPAVARSTA_H
#include "StrategieSortare.h"
#include "Copil.h"

class SortareCopiiDupaVarsta : public StrategieSortare<Copil> {
public:
    bool compara(const Copil& a, const Copil& b) const override {
        return a.varsta() < b.varsta();
    }
};

#endif //CLUBUL_COPIILOR_FERICITI_SORTARECOPIIDUPAVARSTA_H