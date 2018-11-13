//
// Created by Dominik Horn on 07.11.18.
//

#ifndef LLVM_STATE_H
#define LLVM_STATE_H

#include <vector>
#include "AbstractDomain.h"

namespace bra {

    class State {
    public:
        State(int visits, std::vector<std::shared_ptr<AbstractDomain>> domains);
        std::vector<std::shared_ptr<AbstractDomain>> getDomains() const;
        int getVisits() const;
        friend std::ostream& operator <<(std::ostream& outputStream, const State& state);

    protected:
        /// How often this basic block has been visited
        int visits;

        /// The abstract domains stored in this state
        std::vector<std::shared_ptr<AbstractDomain>> domains;
    };
}

#endif //LLVM_STATE_H
