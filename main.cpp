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

void testInfo(int op, const std::string& mesaj) {
    std::cout << "\n[TEST] Optiune " << op << " -> " << mesaj << "\n";
}

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
    std::cout << "8) Afiseaza parinte si copiii\n";
    std::cout << "9) Copii sortati dupa varsta\n";
    std::cout << "10) Instructori sortati dupa tarif\n";
    std::cout << "11) Afiseaza profesori\n";
    std::cout << "12) Sterge copii sub o varsta\n";
    std::cout << "13) Modifica telefon parinte\n";
    std::cout << "14) Modifica specializare/tarif instructor\n";
    std::cout << "15) Administrare::primulDupa\n";
    std::cout << "16) Administrare::toate\n";
    std::cout << "17) Administrare::esteGoala\n";
    std::cout << "18) Afiseaza materie/nivel profesor\n";
    std::cout << "19) Modifica materie/nivel profesor\n";
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
                testInfo(0, "Iesire program");
                break;
            }

            if (op == 1) {
                testInfo(1, "Creare Copil");
                std::string n, e;
                int v;
                std::cin >> n >> e >> v;
                auto c = std::make_unique<Copil>(n, e, v);
                administrareCopii.adauga(*c);
                persoane.push_back(std::move(c));
            }
            else if (op == 2) {
                testInfo(2, "Creare Parinte");
                std::string n, e, t;
                std::cin >> n >> e >> t;
                auto p = std::make_unique<Parinte>(n, e, t);
                administrareParinti.adauga(*p);
                persoane.push_back(std::move(p));
            }
            else if (op == 3) {
                testInfo(3, "Creare Instructor + specializare()");
                std::string n, e, s;
                double tarif;
                std::cin >> n >> e >> s >> tarif;
                auto i = std::make_unique<Instructor>(n, e, s, tarif);
                std::cout << "Specializare initiala: " << i->specializare() << "\n";
                *i += 5;
                administrareInstructori.adauga(*i);
                persoane.push_back(std::move(i));
            }
            else if (op == 4) {
                testInfo(4, "Creare Profesor");
                std::string n, e, m, niv;
                double tarif;
                std::cin >> n >> e >> m >> niv >> tarif;
                auto pr = std::make_unique<Profesor>(n, e, m, niv, tarif);
                administrareProfesori.adauga(*pr);
                persoane.push_back(std::move(pr));
            }
            else if (op == 5) {
                testInfo(5, "Persoana::email");
                for (const auto& p : persoane) {
                    std::cout << *p << "\n";
                    std::cout << "Email = " << p->email() << "\n";
                }
            }
            else if (op == 6) {
                testInfo(6, "setNume + setEmail");
                int id;
                std::string n, e;
                std::cin >> id >> n >> e;
                auto* p = gasesteMut(persoane, id);
                if (p) {
                    p->setNume(n);
                    p->setEmail(e);
                }
            }
            else if (op == 7) {
                testInfo(7, "Asociere Parinte-Copil");
                int idP, idC;
                std::cin >> idP >> idC;
                auto* p = dynamic_cast<Parinte*>(gasesteMut(persoane, idP));
                if (p) p->adaugaCopil(idC);
            }
            else if (op == 8) {
                testInfo(8, "Parinte::telefon + copiiIds");
                int id;
                std::cin >> id;
                const auto* p = dynamic_cast<const Parinte*>(gasesteConst(persoane, id));
                if (p) {
                    std::cout << p->telefon() << "\n";
                    for (int cid : p->copiiIds()) {
                        const auto* c = dynamic_cast<const Copil*>(gasesteConst(persoane, cid));
                        if (c) std::cout << c->nume() << "\n";
                    }
                }
            }
            else if (op == 9) {
                testInfo(9, "sorteazaDupa Copil");
                administrareCopii.sorteazaDupa([](const Copil& a, const Copil& b) {
                    return a.varsta() < b.varsta();
                });
                administrareCopii.afiseaza(std::cout);
            }
            else if (op == 10) {
                testInfo(10, "operator< Instructor");
                administrareInstructori.sorteazaDupa([](const Instructor& a, const Instructor& b) {
                    return a < b;
                });
                administrareInstructori.afiseaza(std::cout);
            }
            else if (op == 11) {
                testInfo(11, "Afisare Profesori");
                administrareProfesori.afiseaza(std::cout);
            }
            else if (op == 12) {
                testInfo(12, "stergeDaca Copil");
                int v;
                std::cin >> v;
                administrareCopii.stergeDaca([v](const Copil& c) {
                    return c.varsta() < v;
                });
            }
            else if (op == 13) {
                testInfo(13, "Parinte::setTelefon");
                int id;
                std::string tel;
                std::cin >> id >> tel;
                auto* p = dynamic_cast<Parinte*>(gasesteMut(persoane, id));
                if (p) p->setTelefon(tel);
            }
            else if (op == 14) {
                testInfo(14, "Instructor::setSpecializare + setTarifOra");
                int id;
                std::string s;
                double t;
                std::cin >> id >> s >> t;
                auto* i = dynamic_cast<Instructor*>(gasesteMut(persoane, id));
                if (i) {
                    i->setSpecializare(s);
                    i->setTarifOra(t);
                }
            }
            else if (op == 15) {
                testInfo(15, "Administrare::primulDupa");
                const Copil& c = administrareCopii.primulDupa([](const Copil&) { return true; });
                std::cout << c << "\n";
            }
            else if (op == 16) {
                testInfo(16, "Administrare::toate");
                for (const auto& c : administrareCopii.toate()) {
                    std::cout << c << "\n";
                }
            }
            else if (op == 17) {
                testInfo(17, "Administrare::esteGoala");
                std::cout << administrareProfesori.esteGoala() << "\n";
            }
            else if (op == 18) {
                testInfo(18, "Profesor::materie + nivel");
                int id;
                std::cin >> id;
                const auto* pr = dynamic_cast<const Profesor*>(gasesteConst(persoane, id));
                if (pr) {
                    std::cout << pr->materie() << " " << pr->nivel() << "\n";
                }
            }
            else if (op == 19) {
                testInfo(19, "Profesor::setMaterie + setNivel");
                int id;
                std::string m, n;
                std::cin >> id >> m >> n;
                auto* pr = dynamic_cast<Profesor*>(gasesteMut(persoane, id));
                if (pr) {
                    pr->setMaterie(m);
                    pr->setNivel(n);
                }
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Eroare: " << ex.what() << "\n";
        }
    }

    return 0;
}
