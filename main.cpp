#include <iostream>
#include <vector>
#include <memory>
#include <limits>

#include "Copil.h"
#include "Parinte.h"
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

// cautare doar pentru citire
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
    std::cout << "3) Afiseaza toate persoanele\n";
    std::cout << "4) Modifica nume/email (dupa id)\n";
    std::cout << "5) Modifica varsta copil / telefon parinte\n";
    std::cout << "6) Asociaza copil la parinte\n";
    std::cout << "7) Afiseaza copiii unui parinte\n";
    std::cout << "8) Afiseaza copiii sortati dupa varsta\n";
    std::cout << "0) Iesire\n";
    std::cout << "Optiune: ";
}

int main() {
    std::vector<std::unique_ptr<Persoana>> persoane;

    // instantieri template (cerinta explicita)
    Administrare<Copil> administrareCopii;
    Administrare<Parinte> administrareParinti;

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

                auto copilPtr = std::make_unique<Copil>(nume, email, varsta);

                // folosesc template-ul
                administrareCopii.adauga(*copilPtr);

                std::cout << "Copil adaugat cu id=" << copilPtr->id() << "\n";
                persoane.push_back(std::move(copilPtr));
            }
            else if (op == 2) {
                std::string nume, email, telefon;

                std::cout << "Nume parinte: ";
                std::cin >> nume;
                std::cout << "Email parinte: ";
                std::cin >> email;
                std::cout << "Telefon parinte: ";
                std::cin >> telefon;

                auto parintePtr = std::make_unique<Parinte>(nume, email, telefon);

                // folosesc template-ul
                administrareParinti.adauga(*parintePtr);

                std::cout << "Parinte adaugat cu id=" << parintePtr->id() << "\n";
                persoane.push_back(std::move(parintePtr));
            }
            else if (op == 3) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                } else {
                    for (const auto& p : persoane) {
                        std::cout << *p << "\n";
                    }
                }
            }
            else if (op == 4) {
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
            else if (op == 5) {
                std::cout << "ID persoana: ";
                int id = citesteInt();

                Persoana* gasita = gasestePersoanaMut(persoane, id);
                if (!gasita) {
                    std::cout << "Persoana inexistenta.\n";
                    continue;
                }

                if (auto* copil = dynamic_cast<Copil*>(gasita)) {
                    std::cout << "Varsta noua: ";
                    int v = citesteInt();
                    copil->setVarsta(v);
                    std::cout << *copil << "\n";
                } else if (auto* parinte = dynamic_cast<Parinte*>(gasita)) {
                    std::string tel;
                    std::cout << "Telefon nou: ";
                    std::cin >> tel;
                    parinte->setTelefon(tel);
                    std::cout << *parinte << "\n";
                }
            }
            else if (op == 6) {
                std::cout << "ID parinte: ";
                int idParinte = citesteInt();
                std::cout << "ID copil: ";
                int idCopil = citesteInt();

                auto* pParinte = dynamic_cast<Parinte*>(
                        gasestePersoanaMut(persoane, idParinte));
                const auto* pCopil = dynamic_cast<const Copil*>(
                        gasestePersoanaConst(persoane, idCopil));

                if (!pParinte || !pCopil) {
                    std::cout << "Asociere invalida.\n";
                    continue;
                }

                pParinte->adaugaCopil(idCopil);
                std::cout << "Asociere realizata.\n";
            }
            else if (op == 7) {
                std::cout << "ID parinte: ";
                int idParinte = citesteInt();

                const auto* parinte = dynamic_cast<const Parinte*>(
                        gasestePersoanaConst(persoane, idParinte));
                if (!parinte) {
                    std::cout << "Nu este parinte.\n";
                    continue;
                }

                std::cout << *parinte << "\n";
            }
            else if (op == 8) {
                administrareCopii.sorteazaDupa(
                        [](const Copil& a, const Copil& b) {
                            return a.varsta() < b.varsta();
                        });

                std::cout << "Copii sortati dupa varsta:\n";
                administrareCopii.afiseaza(std::cout);
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
