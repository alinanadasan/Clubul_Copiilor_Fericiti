#include "Meniu.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <cctype>

#include "PersoanaFactory.h"
#include "Copil.h"
#include "Parinte.h"
#include "Instructor.h"
#include "Profesor.h"

#include "Administrare.h"
#include "SortareCopiiDupaVarsta.h"

namespace {
std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}
} // namespace

int Meniu::citesteInt(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;
        int x{};
        if (std::cin >> x) return x;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valoare invalida. Incercati din nou.\n";
    }
}

double Meniu::citesteDouble(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;
        double x{};
        if (std::cin >> x) return x;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valoare invalida. Incercati din nou.\n";
    }
}

std::string Meniu::citesteString(const std::string& mesaj) {
    std::cout << mesaj;
    std::string s;
    std::cin >> s; // simplu: fara spatii
    return s;
}

void Meniu::ruleaza() {
    while (true) {
        std::cout << "\n=== Clubul Copiilor ===\n"
                  << "1) Testare automata\n"
                  << "2) Testare manuala\n"
                  << "3) Iesire\n";

        const int opt = citesteInt("Alege: ");
        if (opt == 1) {
            std::cout << "[TEST AUTOMAT] Se citesc date din fisierul tastatura.txt\n";
            try {
                ruleazaTestAutomatDinFisier("tastatura.txt");
            } catch (const std::exception& e) {
                std::cout << "Eroare test automat: " << e.what() << "\n";
            }
        } else if (opt == 2) {
            meniuManual();
        } else if (opt == 3) {
            std::cout << "La revedere!\n";
            return;
        } else {
            std::cout << "Optiune invalida.\n";
        }
    }
}

void Meniu::meniuManual() {
    while (true) {
        std::cout << "\n=== Testare manuala ===\n"
                  << "1) Gestioneaza persoane\n"
                  << "0) Inapoi\n";
        const int opt = citesteInt("Alege: ");
        if (opt == 1) meniuGestioneazaPersoane();
        else if (opt == 0) return;
        else std::cout << "Optiune invalida.\n";
    }
}

void Meniu::meniuGestioneazaPersoane() {
    while (true) {
        std::cout << "\n=== Gestioneaza persoane ===\n"
                  << "1) Adauga persoana\n"
                  << "2) Afiseaza toate\n"
                  << "3) Afiseaza dupa ID\n"
                  << "4) Sterge dupa ID\n"
                  << "5) Cauta dupa nume\n"
                  << "6) Sorteaza\n"
                  << "7) Operatii specifice (downcast)\n"
                  << "0) Inapoi\n";

        const int opt = citesteInt("Alege: ");
        try {
            if (opt == 1) adaugaPersoanaManual();
            else if (opt == 2) afiseazaToate();
            else if (opt == 3) afiseazaDupaId();
            else if (opt == 4) stergeDupaId();
            else if (opt == 5) cautaDupaNume();
            else if (opt == 6) sorteazaPersoane();
            else if (opt == 7) operatiiSpecificeDowncast();
            else if (opt == 0) return;
            else std::cout << "Optiune invalida.\n";
        } catch (const std::exception& e) {
            // catch upcast: prindem tot ca std::exception
            std::cout << "Eroare: " << e.what() << "\n";
        }
    }
}

void Meniu::adaugaPersoanaManual() {
    std::cout << "\nTip persoana:\n"
              << "1) Copil\n"
              << "2) Parinte\n"
              << "3) Instructor\n"
              << "4) Profesor\n";
    const int tip = citesteInt("Alege: ");

    const std::string nume = citesteString("Nume: ");
    const std::string prenume = citesteString("Prenume: ");

    if (tip == 1) {
        const int varsta = citesteInt("Varsta (3-18): ");
        registru_.adauga(PersoanaFactory::creeazaCopil(nume, prenume, varsta));
        std::cout << "Copil adaugat.\n";
    } else if (tip == 2) {
        const std::string email = citesteString("Email: ");
        const std::string telefon = citesteString("Telefon: ");
        registru_.adauga(PersoanaFactory::creeazaParinte(nume, prenume, email, telefon));
        std::cout << "Parinte adaugat.\n";
    } else if (tip == 3) {
        const std::string email = citesteString("Email: ");
        const std::string spec = citesteString("Specializare: ");
        const double tarif = citesteDouble("Tarif/ora: ");
        registru_.adauga(PersoanaFactory::creeazaInstructor(nume, prenume, email, spec, tarif));
        std::cout << "Instructor adaugat.\n";
    } else if (tip == 4) {
        const std::string email = citesteString("Email: ");
        const std::string materie = citesteString("Materie: ");
        const std::string nivel = citesteString("Nivel: ");
        const double tarif = citesteDouble("Tarif/ora: ");
        registru_.adauga(PersoanaFactory::creeazaProfesor(nume, prenume, email, materie, nivel, tarif));
        std::cout << "Profesor adaugat.\n";
    } else {
        throw std::invalid_argument("Tip persoana invalid.");
    }
}

void Meniu::afiseazaToate() const {
    if (registru_.esteGol()) {
        std::cout << "Nu exista persoane.\n";
        return;
    }
    registru_.afiseaza(std::cout);
}

void Meniu::afiseazaDupaId() const {
    const int id = citesteInt("ID: ");
    const auto& p = registru_.gasesteDupaId(id);
    std::cout << p << "\n";
}

void Meniu::stergeDupaId() {
    const int id = citesteInt("ID: ");
    const bool ok = registru_.stergeDupaId(id);
    std::cout << (ok ? "Sters.\n" : "Nu exista acest ID.\n");
}

void Meniu::cautaDupaNume() const {
    const std::string cautat = toLower(citesteString("Nume (fara spatii): "));
    const auto ptrs = registru_.toatePtr();

    bool gasit = false;
    for (const auto* p : ptrs) {
        if (p && toLower(p->nume()) == cautat) {
            std::cout << *p << "\n";
            gasit = true;
        }
    }
    if (!gasit) std::cout << "Nicio persoana gasita.\n";
}

void Meniu::sorteazaPersoane() {
    std::cout << "\nSorteaza dupa:\n"
              << "1) ID\n"
              << "2) Nume\n"
              << "3) Tip\n";
    const int opt = citesteInt("Alege: ");

    if (opt == 1) {
        registru_.sorteazaDupa([](const std::unique_ptr<Persoana>& a,
                                 const std::unique_ptr<Persoana>& b) {
            return a->id() < b->id();
        });
    } else if (opt == 2) {
        registru_.sorteazaDupa([](const std::unique_ptr<Persoana>& a,
                                 const std::unique_ptr<Persoana>& b) {
            if (a->nume() != b->nume()) return a->nume() < b->nume();
            return a->prenume() < b->prenume();
        });
    } else if (opt == 3) {
        registru_.sorteazaDupa([](const std::unique_ptr<Persoana>& a,
                                 const std::unique_ptr<Persoana>& b) {
            return a->tip() < b->tip();
        });
    } else {
        throw std::invalid_argument("Optiune sortare invalida.");
    }

    std::cout << "Sortare efectuata.\n";
}

void Meniu::operatiiSpecificeDowncast() {
    std::cout << "\n1) Creste varsta unui copil (ID)\n"
              << "2) Mareste tariful unui instructor/profesor (ID)\n";
    const int opt = citesteInt("Alege: ");
    const int id = citesteInt("ID: ");

    Persoana& p = registru_.gasesteDupaId(id);

    if (opt == 1) {
        auto* c = dynamic_cast<Copil*>(&p);
        if (!c) throw std::runtime_error("Persoana nu este Copil.");
        c->setVarsta(c->varsta() + 1);
        std::cout << "Varsta crescuta. " << *c << "\n";
    } else if (opt == 2) {
        auto* inst = dynamic_cast<Instructor*>(&p); // merge si pentru Profesor (upcast)
        if (!inst) throw std::runtime_error("Persoana nu este Instructor/Profesor.");
        const double suma = citesteDouble("Suma marire: ");
        (*inst) += suma; // operator membru
        std::cout << "Tarif modificat. " << *inst << "\n";
    } else {
        throw std::invalid_argument("Optiune invalida.");
    }
}

void Meniu::ruleazaTestAutomatDinFisier(const std::string& fisier) {
    std::ifstream fin(fisier);
    if (!fin) {
        throw std::runtime_error("Nu pot deschide fisierul tastatura.txt.");
    }

    // Format fisier (simplu):
    // N
    // TIP nume prenume [rest]
    // TIP: COPIL / PARINTE / INSTRUCTOR / PROFESOR
    //
    // COPIL nume prenume varsta
    // PARINTE nume prenume email telefon
    // INSTRUCTOR nume prenume email specializare tarif
    // PROFESOR nume prenume email materie nivel tarif

    int n = 0;
    fin >> n;
    if (n <= 0) {
        throw std::runtime_error("Fisier invalid: N trebuie > 0.");
    }

    for (int i = 0; i < n; ++i) {
        std::string tip;
        fin >> tip;
        tip = toLower(tip);

        if (tip == "copil") {
            std::string nume, prenume;
            int varsta = 0;
            fin >> nume >> prenume >> varsta;
            registru_.adauga(PersoanaFactory::creeazaCopil(nume, prenume, varsta));
        } else if (tip == "parinte") {
            std::string nume, prenume, email, telefon;
            fin >> nume >> prenume >> email >> telefon;
            registru_.adauga(PersoanaFactory::creeazaParinte(nume, prenume, email, telefon));
        } else if (tip == "instructor") {
            std::string nume, prenume, email, spec;
            double tarif = 0;
            fin >> nume >> prenume >> email >> spec >> tarif;
            registru_.adauga(PersoanaFactory::creeazaInstructor(nume, prenume, email, spec, tarif));
        } else if (tip == "profesor") {
            std::string nume, prenume, email, materie, nivel;
            double tarif = 0;
            fin >> nume >> prenume >> email >> materie >> nivel >> tarif;
            registru_.adauga(PersoanaFactory::creeazaProfesor(nume, prenume, email, materie, nivel, tarif));
        } else {
            throw std::runtime_error("Fisier invalid: tip necunoscut.");
        }
    }

    // Demonstrez explicit cele 2 instantiari ale template-ului Administrare<T>
    // (fara sa incurc registrul principal polimorf).
    Administrare<Copil> adminCopii;
    Administrare<Parinte> adminParinti;

    for (const auto* p : registru_.toatePtr()) {
        if (const auto* c = dynamic_cast<const Copil*>(p)) {
            adminCopii.adauga(*c);
        } else if (const auto* par = dynamic_cast<const Parinte*>(p)) {
            adminParinti.adauga(*par);
        }
    }

    SortareCopiiDupaVarsta strat;
    adminCopii.sorteazaCuStrategie(strat);

    std::cout << "\n--- [TEST AUTOMAT] Persoane incarcate ---\n";
    registru_.afiseaza(std::cout);

    std::cout << "\n--- [TEST AUTOMAT] Copii sortati dupa varsta (Strategy) ---\n";
    adminCopii.afiseaza(std::cout);

    std::cout << "\n--- [TEST AUTOMAT] Parinti (instantiere template #2) ---\n";
    adminParinti.afiseaza(std::cout);
}
