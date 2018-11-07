//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_ABSTRACTDOMAIN_H
#define LLVM_ABSTRACTDOMAIN_H

#include <memory>

class AbstractDomain {
public:
    /// Joins multiple domains git
    static virtual AbstractDomain leastUpperBounds(AbstractDomain domains[], int size) = 0;

protected:

};


#endif //LLVM_ABSTRACTDOMAIN_H
