//
// Created by Alina on 02/01/2026.
//

#include "Profesor.h"

#include <stdexcept>
#include <utility>
#include <ostream>
#include <istream>

Profesor::Profesor(std::string nume, std::string email,
                   std::string materie, std::string nivel,
                   double tarifOra)
    // Profesor este Instructor, deci apelam constructorul din Instructor
    : Instructor(std::move(nume), std::move(email),
                 "materie_scolara", tarifOra),
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
    // afisam ce afiseaza Instructor (care afiseaza si Persoana)
    Instructor::afiseaza(out);

    // apoi completam cu ce e specific profesorului
    out << ", Materie=" << materie_
        << ", Nivel=" << nivel_;
}

void Profesor::citeste(std::istream& in) {
    // citim partea comuna de Instructor (nume, email, specializare, tarifOra)
    Instructor::citeste(in);

    in >> materie_ >> nivel_;

    if (materie_.empty() || nivel_.empty()) {
        throw std::invalid_argument("Citire Profesor invalida.");
    }
}
