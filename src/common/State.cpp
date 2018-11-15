#include "State.h"
#include <vector>
#include <iostream>
#include <string>

namespace bra {

    State::State(std::vector<std::shared_ptr<AbstractDomain>> domains)
            : visits(0),
              domains(domains) {
    }

    std::vector<std::shared_ptr<AbstractDomain>> State::getDomains() const {
        return domains;
    }

    int State::getVisits() const {
        return visits;
    }

    void State::wasVisited() {
        visits++;
    }

    std::ostream &operator<<(std::ostream &outputStream, const State &state) {
        outputStream << "State(visits: " << state.visits << ", domains: {";
        for (const auto &domain : state.domains) {
            outputStream << domain << ", ";
        }
        outputStream << "})";
        return outputStream;
    }


}