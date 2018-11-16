//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_ABSTRACTDOMAIN_H
#define LLVM_ABSTRACTDOMAIN_H

#include <vector>
#include <memory>
#include <string>
#include "Variable.h"

namespace bra {
    class AbstractDomain {
    public:
        /// Joins multiple domains by means of calculating the leastUpperBounds.
        /// Returns a new AbstractDomain representing the result
        ///
        /// this should never be called directly, instead the subclasses should implement this
        virtual std::string toString() const = 0;

        virtual std::shared_ptr<AbstractDomain> leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) = 0;

        virtual ~AbstractDomain() = 0;

        virtual std::shared_ptr<AbstractDomain> bottom() = 0;

        /// Interactions with visiting instructions go here. Return value indicates whether or not domain has been modified
        virtual bool transform_add(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1,
                                   std::shared_ptr<Representative> arg2) = 0;

        virtual bool transform_store(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) = 0;

        virtual bool transform_load(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) = 0;
    };
}

#endif //LLVM_ABSTRACTDOMAIN_H
