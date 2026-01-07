#include <iostream>
#include <vector>
#include <memory>
#include <limits>

#include "Copil.h"

int citesteInt() {
    int x;
    while (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Input invalid. Mai incearca: ";
    }
    return x;
}

int main() {
    std::vector<std::unique_ptr<Persoana>> persoane;

    while (true) {
        std::cout << "\n===== MENIU =====\n";
        std::cout << "1) Adauga copil\n";
        std::cout << "2) Afiseaza toate persoanele\n";
        std::cout << "3) Modifica nume/email (dupa id)\n";
        std::cout << "4) Afiseaza varsta copil (dupa id)\n";
        std::cout << "0) Iesire\n";
        std::cout << "Optiune: ";

        int op = citesteInt();

        try {
            if (op == 0) {
                std::cout << "La revedere!\n";
                break;
            }

            if (op == 1) {
                std::string nume, email;
                int varsta;

                std::cout << "Nume (fara spatii): ";
                std::cin >> nume;
                std::cout << "Email: ";
                std::cin >> email;
                std::cout << "Varsta: ";
                varsta = citesteInt();

                auto c = std::make_unique<Copil>(nume, email, varsta);

                std::cout << "Adaugat copil cu id=" << c->id() << "\n";

                persoane.push_back(std::move(c));
            }
            else if (op == 2) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                } else {
                    for (const auto& p : persoane) {
                        // foloseste tip(), afiseaza(), operator<<
                        std::cout << *p << "\n";

                        std::cout << "  (debug) nume=" << p->nume()
                                  << ", email=" << p->email() << "\n";
                    }
                }
            }
            else if (op == 3) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                    continue;
                }

                std::cout << "ID persoana: ";
                int id = citesteInt();

                Persoana* gasita = nullptr;
                for (auto& p : persoane) {
                    if (p->id() == id) {
                        gasita = p.get();
                        break;
                    }
                }

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
            else if (op == 4) {
                if (persoane.empty()) {
                    std::cout << "Nu exista persoane.\n";
                    continue;
                }

                std::cout << "ID copil: ";
                int id = citesteInt();

                Persoana* gasita = nullptr;
                for (auto& p : persoane) {
                    if (p->id() == id) {
                        gasita = p.get();
                        break;
                    }
                }

                if (!gasita) {
                    std::cout << "Nu exista persoana cu id=" << id << "\n";
                    continue;
                }

                // downcast
                const Copil* copil = dynamic_cast<const Copil*>(gasita);
                if (!copil) {
                    std::cout << "Persoana cu id=" << id << " nu este copil.\n";
                    continue;
                }

                std::cout << "Varsta copilului " << copil->nume()
                          << " este " << copil->varsta() << "\n";
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

/////////////////////////////////////////////////////////////////////////
/// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
/// dați exemple de date de intrare folosind fișierul tastatura.txt
/// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
/// (în formatul impus de voi) astfel încât execuția programului să se încheie.
/// De asemenea, trebuie să adăugați în acest fișier date de intrare
/// pentru cât mai multe ramuri de execuție.
/// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
/// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
///
/// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
/// pentru a simula date introduse de la tastatură.
/// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
///
/// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
/// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
/// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
/// program care merg (și să le evitați pe cele care nu merg).
///
/////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
