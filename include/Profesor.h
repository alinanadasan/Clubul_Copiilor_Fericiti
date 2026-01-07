//
// Created by Alina on 02/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_PROFESOR_H
#define CLUBUL_COPIILOR_FERICITI_PROFESOR_H

#include "Instructor.h"

#include <string>

// Profesor = Instructor pentru materii scolare (mate, romana, engleza etc.).
class Profesor final : public Instructor {
private:
    std::string materie_; // ex: "matematica"
    std::string nivel_;   // ex: "primar", "gimnaziu"

public:
    Profesor(std::string nume, std::string email,
             std::string materie, std::string nivel,
             double tarifOra);

    Profesor(const Profesor&) = default;
    Profesor& operator=(const Profesor&) = default;

    ~Profesor() override = default;

    std::string tip() const override { return "Profesor"; }

    void afiseaza(std::ostream& out) const override;
    void citeste(std::istream& in) override;

    const std::string& materie() const noexcept { return materie_; }
    const std::string& nivel() const noexcept { return nivel_; }

    void setMaterie(std::string materie);
    void setNivel(std::string nivel);
};

#endif //CLUBUL_COPIILOR_FERICITI_PROFESOR_H