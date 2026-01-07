//
// Created by Alina on 02/01/2026.
//
#include "Parinte.h"

#include <stdexcept>   // std::invalid_argument
#include <ostream>
#include <istream>
#include <utility>     // std::move

Parinte::Parinte(std::string nume, std::string email, std::string telefon)
    : Persoana(std::move(nume), std::move(email)), telefon_(std::move(telefon)) {
    if (telefon_.empty()) {
        throw std::invalid_argument("Telefonul parintelui nu poate fi gol.");
    }
}

void Parinte::setTelefon(std::string telefon) {
    if (telefon.empty()) {
        throw std::invalid_argument("Telefonul parintelui nu poate fi gol.");
    }
    telefon_ = std::move(telefon);
}

void Parinte::adaugaCopil(int copilId) {
    if (copilId <= 0) {
        throw std::invalid_argument("ID copil invalid.");
    }

    // nu permitem acelasi copil de doua ori
    for (int id : copiiIds_) {
        if (id == copilId) {
            throw std::invalid_argument("Copilul este deja asociat acestui parinte.");
        }
    }

    copiiIds_.push_back(copilId);
}

void Parinte::afiseaza(std::ostream& out) const {
    // partea comuna (id, nume, email)
    Persoana::afiseaza(out);

    // specific parintelui
    out << ", Telefon=" << telefon_;

    // afisam si copiii asociati
    out << ", CopiiIDs=[";
    for (size_t i = 0; i < copiiIds_.size(); ++i) {
        out << copiiIds_[i];
        if (i + 1 < copiiIds_.size()) {
            out << ", ";
        }
    }
    out << "]";
}

void Parinte::citeste(std::istream& in) {
    // partea comuna
    Persoana::citeste(in);

    // telefonul
    in >> telefon_;

    if (telefon_.empty()) {
        throw std::invalid_argument("Citire Parinte invalida.");
    }
}
