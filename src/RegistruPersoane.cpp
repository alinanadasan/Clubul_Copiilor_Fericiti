#include "RegistruPersoane.h"

#include <algorithm>
#include <stdexcept>
#include <istream>
#include <ostream>
void RegistruPersoane::adauga(std::unique_ptr<Persoana> p) {
    if (!p) {
        throw std::invalid_argument("RegistruPersoane: pointer null.");
    }
    persoane_.push_back(std::move(p));
}

Persoana& RegistruPersoane::gasesteDupaId(int id) {
    auto it = std::find_if(persoane_.begin(), persoane_.end(),
                           [id](const std::unique_ptr<Persoana>& p) {
                               return p && p->id() == id;
                           });
    if (it == persoane_.end()) {
        throw std::runtime_error("Nu exista persoana cu ID-ul cerut.");
    }
    return *(*it);
}

const Persoana& RegistruPersoane::gasesteDupaId(int id) const {
    auto it = std::find_if(persoane_.begin(), persoane_.end(),
                           [id](const std::unique_ptr<Persoana>& p) {
                               return p && p->id() == id;
                           });
    if (it == persoane_.end()) {
        throw std::runtime_error("Nu exista persoana cu ID-ul cerut.");
    }
    return *(*it);
}

bool RegistruPersoane::stergeDupaId(int id) {
    const auto vechi = persoane_.size();
    persoane_.erase(
        std::remove_if(persoane_.begin(), persoane_.end(),
                       [id](const std::unique_ptr<Persoana>& p) {
                           return p && p->id() == id;
                       }),
        persoane_.end()
    );
    return persoane_.size() != vechi;
}

void RegistruPersoane::sorteazaDupa(
    const std::function<bool(const std::unique_ptr<Persoana>&,
                             const std::unique_ptr<Persoana>&)>& comp) {
    std::sort(persoane_.begin(), persoane_.end(), comp);
}

void RegistruPersoane::afiseaza(std::ostream& out) const {
    for (const auto& p : persoane_) {
        if (p) {
            out << *p << "\n";
        }
    }
}

std::vector<Persoana*> RegistruPersoane::toatePtr() {
    std::vector<Persoana*> v;
    v.reserve(persoane_.size());
    for (auto& p : persoane_) {
        v.push_back(p.get());
    }
    return v;
}

std::vector<const Persoana*> RegistruPersoane::toatePtr() const {
    std::vector<const Persoana*> v;
    v.reserve(persoane_.size());
    for (const auto& p : persoane_) {
        v.push_back(p.get());
    }
    return v;
}
