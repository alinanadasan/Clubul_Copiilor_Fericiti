//
// Created by Alina on 07/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_PERSOANAFACTORY_H
#define CLUBUL_COPIILOR_FERICITI_PERSOANAFACTORY_H

#include <memory>
#include <string>

#include "Persoana.h"

class PersoanaFactory {
public:
    // Copil: fara email
    static std::unique_ptr<Persoana> creeazaCopil(
        const std::string& nume,
        const std::string& prenume,
        int varsta
    );

    // Parinte: are email + telefon
    static std::unique_ptr<Persoana> creeazaParinte(
        const std::string& nume,
        const std::string& prenume,
        const std::string& email,
        const std::string& telefon
    );

    // Instructor: are email + specializare + tarif
    static std::unique_ptr<Persoana> creeazaInstructor(
        const std::string& nume,
        const std::string& prenume,
        const std::string& email,
        const std::string& specializare,
        double tarif
    );

    // Profesor: are email + materie + nivel + tarif
    static std::unique_ptr<Persoana> creeazaProfesor(
        const std::string& nume,
        const std::string& prenume,
        const std::string& email,
        const std::string& materie,
        const std::string& nivel,
        double tarif
    );
};

#endif // CLUBUL_COPIILOR_FERICITI_PERSOANAFACTORY_H
