//
// Created by Dominik Horn on 09.11.18.
//

#ifndef LLVM_REPRESENTATIVEHASHER_H
#define LLVM_REPRESENTATIVEHASHER_H

#include <functional>
#include "Representative.h"
#include "Variable.h"
#include "Constant.h"

namespace std {

    template<>
    struct hash<bra::Representative> {
        size_t operator()(const bra::Representative &) const;
    };

    template<>
    struct hash<bra::Variable> {
        size_t operator()(const bra::Variable &) const;
    };

    template<>
    struct hash<bra::Constant> {
        size_t operator()(const bra::Constant &) const;
    };
}


#endif //LLVM_REPRESENTATIVEHASHER_H
