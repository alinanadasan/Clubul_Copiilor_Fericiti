//
// Created by Alina on 02/01/2026.
//

#include "Copil.h"

#include <stdexcept>   // std::invalid_argument
#include <utility>     // std::move
#include <ostream>
#include <istream>

Copil::Copil(std::string nume, std::string prenume, int varsta)
    : Persoana(std::move(nume), std::move(prenume)), varsta_(varsta) {
    setVarsta(varsta_);
}

void Copil::setVarsta(int varsta) {
    // cursuri pentru copii 3-18 ani
    if (varsta < 3 || varsta > 18) {
        throw std::invalid_argument("Varsta copilului trebuie sa fie intre 3 si 18.");
    }
    varsta_ = varsta;
}

void Copil::afiseaza(std::ostream& out) const {
    Persoana::afiseaza(out);
    out << ", Varsta=" << varsta_;
}

void Copil::citeste(std::istream& in) {
    // citesc partea comuna (nume + prenume)
    Persoana::citeste(in);

    int v;
    in >> v;
    setVarsta(v);
}
