//
// Created by Alina on 02/01/2026.
//

#include "Instructor.h"

#include <stdexcept>  // std::invalid_argument
#include <utility>    // std::move
#include <ostream>
#include <istream>

Instructor::Instructor(std::string nume, std::string prenume, std::string email,
                       std::string specializare, double tarifOra)
    : Persoana(std::move(nume), std::move(prenume)),
      email_(std::move(email)),
      specializare_(std::move(specializare)),
      tarifOra_(tarifOra) {

    if (email_.empty()) {
        throw std::invalid_argument("Emailul instructorului nu poate fi gol.");
    }
    if (specializare_.empty()) {
        throw std::invalid_argument("Specializarea instructorului nu poate fi goala.");
    }
    if (tarifOra_ <= 0) {
        throw std::invalid_argument("Tariful pe ora trebuie sa fie > 0.");
    }
}

void Instructor::setEmail(std::string email) {
    if (email.empty()) {
        throw std::invalid_argument("Emailul instructorului nu poate fi gol.");
    }
    email_ = std::move(email);
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
    out << ", Email=" << email_
        << ", Specializare=" << specializare_
        << ", TarifOra=" << tarifOra_;
}

void Instructor::citeste(std::istream& in) {
    // citesc partea comuna (nume + prenume)
    Persoana::citeste(in);

    // apoi partea specifica
    in >> email_ >> specializare_ >> tarifOra_;

    if (email_.empty() || specializare_.empty() || tarifOra_ <= 0) {
        throw std::invalid_argument("Citire Instructor invalida.");
    }
}
