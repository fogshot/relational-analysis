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
    enum class ClassType;

    class Constant;

    class Variable : public Representative {
    public:

        friend class EqualityDomain;

        Variable(const std::string &name);

        Variable(const std::string &name, const bool isTemporary);

        bool operator<(const std::shared_ptr<Variable> other) const;

        bool operator==(const std::shared_ptr<Variable> other) const;

        bool operator<(const std::shared_ptr<Constant> other) const;

        bool operator==(const std::shared_ptr<Constant> other) const;

        ClassType getClassType() const override;

        const std::string &getName() const;

        friend std::ostream &operator<<(std::ostream &, const std::shared_ptr<Variable>);

        size_t hash() const override;

        std::string toString() const override;

        int id = 1;

        bool getIsTemporaryVariable() const;

    private:
        std::string name;
        bool isTemporaryVariable;
    };


    /**
     * Helper to compare two variables
     */
    struct VariableComparator {
        bool operator()(const std::shared_ptr<Variable> lVarPtr, const std::shared_ptr<Variable> rVarPtr) const {
            return lVarPtr->getName() < rVarPtr->getName();
        }
    };

}

#endif //LLVM_VARIABLE_H
