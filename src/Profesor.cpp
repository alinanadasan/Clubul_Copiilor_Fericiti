//
// Created by Alina on 02/01/2026.
//

#include "Profesor.h"

#include <stdexcept>   // std::invalid_argument
#include <utility>     // std::move
#include <ostream>
#include <istream>

Profesor::Profesor(std::string nume, std::string prenume, std::string email,
                   std::string materie, std::string nivel,
                   double tarifOra)
    : Instructor(std::move(nume), std::move(prenume),
                 std::move(email),
                 "profesor",  // specializare implicita pentru Profesori
                 tarifOra),
      materie_(std::move(materie)),
      nivel_(std::move(nivel)) {

    if (materie_.empty()) {
        throw std::invalid_argument("Materia profesorului nu poate fi goala.");
    }
    if (nivel_.empty()) {
        throw std::invalid_argument("Nivelul profesorului nu poate fi gol.");
    }
}

void Profesor::setMaterie(std::string materie) {
    if (materie.empty()) {
        throw std::invalid_argument("Materia profesorului nu poate fi goala.");
    }
    materie_ = std::move(materie);
}

void Profesor::setNivel(std::string nivel) {
    if (nivel.empty()) {
        throw std::invalid_argument("Nivelul profesorului nu poate fi gol.");
    }
    nivel_ = std::move(nivel);
}

void Profesor::afiseaza(std::ostream& out) const {
    Instructor::afiseaza(out);
    out << ", Materie=" << materie_
        << ", Nivel=" << nivel_;
}

void Profesor::citeste(std::istream& in) {
    // partea comuna (nume + prenume)
    Persoana::citeste(in);

    std::string email;
    std::string materieCitita;
    std::string nivelCitit;
    double tarifOra;

    in >> email >> materieCitita >> nivelCitit >> tarifOra;

    if (email.empty() || materieCitita.empty() || nivelCitit.empty() || tarifOra <= 0) {
        throw std::invalid_argument("Citire Profesor invalida.");
    }

    setEmail(std::move(email));
    setSpecializare("profesor");
    setTarifOra(tarifOra);

    materie_ = std::move(materieCitita);
    nivel_ = std::move(nivelCitit);
}

