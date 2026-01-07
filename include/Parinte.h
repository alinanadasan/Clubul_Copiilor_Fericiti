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
    std::string telefon_;
    std::vector<int> copiiIds_; // id-urile copiilor asociati parintelui

public:
    // Constructor: apelam constructorul din Persoana
    Parinte(std::string nume, std::string email, std::string telefon);

    // Copiere
    Parinte(const Parinte&) = default;
    Parinte& operator=(const Parinte&) = default;

    // Destructor
    ~Parinte() override = default;

    // Tipul persoanei
    std::string tip() const override { return "Parinte"; }

    // Afisare / citire extinse fata de Persoana
    void afiseaza(std::ostream& out) const override;
    void citeste(std::istream& in) override;

    // Getter / setter pentru telefon
    const std::string& telefon() const noexcept { return telefon_; }
    void setTelefon(std::string telefon);

    // Asociere copil-parinte
    void adaugaCopil(int copilId);

    // Acces la lista de copii pt citire
    const std::vector<int>& copiiIds() const noexcept { return copiiIds_; }
};

#endif //CLUBUL_COPIILOR_FERICITI_PARINTE_H