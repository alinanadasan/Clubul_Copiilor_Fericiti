#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>

#include "Persoana.h"
#include "Copil.h"
#include "Parinte.h"
#include "Instructor.h"
#include "Profesor.h"
#include "Administrare.h"
#include "PersoanaFactory.h"
#include "SortareCopiiDupaVarsta.h"

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
    "9.  Sorteaza copiii dupa varsta (Strategy Pattern)\n"
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
    "20. Demo: Factory Pattern pentru creare persoane\n"
    "21. Demo: Foloseste getter-e (nume, email, telefon, specializare)\n"
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
            // Foloseste Factory Pattern
            auto c = PersoanaFactory::creeazaCopil(n, e, v);
            administrareCopii.adauga(dynamic_cast<Copil&>(*c));
            persoane.push_back(std::move(c));
            std::cout << "Copil adaugat cu succes.\n";
        }
        else if (op == 2) {
            std::string n, e, t;
            std::cin >> n >> e >> t;
            auto p = PersoanaFactory::creeazaParinte(n, e, t);
            administrareParinti.adauga(dynamic_cast<Parinte&>(*p));
            persoane.push_back(std::move(p));
            std::cout << "Parinte adaugat cu succes.\n";
        }
        else if (op == 3) {
            std::string n, e, s;
            double tarif;
            std::cin >> n >> e >> s >> tarif;
            auto i = PersoanaFactory::creeazaInstructor(n, e, s, tarif);
            administrareInstructori.adauga(dynamic_cast<Instructor&>(*i));
            persoane.push_back(std::move(i));
            std::cout << "Instructor adaugat cu succes.\n";
        }
        else if (op == 4) {
            std::string n, e, m, niv;
            double tarif;
            std::cin >> n >> e >> m >> niv >> tarif;
            auto pr = PersoanaFactory::creeazaProfesor(n, e, m, niv, tarif);
            administrareProfesori.adauga(dynamic_cast<Profesor&>(*pr));
            persoane.push_back(std::move(pr));
            std::cout << "Profesor adaugat cu succes.\n";
        }
        else if (op == 5) {
            std::cout << "\n=== TOATE PERSOANELE ===\n";
            for (const auto& p : persoane) {
                std::cout << *p << "\n";
            }
        }
        else if (op == 6) {
            int id;
            std::string n, e;
            std::cout << "ID persoana: ";
            std::cin >> id;
            std::cout << "Nume nou: ";
            std::cin >> n;
            std::cout << "Email nou: ";
            std::cin >> e;

            bool gasit = false;
            for (auto& p : persoane) {
                if (p->id() == id) {
                    p->setNume(n);
                    p->setEmail(e);
                    std::cout << "Persoana modificata cu succes.\n";
                    gasit = true;
                    break;
                }
            }
            if (!gasit) {
                std::cout << "Persoana cu ID " << id << " nu a fost gasita.\n";
            }
        }
        else if (op == 7) {
            int pid, cid;
            std::cout << "ID parinte: ";
            std::cin >> pid;
            std::cout << "ID copil: ";
            std::cin >> cid;

            bool parinteGasit = false;
            bool copilGasit = false;

            // Verifica daca copilul exista
            for (const auto& p : persoane) {
                if (p->id() == cid) {
                    copilGasit = true;
                    break;
                }
            }

            if (!copilGasit) {
                std::cout << "Copilul cu ID " << cid << " nu exista.\n";
                continue;
            }

            for (auto& p : persoane) {
                auto* parinte = dynamic_cast<Parinte*>(p.get());
                if (parinte && parinte->id() == pid) {
                    try {
                        parinte->adaugaCopil(cid);
                        std::cout << "Copil asociat cu succes parintelui.\n";
                        parinteGasit = true;
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Eroare: " << e.what() << "\n";
                    }
                    break;
                }
            }
            if (!parinteGasit) {
                std::cout << "Parinte cu ID " << pid << " nu a fost gasit.\n";
            }
        }
        else if (op == 8) {
            int id;
            std::cout << "ID parinte: ";
            std::cin >> id;

            bool gasit = false;
            for (const auto& p : persoane) {
                auto* parinte = dynamic_cast<Parinte*>(p.get());
                if (parinte && parinte->id() == id) {
                    gasit = true;
                    std::cout << "\n=== PARINTE ===\n";
                    std::cout << *parinte << "\n";

                    std::cout << "\n=== COPIII ASOCIATI ===\n";
                    if (parinte->copiiIds().empty()) {
                        std::cout << "Nu are copii asociati.\n";
                    } else {
                        for (int cid : parinte->copiiIds()) {
                            bool copilGasit = false;
                            for (const auto& pers : persoane) {
                                if (pers->id() == cid) {
                                    std::cout << "  " << *pers << "\n";
                                    copilGasit = true;
                                    break;
                                }
                            }
                            if (!copilGasit) {
                                std::cout << "  Copil ID " << cid << " (sters sau inexistent)\n";
                            }
                        }
                    }
                    break;
                }
            }
            if (!gasit) {
                std::cout << "Parinte cu ID " << id << " nu a fost gasit.\n";
            }
        }
        else if (op == 9) {
            // Strategy Pattern pentru sortare
            SortareCopiiDupaVarsta strategie;
            administrareCopii.sorteazaCuStrategie(strategie);
            std::cout << "Copii sortati dupa varsta (Strategy Pattern).\n";
        }
        else if (op == 10) {
            administrareInstructori.sorteazaDupa(
                [](const Instructor& a, const Instructor& b) {
                    return a < b; // foloseste operatorul < supraincarcat
                }
            );
            std::cout << "Instructori sortati dupa tarif.\n";
        }
        else if (op == 11) {
            std::cout << "\n=== TOTI PROFESORII ===\n";
            if (administrareProfesori.esteGoala()) {
                std::cout << "Nu exista profesori.\n";
            } else {
                administrareProfesori.afiseaza(std::cout);
            }
        }
        else if (op == 12) {
            int v;
            std::cout << "Varsta limita: ";
            std::cin >> v;

            int nrStergeri = administrareCopii.stergeDaca(
                [v](const Copil& c) { return c.varsta() < v; }
            );
            std::cout << "Au fost stersi " << nrStergeri << " copii sub varsta " << v << ".\n";
        }
        else if (op == 13) {
            int id;
            std::string tel;
            std::cout << "ID parinte: ";
            std::cin >> id;
            std::cout << "Telefon nou: ";
            std::cin >> tel;

            bool gasit = false;
            for (auto& p : persoane) {
                auto* parinte = dynamic_cast<Parinte*>(p.get());
                if (parinte && parinte->id() == id) {
                    try {
                        parinte->setTelefon(tel);
                        std::cout << "Telefon modificat cu succes.\n";
                        gasit = true;
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Eroare: " << e.what() << "\n";
                    }
                    break;
                }
            }
            if (!gasit) {
                std::cout << "Parinte cu ID " << id << " nu a fost gasit.\n";
            }
        }
        else if (op == 14) {
            int id;
            std::string s;
            double t;
            std::cout << "ID instructor: ";
            std::cin >> id;
            std::cout << "Specializare noua: ";
            std::cin >> s;
            std::cout << "Tarif nou: ";
            std::cin >> t;

            bool gasit = false;
            for (auto& p : persoane) {
                auto* instr = dynamic_cast<Instructor*>(p.get());
                if (instr && instr->id() == id) {
                    try {
                        instr->setSpecializare(s);
                        instr->setTarifOra(t);
                        std::cout << "Instructor modificat cu succes.\n";
                        gasit = true;
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Eroare: " << e.what() << "\n";
                    }
                    break;
                }
            }
            if (!gasit) {
                std::cout << "Instructor cu ID " << id << " nu a fost gasit.\n";
            }
        }
        else if (op == 15) {
            try {
                std::cout << "\n=== PRIMUL COPIL ===\n";
                std::cout << administrareCopii.primulDupa(
                    [](const Copil&) { return true; }
                ) << "\n";
            } catch (const std::runtime_error& e) {
                std::cout << "Eroare: " << e.what() << "\n";
            }
        }
        else if (op == 16) {
            std::cout << "\n=== TOTI COPIII ===\n";
            if (administrareCopii.esteGoala()) {
                std::cout << "Nu exista copii.\n";
            } else {
                for (const auto& c : administrareCopii.toate()) {
                    std::cout << c << "\n";
                }
            }
        }
        else if (op == 17) {
            std::cout << "\n=== STATISTICI PROFESORI ===\n";
            std::cout << "Lista goala? " << (administrareProfesori.esteGoala() ? "DA" : "NU") << "\n";
            std::cout << "Numar profesori: " << administrareProfesori.marime() << "\n";
        }
        else if (op == 18) {
            int id;
            std::cout << "ID profesor: ";
            std::cin >> id;

            bool gasit = false;
            for (const auto& p : persoane) {
                auto* prof = dynamic_cast<Profesor*>(p.get());
                if (prof && prof->id() == id) {
                    gasit = true;
                    std::cout << "Materie: " << prof->materie() << "\n";
                    std::cout << "Nivel: " << prof->nivel() << "\n";
                    break;
                }
            }
            if (!gasit) {
                std::cout << "Profesor cu ID " << id << " nu a fost gasit.\n";
            }
        }
        else if (op == 19) {
            int id;
            std::string m, n;
            std::cout << "ID profesor: ";
            std::cin >> id;
            std::cout << "Materie noua: ";
            std::cin >> m;
            std::cout << "Nivel nou: ";
            std::cin >> n;

            bool gasit = false;
            for (auto& p : persoane) {
                auto* prof = dynamic_cast<Profesor*>(p.get());
                if (prof && prof->id() == id) {
                    try {
                        prof->setMaterie(m);
                        prof->setNivel(n);
                        std::cout << "Profesor modificat cu succes.\n";
                        gasit = true;
                    } catch (const std::invalid_argument& e) {
                        std::cout << "Eroare: " << e.what() << "\n";
                    }
                    break;
                }
            }
            if (!gasit) {
                std::cout << "Profesor cu ID " << id << " nu a fost gasit.\n";
            }
        }
        else if (op == 20) {
            // Demo Factory Pattern
            std::cout << "\n=== DEMO FACTORY PATTERN ===\n";

            // Creare cu factory
            auto copil = PersoanaFactory::creeazaCopil("Demo", "demo@mail.com", 10);
            auto parinte = PersoanaFactory::creeazaParinte("ParinteDemo", "parent@mail.com", "0722222222");
            auto instructor = PersoanaFactory::creeazaInstructor("InstructorDemo", "instr@mail.com", "sport", 50.0);
            auto profesor = PersoanaFactory::creeazaProfesor("ProfDemo", "prof@mail.com", "informatica", "liceu", 75.0);

            std::cout << "Creat cu Factory:\n";
            std::cout << *copil << "\n";
            std::cout << *parinte << "\n";
            std::cout << *instructor << "\n";
            std::cout << *profesor << "\n";

            // Adauga doar pentru demo
            administrareCopii.adauga(dynamic_cast<Copil&>(*copil));
            administrareParinti.adauga(dynamic_cast<Parinte&>(*parinte));
            administrareInstructori.adauga(dynamic_cast<Instructor&>(*instructor));
            administrareProfesori.adauga(dynamic_cast<Profesor&>(*profesor));

            persoane.push_back(std::move(copil));
            persoane.push_back(std::move(parinte));
            persoane.push_back(std::move(instructor));
            persoane.push_back(std::move(profesor));

            std::cout << "Demo completat. Persoanele au fost adaugate in sistem.\n";
        }
        else if (op == 21) {
            // Demo pentru getter-e nefolosite
            std::cout << "\n=== DEMO GETTER-E ===\n";

            if (!persoane.empty()) {
                // Foloseste getter-ele care erau marcate ca nefolosite
                std::cout << "Prima persoana din sistem:\n";
                std::cout << "ID: " << persoane[0]->id() << "\n";
                std::cout << "Nume: " << persoane[0]->nume() << "\n";
                std::cout << "Email: " << persoane[0]->email() << "\n";

                // Cauta un parinte pentru a folosi telefon()
                for (const auto& p : persoane) {
                    auto* parinte = dynamic_cast<Parinte*>(p.get());
                    if (parinte) {
                        std::cout << "\nParinte gasit:\n";
                        std::cout << "Telefon: " << parinte->telefon() << "\n";
                        break;
                    }
                }

                // Cauta un instructor pentru a folosi specializare()
                for (const auto& p : persoane) {
                    auto* instr = dynamic_cast<Instructor*>(p.get());
                    if (instr) {
                        std::cout << "\nInstructor gasit:\n";
                        std::cout << "Specializare: " << instr->specializare() << "\n";
                        std::cout << "Tarif/oră: " << instr->tarifOra() << "\n";
                        break;
                    }
                }
            } else {
                std::cout << "Nu exista persoane in sistem.\n";
            }
        }
        else {
            std::cout << "Optiune invalida. Incearca din nou.\n";
        }

        // Clear input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}