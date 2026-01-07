//
// Created by Alina on 07/01/2026.
//
#include "PersoanaFactory.h"
#include "Copil.h"
#include "Parinte.h"
#include "Instructor.h"
#include "Profesor.h"

std::unique_ptr<Persoana> PersoanaFactory::creeazaCopil(
    const std::string& nume,
    const std::string& email,
    int varsta
) {
    return std::make_unique<Copil>(nume, email, varsta);
}

std::unique_ptr<Persoana> PersoanaFactory::creeazaParinte(
    const std::string& nume,
    const std::string& email,
    const std::string& telefon
) {
    return std::make_unique<Parinte>(nume, email, telefon);
}

std::unique_ptr<Persoana> PersoanaFactory::creeazaInstructor(
    const std::string& nume,
    const std::string& email,
    const std::string& specializare,
    double tarif
) {
    return std::make_unique<Instructor>(nume, email, specializare, tarif);
}

std::unique_ptr<Persoana> PersoanaFactory::creeazaProfesor(
    const std::string& nume,
    const std::string& email,
    const std::string& materie,
    const std::string& nivel,
    double tarif
) {
    return std::make_unique<Profesor>(nume, email, materie, nivel, tarif);
}
