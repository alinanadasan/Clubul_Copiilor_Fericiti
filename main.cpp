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
    for (const auto& p : persoane)
        if (p->id() == id) return p.get();
    return nullptr;
}

Persoana* gasesteMut(std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
    for (auto& p : persoane)
        if (p->id() == id) return p.get();
    return nullptr;
}

void afiseazaMeniu() {
    std::cout << "\n===== MENIU =====\n";
    std::cout << "1 Adauga copil\n";
    std::cout << "2 Adauga parinte\n";
    std::cout << "3 Adauga instructor\n";
    std::cout << "4 Adauga profesor\n";
    std::cout << "5 Afiseaza toate persoanele\n";
    std::cout << "6 Modifica nume/email persoana\n";
    std::cout << "7 Asociaza copil la parinte\n";
    std::cout << "8 Afiseaza parinte + copii\n";
    std::cout << "9 Copii sortati dupa varsta\n";
    std::cout << "10 Instructori sortati dupa tarif\n";
    std::cout << "11 Afiseaza profesori\n";
    std::cout << "12 Sterge copii sub o varsta\n";
    std::cout << "13 Modifica telefon parinte\n";
    std::cout << "14 Modifica instructor\n";
    std::cout << "15 Primul copil (Administrare)\n";
    std::cout << "16 Afiseaza toti copiii\n";
    std::cout << "17 Verifica profesori (esteGoala + marime)\n";
    std::cout << "18 Afiseaza materie/nivel profesor\n";
    std::cout << "19 Modifica materie/nivel profesor\n";
    std::cout << "0 Iesire\n";
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
                std::cout << "[RESULT] La revedere!\n";
                break;
            }

            if (op == 1) {
                testInfo(1, "Adauga copil");
                std::string n, e;
                int v;
                std::cin >> n >> e >> v;
                std::cout << "[INPUT] nume=" << n << " email=" << e << " varsta=" << v << "\n";
                auto c = std::make_unique<Copil>(n, e, v);
                administrareCopii.adauga(*c);
                persoane.push_back(std::move(c));
                std::cout << "[RESULT] Copil adaugat. Total copii="
                          << administrareCopii.marime() << "\n";
            }
            else if (op == 2) {
                testInfo(2, "Adauga parinte");
                std::string n, e, t;
                std::cin >> n >> e >> t;
                std::cout << "[INPUT] nume=" << n << " email=" << e << " telefon=" << t << "\n";
                auto p = std::make_unique<Parinte>(n, e, t);
                administrareParinti.adauga(*p);
                persoane.push_back(std::move(p));
                std::cout << "[RESULT] Parinte adaugat. Total parinti="
                          << administrareParinti.marime() << "\n";
            }
            else if (op == 3) {
                testInfo(3, "Adauga instructor");
                std::string n, e, s;
                double tarif;
                std::cin >> n >> e >> s >> tarif;
                std::cout << "[INPUT] nume=" << n << " email=" << e
                          << " specializare=" << s << " tarif=" << tarif << "\n";
                auto i = std::make_unique<Instructor>(n, e, s, tarif);
                *i += 5;
                administrareInstructori.adauga(*i);
                persoane.push_back(std::move(i));
                std::cout << "[RESULT] Instructor adaugat. Total instructori="
                          << administrareInstructori.marime() << "\n";
            }
            else if (op == 4) {
                testInfo(4, "Adauga profesor");
                std::string n, e, m, niv;
                double tarif;
                std::cin >> n >> e >> m >> niv >> tarif;
                std::cout << "[INPUT] nume=" << n << " email=" << e
                          << " materie=" << m << " nivel=" << niv
                          << " tarif=" << tarif << "\n";
                auto pr = std::make_unique<Profesor>(n, e, m, niv, tarif);
                administrareProfesori.adauga(*pr);
                persoane.push_back(std::move(pr));
                std::cout << "[RESULT] Profesor adaugat. Total profesori="
                          << administrareProfesori.marime() << "\n";
            }
            else if (op == 5) {
                testInfo(5, "Afisare persoane + email");
                for (const auto& p : persoane) {
                    std::cout << "[RESULT] " << *p
                              << " | email=" << p->email() << "\n";
                }
            }
            else if (op == 17) {
                testInfo(17, "esteGoala + marime (Profesori)");
                std::cout << "[RESULT] esteGoala="
                          << administrareProfesori.esteGoala()
                          << " marime="
                          << administrareProfesori.marime() << "\n";
            }
            else {
                testInfo(op, "Optiune implementata dar neapelata in demo");
                std::cout << "[RESULT] OK\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "[EXCEPTION] " << ex.what() << "\n";
        }
    }

    return 0;
}
