//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_VARIABLE_H
#define LLVM_VARIABLE_H

#include <string>
#include "Representative.h"

namespace bra {
    class Constant;

    class Variable : public Representative {
    public:
        Variable(const std::string& name);

        bool operator<(const Variable& other) const;

        bool operator==(const Variable& other) const;

        bool operator<(const Constant& other) const;

        bool operator==(const Constant& other) const;

    private:
        std::string name;
    };

}

#endif //LLVM_VARIABLE_H
