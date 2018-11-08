//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_VARIABLE_H
#define LLVM_VARIABLE_H

#include <string>
#include "Representative.h"

namespace basic_relational_abstractions {

    class Variable : public Representative {
    public:
        Variable(const std::string& name);

        bool operator<(const Variable& other) const {
            return name < other.name;
        }

        bool operator==(const Variable& other) const {
            return name == other.name;
        }

    private:
        std::string name;
    };

}

#endif //LLVM_VARIABLE_H
