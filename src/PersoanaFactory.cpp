//
// Created by Alina on 07/01/2026.
//

#include "PersoanaFactory.h"

#include "Copil.h"
#include "Parinte.h"
#include "Instructor.h"
#include "Profesor.h"

// Copil: fara email
std::unique_ptr<Persoana> PersoanaFactory::creeazaCopil(
    const std::string& nume,
    const std::string& prenume,
    int varsta
) {
    return std::make_unique<Copil>(nume, prenume, varsta);
}

// Parinte: are email + telefon
std::unique_ptr<Persoana> PersoanaFactory::creeazaParinte(
    const std::string& nume,
    const std::string& prenume,
    const std::string& email,
    const std::string& telefon
) {
    return std::make_unique<Parinte>(nume, prenume, email, telefon);
}

// Instructor: are email + specializare + tarif
std::unique_ptr<Persoana> PersoanaFactory::creeazaInstructor(
    const std::string& nume,
    const std::string& prenume,
    const std::string& email,
    const std::string& specializare,
    double tarif
) {
    return std::make_unique<Instructor>(nume, prenume, email, specializare, tarif);
}

// Profesor: are email + materie + nivel + tarif
std::unique_ptr<Persoana> PersoanaFactory::creeazaProfesor(
    const std::string& nume,
    const std::string& prenume,
    const std::string& email,
    const std::string& materie,
    const std::string& nivel,
    double tarif
) {
    return std::make_unique<Profesor>(nume, prenume, email, materie, nivel, tarif);
}
