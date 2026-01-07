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
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input invalid. Mai incearca: ";
    }
    return x;
}

const Persoana* gasesteConst(const std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
    for (const auto& p : persoane) {
        if (p->id() == id) return p.get();
    }
    return nullptr;
}

Persoana* gasesteMut(std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
    for (auto& p : persoane) {
        if (p->id() == id) return p.get();
    }
    return nullptr;
}

void afiseazaMeniu() {
    std::cout << "\n===== MENIU =====\n";
    std::cout << "1) Adauga copil\n";
    std::cout << "2) Adauga parinte\n";
    std::cout << "3) Adauga instructor\n";
    std::cout << "4) Adauga profesor\n";
    std::cout << "5) Afiseaza toate persoanele\n";
    std::cout << "6) Modifica nume/email persoana\n";
    std::cout << "7) Asociaza copil la parinte\n";
    std::cout << "8) Afiseaza parinte (si copiii lui)\n";
    std::cout << "9) Copii sortati dupa varsta\n";
    std::cout << "10) Instructori sortati dupa tarif\n";
    std::cout << "11) Profesori afisati\n";
    std::cout << "12) Sterge copii sub o varsta\n";
    std::cout << "13) Modifica telefon parinte\n";
    std::cout << "14) Modifica specializare/tarif instructor\n";
    std::cout << "15) Afiseaza primul copil din Administrare (primulDupa)\n";
    std::cout << "16) Afiseaza copii din Administrare folosind toate()\n";
    std::cout << "17) Verifica daca Administrare<Profesor> este goala\n";
    std::cout << "0) Iesire\n";
    std::cout << "Optiune: ";
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

        try {
            if (op == 0) {
                std::cout << "La revedere!\n";
                break;
            }

            if (op == 1) {
                std::string nume, email;
                int varsta;

                std::cin >> nume >> email >> varsta;
                auto c = std::make_unique<Copil>(nume, email, varsta);

                administrareCopii.adauga(*c);
                persoane.push_back(std::move(c));
            }
            else if (op == 2) {
                std::string nume, email, telefon;

                std::cin >> nume >> email >> telefon;
                auto p = std::make_unique<Parinte>(nume, email, telefon);

                administrareParinti.adauga(*p);
                persoane.push_back(std::move(p));
            }
            else if (op == 3) {
                std::string nume, email, spec;
                double tarif;

                std::cin >> nume >> email >> spec >> tarif;
                auto i = std::make_unique<Instructor>(nume, email, spec, tarif);

                std::cout << "Instructor specializare=" << i->specializare() << "\n";

                // folosim operator+= (membru)
                *i += 5.0;

                administrareInstructori.adauga(*i);
                persoane.push_back(std::move(i));
            }
            else if (op == 4) {
                std::string nume, email, materie, nivel;
                double tarif;

                std::cin >> nume >> email >> materie >> nivel >> tarif;
                auto pr = std::make_unique<Profesor>(nume, email, materie, nivel, tarif);

                administrareProfesori.adauga(*pr);
                persoane.push_back(std::move(pr));
            }
            else if (op == 5) {
                for (const auto& p : persoane) {
                    std::cout << *p << "\n";
                }
            }
            else if (op == 6) {
                int id;
                std::string n, e;

                std::cin >> id >> n >> e;
                auto* pers = gasesteMut(persoane, id);
                if (pers) {
                    pers->setNume(n);
                    pers->setEmail(e);
                }
            }
            else if (op == 7) {
                int idParinte, idCopil;
                std::cin >> idParinte >> idCopil;

                auto* parinte = dynamic_cast<Parinte*>(gasesteMut(persoane, idParinte));
                const auto* copil = dynamic_cast<const Copil*>(gasesteConst(persoane, idCopil));

                if (parinte && copil) {
                    parinte->adaugaCopil(idCopil);
                }
            }
            else if (op == 8) {
                int id;
                std::cin >> id;

                const auto* parinte = dynamic_cast<const Parinte*>(gasesteConst(persoane, id));
                if (parinte) {
                    std::cout << "Parinte: " << parinte->nume()
                              << ", telefon=" << parinte->telefon() << "\n";
                    for (int copilId : parinte->copiiIds()) {
                        const auto* copil = dynamic_cast<const Copil*>(gasesteConst(persoane, copilId));
                        if (copil) {
                            std::cout << " - " << copil->nume()
                                      << ", varsta=" << copil->varsta() << "\n";
                        }
                    }
                }
            }
            else if (op == 9) {
                administrareCopii.sorteazaDupa([](const Copil& a, const Copil& b) {
                    return a.varsta() < b.varsta();
                });
                administrareCopii.afiseaza(std::cout);
            }
            else if (op == 10) {
                administrareInstructori.sorteazaDupa([](const Instructor& a, const Instructor& b) {
                    return a < b;
                });
                administrareInstructori.afiseaza(std::cout);
            }
            else if (op == 11) {
                // afisare profesori (si folosim marime/esteGoala indirect mai jos)
                administrareProfesori.afiseaza(std::cout);
            }
            else if (op == 12) {
                int v;
                std::cin >> v;
                administrareCopii.stergeDaca([v](const Copil& c) {
                    return c.varsta() < v;
                });
            }
            else if (op == 13) {
                // folosim Parinte::setTelefon (cppcheck)
                int id;
                std::string tel;
                std::cin >> id >> tel;

                auto* parinte = dynamic_cast<Parinte*>(gasesteMut(persoane, id));
                if (parinte) {
                    parinte->setTelefon(tel);
                    std::cout << "Telefon actualizat: " << parinte->telefon() << "\n";
                }
            }
            else if (op == 14) {
                // folosim Instructor::setSpecializare si setTarifOra (cppcheck)
                int id;
                std::string specNou;
                double tarifNou;

                std::cin >> id >> specNou >> tarifNou;

                auto* instr = dynamic_cast<Instructor*>(gasesteMut(persoane, id));
                if (instr) {
                    instr->setSpecializare(specNou);
                    instr->setTarifOra(tarifNou);
                    std::cout << "Instructor actualizat: " << instr->specializare()
                              << ", tarif=" << instr->tarifOra() << "\n";
                }
            }
            else if (op == 15) {
                // folosim Administrare::primulDupa (cppcheck)
                if (administrareCopii.marime() == 0) {
                    std::cout << "Nu exista copii.\n";
                    continue;
                }

                const Copil& c = administrareCopii.primulDupa([](const Copil& x) {
                    return x.varsta() >= 3; // practic primul valid
                });

                std::cout << "Primul copil gasit: " << c << "\n";
            }
            else if (op == 16) {
                const auto& toti = administrareCopii.toate();
                std::cout << "Copii in administrare (toate) = " << toti.size() << "\n";
                for (const auto& c : toti) {
                    std::cout << c << "\n";
                }
            }
            else if (op == 17) {
                if (administrareProfesori.esteGoala()) {
                    std::cout << "Nu exista profesori.\n";
                } else {
                    std::cout << "Exista profesori: " << administrareProfesori.marime() << "\n";
                }
            }
            else {
                std::cout << "Optiune invalida.\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Eroare: " << ex.what() << "\n";
        }
    }

    return 0;
}
