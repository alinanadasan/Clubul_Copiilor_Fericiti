//
// Created by Alina on 02/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_PERSOANA_H
#define CLUBUL_COPIILOR_FERICITI__PERSOANA_H

#include <string>
#include <iosfwd>

// Clasa de baza pentru toate tipurile de persoane din aplicatie.
class Persoana {
private:
    int id_;                 // id unic pentru fiecare persoana
    std::string nume_;       // numele persoanei
    std::string email_;      // email de contact

    static int urmatorId_;   // contor static pentru generarea id-urilor

protected:
    // Constructor apelat doar din clasele derivate
    Persoana(std::string nume, std::string email);

    // Constructor cu id explicit (pentru citire din fisier)
    Persoana(int id, std::string nume, std::string email);

public:
    // Constructor de copiere si operator=
    Persoana(const Persoana&) = default;
    Persoana& operator=(const Persoana&) = default;

    // Destructor virtual
    virtual ~Persoana() = default;

    // Functie statica pentru generarea unui id nou
    static int genereazaIdNou();

    // Getters
    int id() const noexcept { return id_; }
    const std::string& nume() const noexcept { return nume_; }
    const std::string& email() const noexcept { return email_; }

    // Setters
    void setNume(std::string nume);
    void setEmail(std::string email);

    // Metoda virtuala -> clasa abstracta
    virtual std::string tip() const = 0;

    // Functii virtuale pentru afisare si citire
    virtual void afiseaza(std::ostream& out) const;
    virtual void citeste(std::istream& in);
};

// Operatori non-membru
std::ostream& operator<<(std::ostream& out, const Persoana& p);
std::istream& operator>>(std::istream& in, Persoana& p);

#endif // OOP_PERSOANA_H

