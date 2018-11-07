//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_ABSTRACTDOMAIN_H
#define LLVM_ABSTRACTDOMAIN_H

#include <memory>

class AbstractDomain {
public:
    /// Constructor returns an empty domain, i.e. one representing all Invariants
    AbstractDomain() {}

    /// Joins multiple domains by means of calculating the leastUpperBounds. Returns a new AbstractDomain representing the result
    static virtual AbstractDomain leastUpperBounds(AbstractDomain domains[], int size) = 0;
};


#endif //LLVM_ABSTRACTDOMAIN_H
