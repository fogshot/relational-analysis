#include "State.h"
#include <vector>
#include <iostream>
#include <string>

namespace bra {

    State::State(std::vector<std::shared_ptr<AbstractDomain>> domains)
            : visits(0),
              lastModified(-1),
              domains(domains) {}

    std::vector<std::shared_ptr<AbstractDomain>> State::getDomains() const {
        return domains;
    }

    int State::getVisits() const {
        return visits;
    }

    void State::willVisit() {
        DEBUG_OUTPUT("State::wilVisit()");
        visits++;
    }

    void State::setUpdated() {
        DEBUG_OUTPUT("State::setUpdated()");
        lastModified = visits;
    }

    bool State::wasUpdatedOnLastVisit() {
        DEBUG_OUTPUT("State::wasUpdate()");
        return lastModified == visits;
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