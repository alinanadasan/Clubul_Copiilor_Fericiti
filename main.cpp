#include <iostream>
#include <array>
#include <memory>
#include "Copil.h"

    int main() {
        try {
            // cream un copil normal
            Copil c1("Ana", "ana@email.com", 10);

            // afisare directa
            std::cout << c1 << '\n';

            // polimorfism: upcast Copil -> Persoana
            std::unique_ptr<Persoana> p = std::make_unique<Copil>(
                "Mihai", "mihai@email.com", 12
            );

            // afisare prin pointer la baza
            std::cout << *p << '\n';

            // test de exceptie (varsta invalida)
            Copil c2("Ion", "ion@email.com", 25);
            std::cout << c2 << '\n';
        }
        catch (const std::exception& e) {
            std::cout << "Eroare: " << e.what() << '\n';
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
