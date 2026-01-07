#include <iostream>
#include <vector>
#include <memory>
#include <limits>

#include "Persoana.h"
#include "Copil.h"
#include "Parinte.h"
#include "Instructor.h"
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

// cautare pentru citire
const Persoana* gasestePersoanaConst(
        const std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
    for (const auto& p : persoane) {
        if (p->id() == id) return p.get();
    }
    return nullptr;
}

// cautare pentru modificare
Persoana* gasestePersoanaMut(
        std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
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
    std::cout << "4) Afiseaza toate persoanele\n";
    std::cout << "5) Modifica date persoana\n";
    std::cout << "6) Asociaza copil la parinte\n";
    std::cout << "7) Afiseaza copiii unui parinte\n";
    std::cout << "8) Copii sortati dupa varsta\n";
    std::cout << "9) Instructori sortati dupa tarif\n";
    std::cout << "10) Sterge copii sub o anumita varsta (Administrare)\n";
    std::cout << "0) Iesire\n";
    std::cout << "Optiune: ";
}

int main() {
    std::vector<std::unique_ptr<Persoana>> persoane;

    // instante template
    Administrare<Copil> administrareCopii;
    Administrare<Parinte> administrareParinti;
    Administrare<Instructor> administrareInstructori;

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

                std::cout << "Nume copil: ";
                std::cin >> nume;
                std::cout << "Email copil: ";
                std::cin >> email;
                std::cout << "Varsta copil: ";
                varsta = citesteInt();

                auto c = std::make_unique<Copil>(nume, email, varsta);
                administrareCopii.adauga(*c);

                std::cout << "Copil adaugat: " << c->nume()
                          << " (id=" << c->id() << ")\n";

                persoane.push_back(std::move(c));
            }
            else if (op == 2) {
                std::string nume, email, telefon;

                std::cout << "Nume parinte: ";
                std::cin >> nume;
                std::cout << "Email parinte: ";
                std::cin >> email;
                std::cout << "Telefon parinte: ";
                std::cin >> telefon;

                auto p = std::make_unique<Parinte>(nume, email, telefon);
                administrareParinti.adauga(*p);

                std::cout << "Parinte adaugat: " << p->nume()
                          << " (telefon=" << p->telefon() << ")\n";

                persoane.push_back(std::move(p));
            }
            else if (op == 3) {
                std::string nume, email, specializare;
                double tarif;

                std::cout << "Nume instructor: ";
                std::cin >> nume;
                std::cout << "Email instructor: ";
                std::cin >> email;
                std::cout << "Specializare: ";
                std::cin >> specializare;
                std::cout << "Tarif ora: ";
                std::cin >> tarif;

                auto i = std::make_unique<Instructor>(nume, email, specializare, tarif);
                *i += 5.0; // folossesc operator+=

                administrareInstructori.adauga(*i);

                std::cout << "Instructor adaugat: " << *i << "\n";
                persoane.push_back(std::move(i));
            }
            else if (op == 4) {
                for (const auto& p : persoane) {
                    std::cout << *p << "\n";
                    // folossesc getterii Persoana
                    std::cout << "  -> nume=" << p->nume()
                              << ", email=" << p->email() << "\n";
                }
            }
            else if (op == 5) {
                std::cout << "ID persoana: ";
                int id = citesteInt();

                Persoana* gasita = gasestePersoanaMut(persoane, id);
                if (!gasita) {
                    std::cout << "Persoana inexistenta.\n";
                    continue;
                }

                std::string numeNou, emailNou;
                std::cout << "Nume nou: ";
                std::cin >> numeNou;
                std::cout << "Email nou: ";
                std::cin >> emailNou;

                gasita->setNume(numeNou);
                gasita->setEmail(emailNou);

                std::cout << "Actualizat: " << *gasita << "\n";
            }
            else if (op == 6) {
                int idParinte, idCopil;
                std::cout << "ID parinte: ";
                idParinte = citesteInt();
                std::cout << "ID copil: ";
                idCopil = citesteInt();

                auto* parinte = dynamic_cast<Parinte*>(
                        gasestePersoanaMut(persoane, idParinte));
                const auto* copil = dynamic_cast<const Copil*>(
                        gasestePersoanaConst(persoane, idCopil));

                if (!parinte || !copil) {
                    std::cout << "Asociere invalida.\n";
                    continue;
                }

                parinte->adaugaCopil(idCopil);
                std::cout << "Copilul " << copil->nume()
                          << " a fost asociat parintelui "
                          << parinte->nume() << "\n";
            }
            else if (op == 7) {
                std::cout << "ID parinte: ";
                int id = citesteInt();

                const auto* parinte = dynamic_cast<const Parinte*>(
                        gasestePersoanaConst(persoane, id));
                if (!parinte) {
                    std::cout << "Nu este parinte.\n";
                    continue;
                }

                std::cout << "Parinte: " << parinte->nume()
                          << ", telefon=" << parinte->telefon() << "\n";

                for (int copilId : parinte->copiiIds()) {
                    const auto* copil = dynamic_cast<const Copil*>(
                            gasestePersoanaConst(persoane, copilId));
                    if (copil) {
                        std::cout << " - " << copil->nume()
                                  << ", varsta=" << copil->varsta() << "\n";
                    }
                }
            }
            else if (op == 8) {
                administrareCopii.sorteazaDupa(
                        [](const Copil& a, const Copil& b) {
                            return a.varsta() < b.varsta();
                        });

                std::cout << "Copii sortati dupa varsta ("
                          << administrareCopii.marime() << "):\n";
                administrareCopii.afiseaza(std::cout);
            }
            else if (op == 9) {
                administrareInstructori.sorteazaDupa(
                        [](const Instructor& a, const Instructor& b) {
                            return a < b;
                        });

                std::cout << "Instructori sortati dupa tarif:\n";
                administrareInstructori.afiseaza(std::cout);
            }
            else if (op == 10) {
                std::cout << "Stergere copii sub varsta: ";
                int v = citesteInt();

                std::size_t sterse = administrareCopii.stergeDaca(
                        [v](const Copil& c) {
                            return c.varsta() < v;
                        });

                std::cout << "Copii stersi: " << sterse << "\n";
                std::cout << "Copii ramasi: "
                          << administrareCopii.marime() << "\n";
            }
            else {
                std::cout << "Optiune invalida.\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Eroare: " << e.what() << "\n";
        }
    }

    return 0;
}
