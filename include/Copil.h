//
// Created by Alina on 02/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_COPIL_H
#define CLUBUL_COPIILOR_FERICITI_COPIL_H

#include "Persoana.h"

// Copil = Persoana care participa la cursuri.
// E derivata din Persoana, deci mosteneste id, nume, email si comportamentul de baza.
class Copil final : public Persoana {
private:
    int varsta_; // varsta copil

public:
    // Constructor
    Copil(std::string nume, std::string email, int varsta);

    // Constructor de copiere si operator=
    Copil(const Copil&) = default;
    Copil& operator=(const Copil&) = default;

    // Destructor
    ~Copil() override = default;

    // tip persoana
    std::string tip() const override { return "Copil"; }

    // Pentru afisare/citire
    void afiseaza(std::ostream& out) const override;
    void citeste(std::istream& in) override;

    // Get/set pentru varsta
    int varsta() const noexcept { return varsta_; }
    void setVarsta(int varsta);
};

#endif //CLUBUL_COPIILOR_FERICITI_COPIL_H