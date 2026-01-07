//
// Created by Alina on 02/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_INSTRUCTOR_H
#define CLUBUL_COPIILOR_FERICITI_INSTRUCTOR_H

#include "Persoana.h"

#include <string>

// Instructor = persoana care tine activitati (dans, pictura, programare, etc.).
class Instructor : public Persoana {
private:
    std::string email_;
    std::string specializare_; // ex: "dans", "pictura", "robotica"
    double tarifOra_;          // cat cere pe ora

public:
    Instructor(std::string nume, std::string prenume, std::string email,
               std::string specializare, double tarifOra);

    Instructor(const Instructor&) = default;
    Instructor& operator=(const Instructor&) = default;

    ~Instructor() override = default;

    std::string tip() const override { return "Instructor"; }

    void afiseaza(std::ostream& out) const override;
    void citeste(std::istream& in) override;

    const std::string& email() const noexcept { return email_; }
    void setEmail(std::string email);

    const std::string& specializare() const noexcept { return specializare_; }
    double tarifOra() const noexcept { return tarifOra_; }

    void setSpecializare(std::string specializare);
    void setTarifOra(double tarifOra);

    // Operator membru (alt operator supraincarcat ca functie membra)
    // Exemplu: marim tariful cu o suma
    Instructor& operator+=(double suma);
};

// Operator non-membru (alt operator supraincarcat ca functie non-membra)
// Exemplu: comparam instructorii dupa tarif
bool operator<(const Instructor& a, const Instructor& b);

#endif // CLUBUL_COPIILOR_FERICITI_INSTRUCTOR_H
