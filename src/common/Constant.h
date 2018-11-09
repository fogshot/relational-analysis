//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
// A constant has a specific int value
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_CONSTANT_H
#define LLVM_CONSTANT_H

#include "Representative.h"

namespace bra {
    class Variable;

    class Constant : public Representative {
    public:
        Constant(int value);

        bool operator<(const Constant& other) const;

        bool operator==(const Constant& other) const;

        bool operator<(const Variable& other) const;

        bool operator==(const Variable& other) const;

    private:
        int value;
    };

}

#endif //LLVM_CONSTANT_H
