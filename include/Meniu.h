#ifndef CLUBUL_COPIILOR_FERICITI_MENIU_H
#define CLUBUL_COPIILOR_FERICITI_MENIU_H

#include <string>

#include "RegistruPersoane.h"
#include <istream>

class Meniu {
private:
    RegistruPersoane registru_;

    static int citesteInt(const std::string& mesaj);
    static double citesteDouble(const std::string& mesaj);
    static std::string citesteString(const std::string& mesaj);

    void ruleazaTestAutomatDinFisier(const std::string& fisier);
    // nou: pentru CI (cand inputul vine prin pipe)
    void ruleazaTestAutomatDinStream(std::istream& in, int nDejaCitit);

    void meniuManual();
    void meniuGestioneazaPersoane();

    void adaugaPersoanaManual();
    void afiseazaToate() const;
    void afiseazaDupaId() const;
    void stergeDupaId();
    void cautaDupaNume() const;
    void sorteazaPersoane();

    // Operatii specifice tipului (downcast + folosim getter/setter ca sa nu pice cppcheck)
    void operatiiSpecificeDowncast();
    void schimbaNumePrenume();
    void seteazaTelefonParinte();
    void asociazaCopilLaParinte();
    void modificaMaterieNivelProfesor();

public:
    Meniu() = default;
    void ruleaza();
};

#endif
