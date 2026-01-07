#ifndef CLUBUL_COPIILOR_FERICITI_REGISTRUPERSOANE_H
#define CLUBUL_COPIILOR_FERICITI_REGISTRUPERSOANE_H

#include <memory>
#include <vector>
#include <functional>
#include <iosfwd>

#include "Persoana.h"

class RegistruPersoane {
private:
    std::vector<std::unique_ptr<Persoana>> persoane_;

public:
    RegistruPersoane() = default;

    bool esteGol() const noexcept { return persoane_.empty(); }
    std::size_t marime() const noexcept { return persoane_.size(); }

    void adauga(std::unique_ptr<Persoana> p);

    Persoana& gasesteDupaId(int id);
    const Persoana& gasesteDupaId(int id) const;

    bool stergeDupaId(int id);

    void sorteazaDupa(const std::function<bool(const std::unique_ptr<Persoana>&,
                                               const std::unique_ptr<Persoana>&)>& comp);

    void afiseaza(std::ostream& out) const;

    // util pt. meniu: listă de pointeri raw (fără ownership)
    std::vector<Persoana*> toatePtr();
    std::vector<const Persoana*> toatePtr() const;
};

#endif
