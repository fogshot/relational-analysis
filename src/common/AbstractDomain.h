//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_ABSTRACTDOMAIN_H
#define LLVM_ABSTRACTDOMAIN_H

#include <vector>

namespace bra {

    class AbstractDomain {
    public:
        /// Constructor returns an empty domain, i.e. one representing all Invariants
        template<typename Domain>
        static Domain emptyDomain() { return new Domain; };

        /// Joins multiple domains by means of calculating the leastUpperBounds. Returns a new AbstractDomain representing the result
        static AbstractDomain leastUpperBounds(std::vector<AbstractDomain> domains);
    };

}

#endif //LLVM_ABSTRACTDOMAIN_H
