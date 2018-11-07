//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_STATE_H
#define LLVM_STATE_H

#include <vector>
#include "AbstractDomain.h"

namespace basic_relational_abstractions {

    class State {
    protected:
        /// How often this basic block has been visited
        int visits;

        /// The abstract domains stored in this state
        std::vector<AbstractDomain> domains;
    };

}

#endif //LLVM_STATE_H
