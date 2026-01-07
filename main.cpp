#include <iostream>
#include <vector>
#include <memory>
#include <limits>

#include "Persoana.h"
#include "Copil.h"
#include "Parinte.h"
#include "Instructor.h"
#include "Profesor.h"
#include "Administrare.h"

int citesteInt() {
    int x;
    std::cin >> x;
    return x;
}

void afiseazaMeniu() {
    std::cout <<
    "\n================= MENIU PRINCIPAL =================\n"
    "1.  Adauga copil\n"
    "2.  Adauga parinte\n"
    "3.  Adauga instructor\n"
    "4.  Adauga profesor\n"
    "5.  Afiseaza toate persoanele\n"
    "6.  Modifica nume si email pentru o persoana\n"
    "7.  Asociaza copil unui parinte\n"
    "8.  Afiseaza un parinte si copiii sai\n"
    "9.  Sorteaza copiii dupa varsta\n"
    "10. Sorteaza instructorii dupa tarif\n"
    "11. Afiseaza toti profesorii\n"
    "12. Sterge copiii sub o anumita varsta\n"
    "13. Modifica telefonul unui parinte\n"
    "14. Modifica specializarea si tariful unui instructor\n"
    "15. Afiseaza primul copil\n"
    "16. Afiseaza toti copiii\n"
    "17. Verifica lista profesori (goala + marime)\n"
    "18. Afiseaza materia si nivelul unui profesor\n"
    "19. Modifica materia si nivelul unui profesor\n"
    "0.  Iesire\n"
    "===================================================\n"
    "Optiune: ";
}

int main() {
    std::vector<std::unique_ptr<Persoana>> persoane;

    Administrare<Copil> administrareCopii;
    Administrare<Parinte> administrareParinti;
    Administrare<Instructor> administrareInstructori;
    Administrare<Profesor> administrareProfesori;

    while (true) {
        afiseazaMeniu();
        int op = citesteInt();

        if (op == 0) {
            std::cout << "Iesire din aplicatie.\n";
            break;
        }

        if (op == 1) {
            std::string n, e;
            int v;
            std::cin >> n >> e >> v;
            auto c = std::make_unique<Copil>(n, e, v);
            administrareCopii.adauga(*c);
            persoane.push_back(std::move(c));
        }
        else if (op == 2) {
            std::string n, e, t;
            std::cin >> n >> e >> t;
            auto p = std::make_unique<Parinte>(n, e, t);
            administrareParinti.adauga(*p);
            persoane.push_back(std::move(p));
        }
        else if (op == 3) {
            std::string n, e, s;
            double tarif;
            std::cin >> n >> e >> s >> tarif;
            auto i = std::make_unique<Instructor>(n, e, s, tarif);
            administrareInstructori.adauga(*i);
            persoane.push_back(std::move(i));
        }
        else if (op == 4) {
            std::string n, e, m, niv;
            double tarif;
            std::cin >> n >> e >> m >> niv >> tarif;
            auto pr = std::make_unique<Profesor>(n, e, m, niv, tarif);
            administrareProfesori.adauga(*pr);
            persoane.push_back(std::move(pr));
        }
        else if (op == 5) {
            for (const auto& p : persoane)
                std::cout << *p << "\n";
        }
        else if (op == 6) {
            int id;
            std::string n, e;
            std::cin >> id >> n >> e;
            for (auto& p : persoane)
                if (p->id() == id) {
                    p->setNume(n);
                    p->setEmail(e);
                }
        }
        else if (op == 7) {
            int pid, cid;
            std::cin >> pid >> cid;
            for (auto& p : persoane) {
                auto* parinte = dynamic_cast<Parinte*>(p.get());
                if (parinte && parinte->id() == pid)
                    parinte->adaugaCopil(cid);
            }
        }
        else if (op == 8) {
            int id;
            std::cin >> id;
            for (const auto& p : persoane) {
                auto* parinte = dynamic_cast<Parinte*>(p.get());
                if (parinte && parinte->id() == id) {
                    std::cout << *parinte << "\n";
                    for (int cid : parinte->copiiIds()) {
                        for (const auto& x : persoane)
                            if (x->id() == cid)
                                std::cout << "  " << *x << "\n";
                    }
                }
            }
        }
        else if (op == 9) {
            administrareCopii.sorteazaDupa(
                [](const Copil& a, const Copil& b) {
                    return a.varsta() < b.varsta();
                }
            );
        }
        else if (op == 10) {
            administrareInstructori.sorteazaDupa(
                [](const Instructor& a, const Instructor& b) {
                    return a < b;
                }
            );
        }
        else if (op == 11) {
            administrareProfesori.afiseaza(std::cout);
        }
        else if (op == 12) {
            int v;
            std::cin >> v;
            administrareCopii.stergeDaca(
                [v](const Copil& c) { return c.varsta() < v; }
            );
        }
        else if (op == 13) {
            int id;
            std::string tel;
            std::cin >> id >> tel;
            for (auto& p : persoane) {
                auto* parinte = dynamic_cast<Parinte*>(p.get());
                if (parinte && parinte->id() == id)
                    parinte->setTelefon(tel);
            }
        }
        else if (op == 14) {
            int id;
            std::string s;
            double t;
            std::cin >> id >> s >> t;
            for (auto& p : persoane) {
                auto* i = dynamic_cast<Instructor*>(p.get());
                if (i && i->id() == id) {
                    i->setSpecializare(s);
                    i->setTarifOra(t);
                }
            }
        }
        else if (op == 15) {
            std::cout << administrareCopii.primulDupa(
                [](const Copil&) { return true; }
            ) << "\n";
        }
        else if (op == 16) {
            for (const auto& c : administrareCopii.toate())
                std::cout << c << "\n";
        }
        else if (op == 17) {
            std::cout << administrareProfesori.esteGoala()
                      << " " << administrareProfesori.marime() << "\n";
        }
        else if (op == 18) {
            int id;
            std::cin >> id;
            for (const auto& p : persoane) {
                auto* pr = dynamic_cast<Profesor*>(p.get());
                if (pr && pr->id() == id)
                    std::cout << pr->materie() << " " << pr->nivel() << "\n";
            }
        }
        else if (op == 19) {
            int id;
            std::string m, n;
            std::cin >> id >> m >> n;
            for (auto& p : persoane) {
                auto* pr = dynamic_cast<Profesor*>(p.get());
                if (pr && pr->id() == id) {
                    pr->setMaterie(m);
                    pr->setNivel(n);
                }
            }
        }
    }

    return 0;
}
