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
        std::cout << "[INPUT] invalid, reincearca: ";
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
    std::cout << "5) Afiseaza toate persoanele (si email)\n";
    std::cout << "6) Modifica nume/email persoana\n";
    std::cout << "7) Asociaza copil la parinte\n";
    std::cout << "8) Afiseaza parinte + copii (telefon/copiiIds)\n";
    std::cout << "9) Copii sortati dupa varsta\n";
    std::cout << "10) Instructori sortati dupa tarif\n";
    std::cout << "11) Afiseaza profesori\n";
    std::cout << "12) Sterge copii sub o varsta\n";
    std::cout << "13) Modifica telefon parinte\n";
    std::cout << "14) Modifica specializare/tarif instructor\n";
    std::cout << "15) Administrare::primulDupa (copil)\n";
    std::cout << "16) Administrare::toate (copii)\n";
    std::cout << "17) Administrare::esteGoala + marime (profesori)\n";
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
                testInfo(0, "Iesire");
                std::cout << "[RESULT] La revedere!\n";
                break;
            }

            if (op == 1) {
                testInfo(1, "Creare Copil + Administrare<Copil>::adauga");
                std::string n, e;
                int v;
                std::cin >> n >> e >> v;
                std::cout << "[INPUT] nume=" << n << " email=" << e << " varsta=" << v << "\n";
                auto c = std::make_unique<Copil>(n, e, v);
                administrareCopii.adauga(*c);
                std::cout << "[RESULT] " << *c << "\n";
                persoane.push_back(std::move(c));
                std::cout << "[RESULT] copii in administrare=" << administrareCopii.marime() << "\n";
            }
            else if (op == 2) {
                testInfo(2, "Creare Parinte + Administrare<Parinte>::adauga");
                std::string n, e, t;
                std::cin >> n >> e >> t;
                std::cout << "[INPUT] nume=" << n << " email=" << e << " telefon=" << t << "\n";
                auto p = std::make_unique<Parinte>(n, e, t);
                administrareParinti.adauga(*p);
                std::cout << "[RESULT] " << *p << "\n";
                persoane.push_back(std::move(p));
                std::cout << "[RESULT] parinti in administrare=" << administrareParinti.marime() << "\n";
            }
            else if (op == 3) {
                testInfo(3, "Creare Instructor + specializare() + operator+= + Administrare<Instructor>::adauga");
                std::string n, e, s;
                double tarif;
                std::cin >> n >> e >> s >> tarif;
                std::cout << "[INPUT] nume=" << n << " email=" << e << " spec=" << s << " tarif=" << tarif << "\n";
                auto i = std::make_unique<Instructor>(n, e, s, tarif);
                std::cout << "[RESULT] specializare initiala=" << i->specializare() << "\n";
                *i += 5.0;
                administrareInstructori.adauga(*i);
                std::cout << "[RESULT] " << *i << "\n";
                persoane.push_back(std::move(i));
                std::cout << "[RESULT] instructori in administrare=" << administrareInstructori.marime() << "\n";
            }
            else if (op == 4) {
                testInfo(4, "Creare Profesor + Administrare<Profesor>::adauga");
                std::string n, e, m, niv;
                double tarif;
                std::cin >> n >> e >> m >> niv >> tarif;
                std::cout << "[INPUT] nume=" << n << " email=" << e << " materie=" << m << " nivel=" << niv << " tarif=" << tarif << "\n";
                auto pr = std::make_unique<Profesor>(n, e, m, niv, tarif);
                administrareProfesori.adauga(*pr);
                std::cout << "[RESULT] " << *pr << "\n";
                persoane.push_back(std::move(pr));
                std::cout << "[RESULT] profesori in administrare=" << administrareProfesori.marime() << "\n";
            }
            else if (op == 5) {
                testInfo(5, "Afisare persoane + Persoana::email()");
                std::cout << "[RESULT] total persoane=" << persoane.size() << "\n";
                for (const auto& p : persoane) {
                    std::cout << "  " << *p << "\n";
                    std::cout << "    email=" << p->email() << "\n";
                }
            }
            else if (op == 6) {
                testInfo(6, "Modificare nume/email (setNume/setEmail)");
                int id;
                std::string n, e;
                std::cin >> id >> n >> e;
                std::cout << "[INPUT] id=" << id << " numeNou=" << n << " emailNou=" << e << "\n";
                auto* p = gasesteMut(persoane, id);
                if (!p) {
                    std::cout << "[RESULT] persoana inexistenta\n";
                } else {
                    p->setNume(n);
                    p->setEmail(e);
                    std::cout << "[RESULT] " << *p << "\n";
                }
            }
            else if (op == 7) {
                testInfo(7, "Asociere copil la parinte (Parinte::adaugaCopil)");
                int idP, idC;
                std::cin >> idP >> idC;
                std::cout << "[INPUT] parinteId=" << idP << " copilId=" << idC << "\n";
                auto* p = dynamic_cast<Parinte*>(gasesteMut(persoane, idP));
                const auto* c = dynamic_cast<const Copil*>(gasesteConst(persoane, idC));
                if (!p || !c) {
                    std::cout << "[RESULT] asociere invalida\n";
                } else {
                    p->adaugaCopil(idC);
                    std::cout << "[RESULT] asociat: " << p->nume() << " -> " << c->nume() << "\n";
                }
            }
            else if (op == 8) {
                testInfo(8, "Afisare parinte + telefon() + copiiIds()");
                int id;
                std::cin >> id;
                std::cout << "[INPUT] parinteId=" << id << "\n";
                const auto* p = dynamic_cast<const Parinte*>(gasesteConst(persoane, id));
                if (!p) {
                    std::cout << "[RESULT] nu este parinte\n";
                } else {
                    std::cout << "[RESULT] parinte=" << p->nume() << " telefon=" << p->telefon() << "\n";
                    std::cout << "[RESULT] copiiIds=";
                    for (int cid : p->copiiIds()) std::cout << cid << " ";
                    std::cout << "\n";
                    for (int cid : p->copiiIds()) {
                        const auto* c = dynamic_cast<const Copil*>(gasesteConst(persoane, cid));
                        if (c) std::cout << "  copil: " << c->nume() << " varsta=" << c->varsta() << "\n";
                    }
                }
            }
            else if (op == 9) {
                testInfo(9, "Administrare<Copil>::sorteazaDupa (lambda) + afiseaza");
                administrareCopii.sorteazaDupa([](const Copil& a, const Copil& b) {
                    return a.varsta() < b.varsta();
                });
                std::cout << "[RESULT] copii sortati, count=" << administrareCopii.marime() << "\n";
                administrareCopii.afiseaza(std::cout);
            }
            else if (op == 10) {
                testInfo(10, "Administrare<Instructor>::sorteazaDupa (operator<) + afiseaza");
                administrareInstructori.sorteazaDupa([](const Instructor& a, const Instructor& b) {
                    return a < b;
                });
                std::cout << "[RESULT] instructori sortati, count=" << administrareInstructori.marime() << "\n";
                administrareInstructori.afiseaza(std::cout);
            }
            else if (op == 11) {
                testInfo(11, "Administrare<Profesor>::afiseaza");
                std::cout << "[RESULT] profesori, count=" << administrareProfesori.marime() << "\n";
                administrareProfesori.afiseaza(std::cout);
            }
            else if (op == 12) {
                testInfo(12, "Administrare<Copil>::stergeDaca");
                int v;
                std::cin >> v;
                std::cout << "[INPUT] pragVarsta=" << v << "\n";
                std::size_t inainte = administrareCopii.marime();
                std::size_t sterse = administrareCopii.stergeDaca([v](const Copil& c) {
                    return c.varsta() < v;
                });
                std::cout << "[RESULT] copii inainte=" << inainte
                          << " sterse=" << sterse
                          << " ramase=" << administrareCopii.marime() << "\n";
            }
            else if (op == 13) {
                testInfo(13, "Parinte::setTelefon + telefon()");
                int id;
                std::string tel;
                std::cin >> id >> tel;
                std::cout << "[INPUT] parinteId=" << id << " telefonNou=" << tel << "\n";
                auto* p = dynamic_cast<Parinte*>(gasesteMut(persoane, id));
                if (!p) {
                    std::cout << "[RESULT] nu este parinte\n";
                } else {
                    p->setTelefon(tel);
                    std::cout << "[RESULT] telefon=" << p->telefon() << "\n";
                }
            }
            else if (op == 14) {
                testInfo(14, "Instructor::setSpecializare + setTarifOra + specializare/tarifOra");
                int id;
                std::string s;
                double t;
                std::cin >> id >> s >> t;
                std::cout << "[INPUT] instructorId=" << id << " specNou=" << s << " tarifNou=" << t << "\n";
                auto* i = dynamic_cast<Instructor*>(gasesteMut(persoane, id));
                if (!i) {
                    std::cout << "[RESULT] nu este instructor\n";
                } else {
                    i->setSpecializare(s);
                    i->setTarifOra(t);
                    std::cout << "[RESULT] specializare=" << i->specializare()
                              << " tarifOra=" << i->tarifOra() << "\n";
                }
            }
            else if (op == 15) {
                testInfo(15, "Administrare<Copil>::primulDupa");
                const Copil& c = administrareCopii.primulDupa([](const Copil&) { return true; });
                std::cout << "[RESULT] primul copil: " << c << "\n";
            }
            else if (op == 16) {
                testInfo(16, "Administrare<Copil>::toate");
                const auto& toti = administrareCopii.toate();
                std::cout << "[RESULT] copii in toate()=" << toti.size() << "\n";
                for (const auto& c : toti) std::cout << "  " << c << "\n";
            }
            else if (op == 17) {
                testInfo(17, "Administrare<Profesor>::esteGoala + marime");
                bool goala = administrareProfesori.esteGoala();
                std::size_t nr = administrareProfesori.marime();
                std::cout << "[RESULT] esteGoala=" << goala << " marime=" << nr << "\n";
            }
            else if (op == 18) {
                testInfo(18, "Profesor::materie + nivel");
                int id;
                std::cin >> id;
                std::cout << "[INPUT] profesorId=" << id << "\n";
                const auto* pr = dynamic_cast<const Profesor*>(gasesteConst(persoane, id));
                if (!pr) {
                    std::cout << "[RESULT] nu este profesor\n";
                } else {
                    std::cout << "[RESULT] materie=" << pr->materie()
                              << " nivel=" << pr->nivel() << "\n";
                }
            }
            else if (op == 19) {
                testInfo(19, "Profesor::setMaterie + setNivel + (apoi getter)");
                int id;
                std::string m, niv;
                std::cin >> id >> m >> niv;
                std::cout << "[INPUT] profesorId=" << id << " materieNoua=" << m << " nivelNou=" << niv << "\n";
                auto* pr = dynamic_cast<Profesor*>(gasesteMut(persoane, id));
                if (!pr) {
                    std::cout << "[RESULT] nu este profesor\n";
                } else {
                    pr->setMaterie(m);
                    pr->setNivel(niv);
                    std::cout << "[RESULT] materie=" << pr->materie()
                              << " nivel=" << pr->nivel() << "\n";
                }
            }
            else {
                testInfo(op, "Optiune invalida");
                std::cout << "[RESULT] ignor\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "[EXCEPTION] " << ex.what() << "\n";
        }
    }

    return 0;
}
