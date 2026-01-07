//
// Created by Alina on 02/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_PARINTE_H
#define CLUBUL_COPIILOR_FERICITI_PARINTE_H

#include "Persoana.h"

#include <string>
#include <vector>

// Parinte = persoana care plateste cursurile copiilor.
// Un parinte poate avea unul sau mai multi copii inscrisi.
class Parinte final : public Persoana {
private:
    std::string email_;
    std::string telefon_;
    std::vector<int> copiiIds_; // id-urile copiilor asociati parintelui

public:
    // Constructor: apelam constructorul din Persoana
    Parinte(std::string nume, std::string prenume, std::string email, std::string telefon);

    Parinte(const Parinte&) = default;
    Parinte& operator=(const Parinte&) = default;

    ~Parinte() override = default;

    std::string tip() const override { return "Parinte"; }

    void afiseaza(std::ostream& out) const override;
    void citeste(std::istream& in) override;

    // Getter / setter pentru email
    const std::string& email() const noexcept { return email_; }
    void setEmail(std::string email);

    // Getter / setter pentru telefon
    const std::string& telefon() const noexcept { return telefon_; }
    void setTelefon(std::string telefon);

    // Asociere copil-parinte
    void adaugaCopil(int copilId);

    const std::vector<int>& copiiIds() const noexcept { return copiiIds_; }
};

#endif // CLUBUL_COPIILOR_FERICITI_PARINTE_H
