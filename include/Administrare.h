//
// Created by Alina on 03/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_ADMINISTRARE_H
#define CLUBUL_COPIILOR_FERICITI_ADMINISTRARE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <ostream>
#include <utility>

// Administrare<T> = colectie de elemente T.
// Ex: Administrare<Copil>, Administrare<Parinte>, Administrare<Plata> etc.
template<typename T>
class Administrare {
private:
    std::vector<T> elemente_;

public:
    Administrare() = default;

    const std::vector<T>& toate() const noexcept { return elemente_; }
    bool esteGoala() const noexcept { return elemente_.empty(); }
    std::size_t marime() const noexcept { return elemente_.size(); }

    void adauga(const T& elem) { elemente_.push_back(elem); }
    void adauga(T&& elem) { elemente_.push_back(std::move(elem)); }

    std::size_t stergeDaca(const std::function<bool(const T&)>& pred) {
        const auto vechi = elemente_.size();
        elemente_.erase(
            std::remove_if(elemente_.begin(), elemente_.end(), pred),
            elemente_.end()
        );
        return vechi - elemente_.size();
    }

    T& primulDupa(const std::function<bool(const T&)>& pred) {
        auto it = std::find_if(elemente_.begin(), elemente_.end(), pred);
        if (it == elemente_.end()) {
            throw std::runtime_error("Administrare: element inexistent.");
        }
        return *it;
    }

    const T& primulDupa(const std::function<bool(const T&)>& pred) const {
        auto it = std::find_if(elemente_.begin(), elemente_.end(), pred);
        if (it == elemente_.end()) {
            throw std::runtime_error("Administrare: element inexistent.");
        }
        return *it;
    }

    void sorteazaDupa(const std::function<bool(const T&, const T&)>& comp) {
        std::sort(elemente_.begin(), elemente_.end(), comp);
    }

    void afiseaza(std::ostream& out) const {
        for (const auto& e : elemente_) {
            out << e << "\n";
        }
    }
};

#endif //CLUBUL_COPIILOR_FERICITI_ADMINISTRARE_H