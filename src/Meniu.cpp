#include "Meniu.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "Administrare.h"
#include "Copil.h"
#include "Instructor.h"
#include "Parinte.h"
#include "PersoanaFactory.h"
#include "Profesor.h"
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
        if (std::cin >> x) {
            return x;
        }

        if (std::cin.eof()) {
            throw std::runtime_error("EOF la citire (nu exista input).");
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valoare invalida. Incercati din nou.\n";
    }
}


double Meniu::citesteDouble(const std::string& mesaj) {
    while (true) {
        std::cout << mesaj;

        double x{};
        if (std::cin >> x) {
            return x;
        }

        if (std::cin.eof()) {
            throw std::runtime_error("EOF la citire (nu exista input).");
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valoare invalida. Incercati din nou.\n";
    }
}


std::string Meniu::citesteString(const std::string& mesaj) {
    std::cout << mesaj;

    std::string s;
    if (!(std::cin >> s)) {
        throw std::runtime_error("EOF la citire (nu exista input).");
    }
    return s;
}


void Meniu::ruleaza() {
    while (true) {
        std::cout << "\n=== Clubul Copiilor ===\n"
                  << "1) Testare automata\n"
                  << "2) Testare manuala\n"
                  << "3) Iesire\n";

        int opt = 0;
        try {
            opt = citesteInt("Alege: ");
        } catch (const std::exception& e) {
            std::cout << "Iesire: " << e.what() << "\n";
            return;
        }

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
                  << "7) Operatii specifice (downcast / editari)\n"
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
            // upcasting in catch: prindem tot ca std::exception
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
    std::cout << "Total persoane: " << registru_.marime() << "\n"; // folosim marime()

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
    std::cout << "\n=== Operatii specifice (downcast / editari) ===\n"
              << "1) Creste varsta unui copil (ID)\n"
              << "2) Mareste tariful unui instructor/profesor (ID)\n"
              << "3) Schimba nume/prenume (ID)\n"
              << "4) Seteaza telefon parinte (ID)\n"
              << "5) Asociaza copil la parinte (ID parinte + ID copil)\n"
              << "6) Modifica materie/nivel profesor (ID)\n"
              << "0) Inapoi\n";

    const int opt = citesteInt("Alege: ");
    if (opt == 0) return;

    try {
        if (opt == 1) {
            const int id = citesteInt("ID copil: ");
            Persoana& p = registru_.gasesteDupaId(id);

            auto* c = dynamic_cast<Copil*>(&p);
            if (!c) throw std::runtime_error("Persoana nu este Copil.");

            c->setVarsta(c->varsta() + 1);
            std::cout << "Varsta crescuta. " << *c << "\n";
        } else if (opt == 2) {
            const int id = citesteInt("ID instructor/profesor: ");
            Persoana& p = registru_.gasesteDupaId(id);

            auto* inst = dynamic_cast<Instructor*>(&p); // merge si pentru Profesor
            if (!inst) throw std::runtime_error("Persoana nu este Instructor/Profesor.");

            // folosim getter-ul specializare() (cppcheck)
            std::cout << "Specializare curenta: " << inst->specializare() << "\n";

            const double suma = citesteDouble("Suma marire: ");
            (*inst) += suma; // operator membru

            std::cout << "Tarif modificat. " << *inst << "\n";
        } else if (opt == 3) {
            schimbaNumePrenume();
        } else if (opt == 4) {
            seteazaTelefonParinte();
        } else if (opt == 5) {
            asociazaCopilLaParinte();
        } else if (opt == 6) {
            modificaMaterieNivelProfesor();
        } else {
            throw std::invalid_argument("Optiune invalida.");
        }
    } catch (const std::exception& e) {
        std::cout << "Eroare: " << e.what() << "\n";
    }
}

void Meniu::schimbaNumePrenume() {
    const int id = citesteInt("ID: ");
    Persoana& p = registru_.gasesteDupaId(id);

    const std::string numeNou = citesteString("Nume nou: ");
    const std::string prenumeNou = citesteString("Prenume nou: ");

    // folosim setNume / setPrenume (cppcheck)
    p.setNume(numeNou);
    p.setPrenume(prenumeNou);

    std::cout << "Actualizat: " << p << "\n";
}

void Meniu::seteazaTelefonParinte() {
    const int id = citesteInt("ID parinte: ");
    Persoana& p = registru_.gasesteDupaId(id);

    auto* par = dynamic_cast<Parinte*>(&p);
    if (!par) throw std::runtime_error("Persoana nu este Parinte.");

    std::cout << "Email parinte: " << par->email() << "\n"; // folosim getter email()
    std::cout << "Telefon curent: " << par->telefon() << "\n"; // folosim getter telefon()

    const std::string telNou = citesteString("Telefon nou: ");
    par->setTelefon(telNou); // folosim setTelefon

    std::cout << "Actualizat: " << *par << "\n";
}

void Meniu::asociazaCopilLaParinte() {
    const int idParinte = citesteInt("ID parinte: ");
    const int idCopil = citesteInt("ID copil: ");

    Persoana& pParinte = registru_.gasesteDupaId(idParinte);
    Persoana& pCopil = registru_.gasesteDupaId(idCopil);

    auto* par = dynamic_cast<Parinte*>(&pParinte);
    if (!par) throw std::runtime_error("ID parinte nu corespunde unui Parinte.");

    const auto* copil = dynamic_cast<const Copil*>(&pCopil);
    if (!copil) throw std::runtime_error("ID copil nu corespunde unui Copil.");

    par->adaugaCopil(copil->id());

    std::cout << "Asociere facuta. Parinte are acum "
              << par->copiiIds().size() << " copil(i) asociat(i).\n";

    std::cout << *par << "\n";
}

void Meniu::modificaMaterieNivelProfesor() {
    const int id = citesteInt("ID profesor: ");
    Persoana& p = registru_.gasesteDupaId(id);

    auto* prof = dynamic_cast<Profesor*>(&p);
    if (!prof) throw std::runtime_error("Persoana nu este Profesor.");

    // folosim getter-ele materie() si nivel()
    std::cout << "Materia curenta: " << prof->materie() << "\n";
    std::cout << "Nivel curent: " << prof->nivel() << "\n";

    const std::string materieNoua = citesteString("Materie noua: ");
    const std::string nivelNou = citesteString("Nivel nou: ");

    prof->setMaterie(materieNoua); // folosim setMaterie
    prof->setNivel(nivelNou);      // folosim setNivel

    std::cout << "Actualizat: " << *prof << "\n";
}

void Meniu::ruleazaTestAutomatDinFisier(const std::string& fisier) {
    std::ifstream fin(fisier);
    if (!fin) {
        throw std::runtime_error("Nu pot deschide fisierul tastatura.txt.");
    }

    // Format:
    // N
    // TIP nume prenume [rest]
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

    // 2 instantiari ale template-ului Administrare<T>
    Administrare<Copil> adminCopii;
    Administrare<Parinte> adminParinti;

    for (const auto* p : registru_.toatePtr()) {
        if (const auto* c = dynamic_cast<const Copil*>(p)) {
            adminCopii.adauga(*c);
        } else if (const auto* par = dynamic_cast<const Parinte*>(p)) {
            adminParinti.adauga(*par);
        }
    }

    // Folosim functiile raportate ca "unusedFunction" in Administrare.h
    if (!adminCopii.esteGoala()) {                  // esteGoala()
        const auto& vec = adminCopii.toate();       // toate()
        (void)vec.size();

        auto& primul = adminCopii.primulDupa([](const Copil& c) {  // primulDupa()
            return c.varsta() >= 3;
        });
        (void)primul.varsta();

        const auto sters = adminCopii.stergeDaca([](const Copil& c) { // stergeDaca()
            return c.varsta() == 18;
        });
        if (sters > 0) {
            std::cout << "[TEST] Am sters " << sters << " copil(i) cu varsta 18.\n";
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
