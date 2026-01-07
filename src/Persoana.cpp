//
// Created by Alina on 02/01/2026.
//
#include "Persoana.h"

#include <stdexcept>
#include <utility>
#include <istream>
#include <ostream>

// Variabila statica
int Persoana::urmatorId_ = 1;

int Persoana::genereazaIdNou() {
    // returnez id-ul curent si apoi il incrementez pentru urmatoarea persoana
    return urmatorId_++;
}

Persoana::Persoana(std::string nume, std::string prenume)
    : id_(genereazaIdNou()), nume_(std::move(nume)), prenume_(std::move(prenume)) {
    if (nume_.empty()) {
        throw std::invalid_argument("Numele nu poate fi gol.");
    }
    if (prenume_.empty()) {
        throw std::invalid_argument("Prenumele nu poate fi gol.");
    }
}

Persoana::Persoana(int id, std::string nume, std::string prenume)
    : id_(id), nume_(std::move(nume)), prenume_(std::move(prenume)) {
    if (id_ <= 0) {
        throw std::invalid_argument("ID invalid (trebuie > 0).");
    }
    if (nume_.empty()) {
        throw std::invalid_argument("Numele nu poate fi gol.");
    }
    if (prenume_.empty()) {
        throw std::invalid_argument("Prenumele nu poate fi gol.");
    }

    // daca citim persoane cu id mare, nu vrem ca urmatorId_ sa genereze duplicate
    if (id_ >= urmatorId_) {
        urmatorId_ = id_ + 1;
    }
}

void Persoana::setNume(std::string nume) {
    if (nume.empty()) {
        throw std::invalid_argument("Numele nu poate fi gol.");
    }
    nume_ = std::move(nume);
}

void Persoana::setPrenume(std::string prenume) {
    if (prenume.empty()) {
        throw std::invalid_argument("Prenumele nu poate fi gol.");
    }
    prenume_ = std::move(prenume);
}

void Persoana::afiseaza(std::ostream& out) const {
    out << "ID=" << id_
        << ", Nume=" << nume_
        << ", Prenume=" << prenume_;
}

void Persoana::citeste(std::istream& in) {
    // citire: nume si prenume fara spatii
    in >> nume_ >> prenume_;

    if (nume_.empty() || prenume_.empty()) {
        throw std::invalid_argument("Citire Persoana invalida.");
    }
}

std::ostream& operator<<(std::ostream& out, const Persoana& p) {
    out << "[" << p.tip() << "] ";
    p.afiseaza(out);
    return out;
}

std::istream& operator>>(std::istream& in, Persoana& p) {
    p.citeste(in);
    return in;
}
