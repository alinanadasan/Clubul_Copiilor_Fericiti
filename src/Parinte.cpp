//
// Created by Alina on 02/01/2026.
//
#include "Parinte.h"

#include <stdexcept>
#include <utility>
#include <istream>
#include <ostream>

Parinte::Parinte(std::string nume, std::string prenume, std::string email, std::string telefon)
    : Persoana(std::move(nume), std::move(prenume)),
      email_(std::move(email)),
      telefon_(std::move(telefon)) {
    if (email_.empty()) {
        throw std::invalid_argument("Emailul parintelui nu poate fi gol.");
    }
    if (telefon_.empty()) {
        throw std::invalid_argument("Telefonul parintelui nu poate fi gol.");
    }
}

void Parinte::setEmail(std::string email) {
    if (email.empty()) {
        throw std::invalid_argument("Emailul parintelui nu poate fi gol.");
    }
    email_ = std::move(email);
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
    // partea comuna (id, nume, prenume)
    Persoana::afiseaza(out);

    // specific parintelui
    out << ", Email=" << email_
        << ", Telefon=" << telefon_;

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
    // partea comuna (nume + prenume)
    Persoana::citeste(in);

    // email + telefon
    in >> email_ >> telefon_;

    if (email_.empty() || telefon_.empty()) {
        throw std::invalid_argument("Citire Parinte invalida.");
    }
}
