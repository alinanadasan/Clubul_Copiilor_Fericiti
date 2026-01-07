#ifndef CLUBUL_COPIILOR_FERICITI_MENIU_H
#define CLUBUL_COPIILOR_FERICITI_MENIU_H

#include <string>

#include "RegistruPersoane.h"

class Meniu {
private:
    RegistruPersoane registru_;

    static int citesteInt(const std::string& mesaj);
    static double citesteDouble(const std::string& mesaj);
    static std::string citesteString(const std::string& mesaj);

    void ruleazaTestAutomatDinFisier(const std::string& fisier);

    void meniuManual();
    void meniuGestioneazaPersoane();

    void adaugaPersoanaManual();
    void afiseazaToate() const;
    void afiseazaDupaId() const;
    void stergeDupaId();
    void cautaDupaNume() const;
    void sorteazaPersoane();
    void operatiiSpecificeDowncast(); // exemplu downcast

public:
    Meniu() = default;
    void ruleaza();
};

#endif
