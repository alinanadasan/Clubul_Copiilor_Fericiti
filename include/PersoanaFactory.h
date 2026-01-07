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
    static std::unique_ptr<Persoana> creeazaCopil(
        const std::string& nume,
        const std::string& email,
        int varsta
    );

    static std::unique_ptr<Persoana> creeazaParinte(
        const std::string& nume,
        const std::string& email,
        const std::string& telefon
    );

    static std::unique_ptr<Persoana> creeazaInstructor(
        const std::string& nume,
        const std::string& email,
        const std::string& specializare,
        double tarif
    );

    static std::unique_ptr<Persoana> creeazaProfesor(
        const std::string& nume,
        const std::string& email,
        const std::string& materie,
        const std::string& nivel,
        double tarif
    );
};

#endif //CLUBUL_COPIILOR_FERICITI_PERSOANAFACTORY_H