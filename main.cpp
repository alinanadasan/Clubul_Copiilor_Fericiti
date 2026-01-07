#include <iostream>
#include <vector>
#include <memory>
#include <limits>

#include "Copil.h"
#include "Parinte.h"

int citesteInt() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input invalid. Mai incearca: ";
    }
    return x;
}

const Persoana* gasestePersoanaConst(const std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
    for (const auto& p : persoane) {
        if (p->id() == id) return p.get();
    }
    return nullptr;
}

Persoana* gasestePersoanaMut(std::vector<std::unique_ptr<Persoana>>& persoane, int id) {
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
    std::cout << "5) Modifica varsta copil / telefon parinte (dupa id)\n";
    std::cout << "6) Asociaza copil la parinte (parinteId, copilId)\n";
    std::cout << "7) Afiseaza copiii unui parinte (dupa id)\n";
    std::cout << "0) Iesire\n";
    std::cout << "Optiune: ";
}

int main() {
    std::vector<std::unique_ptr<Persoana>> persoane;

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

                std::cout << "Nume copil (fara spatii): ";
                std::cin >> nume;
                std::cout << "Email copil: ";
                std::cin >> email;
                std::cout << "Varsta copil: ";
                varsta = citesteInt();

                auto c = std::make_unique<Copil>(nume, email, varsta);
                std::cout << "Adaugat copil cu id=" << c->id() << "\n";

                persoane.push_back(std::move(c));
            }
            else if (op == 2) {
                std::string nume, email, telefon;

                std::cout << "Nume parinte (fara spatii): ";
                std::cin >> nume;
                std::cout << "Email parinte: ";
                std::cin >> email;
                std::cout << "Telefon parinte: ";
                std::cin >> telefon;

                auto p = std::make_unique<Parinte>(nume, email, telefon);
                std::cout << "Adaugat parinte cu id=" << p->id() << "\n";

                persoane.push_back(std::move(p));
            }
            else if (op == 3) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                } else {
                    for (const auto& p : persoane) {
                        std::cout << *p << "\n";

                        std::cout << "  (info) id=" << p->id()
                                  << ", nume=" << p->nume()
                                  << ", email=" << p->email() << "\n";
                    }
                }
            }
            else if (op == 4) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                    continue;
                }

                std::cout << "ID persoana: ";
                int id = citesteInt();

                Persoana* gasita = gasestePersoanaMut(persoane, id);
                if (!gasita) {
                    std::cout << "Nu exista persoana cu id=" << id << "\n";
                    continue;
                }

                std::string numeNou, emailNou;
                std::cout << "Nume nou (fara spatii): ";
                std::cin >> numeNou;
                std::cout << "Email nou: ";
                std::cin >> emailNou;

                gasita->setNume(numeNou);
                gasita->setEmail(emailNou);

                std::cout << "Actualizat: " << *gasita << "\n";
            }
            else if (op == 5) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                    continue;
                }

                std::cout << "ID persoana: ";
                int id = citesteInt();

                Persoana* gasita = gasestePersoanaMut(persoane, id);
                if (!gasita) {
                    std::cout << "Nu exista persoana cu id=" << id << "\n";
                    continue;
                }

                if (auto* copil = dynamic_cast<Copil*>(gasita)) {
                    std::cout << "Varsta noua pentru copil: ";
                    int v = citesteInt();
                    copil->setVarsta(v);
                    std::cout << "Actualizat: " << *copil << "\n";
                } else if (auto* parinte = dynamic_cast<Parinte*>(gasita)) {
                    std::string tel;
                    std::cout << "Telefon nou pentru parinte: ";
                    std::cin >> tel;
                    parinte->setTelefon(tel);
                    std::cout << "Actualizat: " << *parinte << "\n";
                } else {
                    std::cout << "Tip de persoana necunoscut (nu ar trebui sa se intample).\n";
                }
            }
            else if (op == 6) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                    continue;
                }

                std::cout << "ID parinte: ";
                int parinteId = citesteInt();
                std::cout << "ID copil: ";
                int copilId = citesteInt();

                // parinte mutabil (il modificam: adaugam copilId)
                Persoana* pParinte = gasestePersoanaMut(persoane, parinteId);
                if (!pParinte) {
                    std::cout << "Nu exista persoana cu id=" << parinteId << "\n";
                    continue;
                }

                auto* parinte = dynamic_cast<Parinte*>(pParinte);
                if (!parinte) {
                    std::cout << "Persoana cu id=" << parinteId << " nu este parinte.\n";
                    continue;
                }

                // copilul doar il verificam ca exista si e copil
                const Persoana* pCopil = gasestePersoanaConst(persoane, copilId);
                if (!pCopil) {
                    std::cout << "Nu exista persoana cu id=" << copilId << "\n";
                    continue;
                }

                const auto* copil = dynamic_cast<const Copil*>(pCopil);
                if (!copil) {
                    std::cout << "Persoana cu id=" << copilId << " nu este copil.\n";
                    continue;
                }

                parinte->adaugaCopil(copilId);
                std::cout << "Asociere facuta: parinte " << parinte->nume()
                          << " -> copil " << copil->nume() << "\n";
            }
            else if (op == 7) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                    continue;
                }

                std::cout << "ID parinte: ";
                int parinteId = citesteInt();

                const Persoana* pParinte = gasestePersoanaConst(persoane, parinteId);
                if (!pParinte) {
                    std::cout << "Nu exista persoana cu id=" << parinteId << "\n";
                    continue;
                }

                const auto* parinte = dynamic_cast<const Parinte*>(pParinte);
                if (!parinte) {
                    std::cout << "Persoana cu id=" << parinteId << " nu este parinte.\n";
                    continue;
                }

                std::cout << "Parinte: " << parinte->nume()
                          << " (telefon=" << parinte->telefon() << ")\n";

                const auto& ids = parinte->copiiIds();
                if (ids.empty()) {
                    std::cout << "Nu are copii asociati.\n";
                    continue;
                }

                std::cout << "Copii asociati:\n";
                for (int idCopil : ids) {
                    const Persoana* pCopil = gasestePersoanaConst(persoane, idCopil);
                    if (!pCopil) {
                        std::cout << " - copilId=" << idCopil << " (nu mai exista in lista)\n";
                        continue;
                    }

                    const auto* copil = dynamic_cast<const Copil*>(pCopil);
                    if (!copil) {
                        std::cout << " - copilId=" << idCopil << " (nu este copil)\n";
                        continue;
                    }

                    std::cout << " - " << copil->nume() << ", varsta=" << copil->varsta()
                              << ", id=" << copil->id() << "\n";
                }
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
