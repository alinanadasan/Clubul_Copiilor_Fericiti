//
// Created by Alina on 02/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_COPIL_H
#define CLUBUL_COPIILOR_FERICITI_COPIL_H

#include "Persoana.h"

// Copil = Persoana care participa la cursuri.
// E derivata din Persoana, deci mosteneste id, nume, prenume.
class Copil final : public Persoana {
private:
    int varsta_; // varsta copil

public:
    // Constructor
    Copil(std::string nume, std::string prenume, int varsta);

    Copil(const Copil&) = default;
    Copil& operator=(const Copil&) = default;

    ~Copil() override = default;

    std::string tip() const override { return "Copil"; }

    void afiseaza(std::ostream& out) const override;
    void citeste(std::istream& in) override;

    int varsta() const noexcept { return varsta_; }
    void setVarsta(int varsta);
};

#endif // CLUBUL_COPIILOR_FERICITI_COPIL_H
