//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_VARIABLE_H
#define LLVM_VARIABLE_H

#include <functional>
#include <string>
#include "Representative.h"

namespace bra {
    class Constant;

    class Variable : public Representative {
    public:
        Variable(const std::string &name);

        bool operator<(const Variable &other) const;

        bool operator==(const Variable &other) const;

        bool operator<(const Constant &other) const;

        bool operator==(const Constant &other) const;

        const std::string &getName() const;

        friend std::ostream &operator<<(std::ostream &, const Variable &);
        friend std::ostream &operator<<(std::ostream &, const std::shared_ptr<Variable> &);

        size_t hash() const override;

        std::string toString() const override;

        int id = 1;

    private:
        std::string name;
    };

}

#endif //LLVM_VARIABLE_H
