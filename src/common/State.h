#ifndef LLVM_STATE_H
#define LLVM_STATE_H

#include <vector>
#include <iostream>
#include <string>
#include "AbstractDomain.h"

namespace bra {

    class State {
    public:
        /// Standard constructor
        //TODO: use unique_ptr for domains
        State(std::vector<std::shared_ptr<AbstractDomain>>);

        /// Obtain all domains of this state
        //TODO: use unique_ptr for domains
        std::vector<std::shared_ptr<AbstractDomain>> getDomains() const;

        /// Obtain amount of BB visits (debug)
        int getVisits() const;

        /// Increments the visited count
        void willVisit();

        /// Update lastModified
        void setUpdated();

        /// Whether or not it was updated
        bool wasUpdatedOnLastVisit();

        /// Helper to print current state to stream (f.e. for output)
        friend std::ostream &operator<<(std::ostream &outputStream, const State &state);

        // TODO: add toString()
    protected:
        /// How often this basic block has been visited (debug)
        int visits;

        /// When the State was last modified
        int lastModified;

        /// The abstract domains stored in this state
        //TODO: use unique_ptr for domains
        std::vector<std::shared_ptr<AbstractDomain>> domains;
    };
}

#endif //LLVM_STATE_H
