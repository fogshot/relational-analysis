//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_VARIABLE_H
#define LLVM_VARIABLE_H

#include<string>

namespace basic_relational_abstractions {

    class Variable {
    public:
        Variable(const std::string &name);

    private:
        std::string name;
    };

}

#endif //LLVM_VARIABLE_H
