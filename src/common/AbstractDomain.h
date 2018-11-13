//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_ABSTRACTDOMAIN_H
#define LLVM_ABSTRACTDOMAIN_H

#include <vector>
#include <memory>

namespace bra {
    class AbstractDomain {
    public:
        /// Joins multiple domains by means of calculating the leastUpperBounds.
        /// Returns a new AbstractDomain representing the result
        ///
        /// this should never be called directly, instead the subclasses should implement this
        virtual std::string toString() = 0;
        virtual std::shared_ptr<AbstractDomain> leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) = 0;
        virtual ~AbstractDomain() = 0;
        virtual void add() = 0;
        virtual void move() = 0;
        virtual std::shared_ptr<AbstractDomain> bottom() = 0;
    };
}

#endif //LLVM_ABSTRACTDOMAIN_H
