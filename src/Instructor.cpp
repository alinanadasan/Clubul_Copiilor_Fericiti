//
// Created by Alina on 02/01/2026.
//

#include "Instructor.h"

#include <stdexcept>  // std::invalid_argument
#include <utility>    // std::move
#include <ostream>
#include <istream>

Instructor::Instructor(std::string nume, std::string email, std::string specializare, double tarifOra)
    : Persoana(std::move(nume), std::move(email)),
      specializare_(std::move(specializare)),
      tarifOra_(tarifOra) {

    if (specializare_.empty()) {
        throw std::invalid_argument("Specializarea instructorului nu poate fi goala.");
    }
    if (tarifOra_ <= 0) {
        throw std::invalid_argument("Tariful pe ora trebuie sa fie > 0.");
    }
}

void Instructor::setSpecializare(std::string specializare) {
    if (specializare.empty()) {
        throw std::invalid_argument("Specializarea instructorului nu poate fi goala.");
    }
    specializare_ = std::move(specializare);
}

void Instructor::setTarifOra(double tarifOra) {
    if (tarifOra <= 0) {
        throw std::invalid_argument("Tariful pe ora trebuie sa fie > 0.");
    }
    tarifOra_ = tarifOra;
}

Instructor& Instructor::operator+=(double suma) {
    if (suma <= 0) {
        throw std::invalid_argument("Suma pentru marire trebuie sa fie > 0.");
    }
    tarifOra_ += suma;
    return *this;
}

bool operator<(const Instructor& a, const Instructor& b) {
    return a.tarifOra() < b.tarifOra();
}

void Instructor::afiseaza(std::ostream& out) const {
    Persoana::afiseaza(out);
    out << ", Specializare=" << specializare_
        << ", TarifOra=" << tarifOra_;
}

void Instructor::citeste(std::istream& in) {
    Persoana::citeste(in);

    in >> specializare_ >> tarifOra_;

    if (specializare_.empty() || tarifOra_ <= 0) {
        throw std::invalid_argument("Citire Instructor invalida.");
    }
}
