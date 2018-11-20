//===----------------------------------------------------------------------===//
//
// This class defines the representative of an entry in the domain map.
// Possible subclasses: constant, variable
//
//===----------------------------------------------------------------------===//
#ifndef LLVM_REPRESENTATIVE_H
#define LLVM_REPRESENTATIVE_H

#include <functional>
#include <iostream>
#include <stddef.h>
#include <string>
#include <memory>

namespace bra {

    enum class ClassType;

    class Variable;
    class Constant;

    class Representative {
    public:
        Representative();

        virtual ~Representative() {};

        virtual size_t hash() const = 0;

        virtual std::string toString() const = 0;

        virtual std::string toDotString() const = 0;

        virtual ClassType getClassType() const = 0;

        friend std::ostream &operator<<(std::ostream &, const std::shared_ptr<Representative>);
    };

    //inline bool operator<(const Representative&, const Representative&);
}


#endif //LLVM_REPRESENTATIVE_H
