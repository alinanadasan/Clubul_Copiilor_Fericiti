//
// Created by Alina on 07/01/2026.
//

#ifndef CLUBUL_COPIILOR_FERICITI_STRATEGIESORTARE_H
#define CLUBUL_COPIILOR_FERICITI_STRATEGIESORTARE_H

template <typename T>
class StrategieSortare {
public:
    virtual bool compara(const T& a, const T& b) const = 0;
    virtual ~StrategieSortare() = default;
};

#endif //CLUBUL_COPIILOR_FERICITI_STRATEGIESORTARE_H