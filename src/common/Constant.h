//===----------------------------------------------------------------------===//
//
// Implementation of lib/Analysis/RelationalAnalysis/src/common/Representative.h
// A constant has a specific int value
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_CONSTANT_H
#define LLVM_CONSTANT_H

#include <functional>
#include <memory>
#include "Representative.h"

namespace bra {

    enum class ClassType;
    class Variable;

    class Constant : public Representative {
    public:
        Constant(int value);

        ~Constant() {};

        bool operator<(const std::shared_ptr<Constant> other) const;

        bool operator==(const std::shared_ptr<Constant> other) const;

        bool operator<(const std::shared_ptr<Variable> other) const;

        bool operator==(const std::shared_ptr<Variable> other) const;

        int getValue() const;

        ClassType getClassType() const override;

        size_t hash() const override;

        friend std::ostream &operator<<(std::ostream &, const std::shared_ptr<Constant>);

        std::string toString() const override;

        int id = 2;



    private:
        int value;
    };

}

#endif //LLVM_CONSTANT_H
