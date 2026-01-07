//
// Created by Alina on 02/01/2026.
//
#include "Persoana.h"

#include <stdexcept>   // pentru std::invalid_argument
#include <utility>     // pentru std::move
#include <ostream>     // pentru std::ostream
#include <istream>     // pentru std::istream

// Variabila statica
int Persoana::urmatorId_ = 1;

int Persoana::genereazaIdNou() {
    // returnez id-ul curent si apoi il incrementez pentru urmatoarea persoana
    return urmatorId_++;
}

Persoana::Persoana(std::string nume, std::string email)
    : id_(genereazaIdNou()), nume_(std::move(nume)), email_(std::move(email)) {
    // validari
    if (nume_.empty()) {
        throw std::invalid_argument("Numele nu poate fi gol.");
    }
    if (email_.empty()) {
        throw std::invalid_argument("Emailul nu poate fi gol.");
    }
}

Persoana::Persoana(int id, std::string nume, std::string email)
    : id_(id), nume_(std::move(nume)), email_(std::move(email)) {
    if (id_ <= 0) {
        throw std::invalid_argument("ID invalid (trebuie > 0).");
    }
    if (nume_.empty()) {
        throw std::invalid_argument("Numele nu poate fi gol.");
    }
    if (email_.empty()) {
        throw std::invalid_argument("Emailul nu poate fi gol.");
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

void Persoana::setEmail(std::string email) {
    if (email.empty()) {
        throw std::invalid_argument("Emailul nu poate fi gol.");
    }
    email_ = std::move(email);
}

void Persoana::afiseaza(std::ostream& out) const {
    // atribute comune
    out << "ID=" << id_
        << ", Nume=" << nume_
        << ", Email=" << email_;
}

void Persoana::citeste(std::istream& in) {
    // citire: nume si email fara spatii
    in >> nume_ >> email_;

    if (nume_.empty() || email_.empty()) {
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
