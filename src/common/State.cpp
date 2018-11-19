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

    void State::updateDomain(std::shared_ptr<AbstractDomain> updatedDomain) {
        for (auto domIt = domains.begin(); domIt != domains.end(); domIt++) {
            if (domIt->get()->getClassType() == updatedDomain->getClassType()) {
                // Check if something changed TODO: implement proper comparison on domains!!! (I am aware this is ugly)
                if (domIt->get()->toString() != updatedDomain->toString()) {
//                    DEBUG_OUTPUT(std::string(RED)
//                                         +domIt->get()->toString()
//                                         + "\n!=\n"
//                                         + updatedDomain->toString()
//                                         + std::string(NO_COLOR));
                    // Set updated
                    lastModified = visits;
                }
                domains.erase(domIt);
                domains.push_back(updatedDomain);
                return;
            }
        }
    }

    int State::getVisits() const {
        return visits;
    }

    void State::willVisit() {
        visits++;
    }

    bool State::wasUpdatedOnLastVisit() {
        return lastModified == visits;
    }

    std::ostream &operator<<(std::ostream &outputStream, const State &state) {
        return outputStream << state.toString();
    }


    std::string State::toString() const {
        std::string result = "State(visits: " + std::to_string(visits) + ", domains: {";
        for (auto domIt = domains.begin(); domIt != domains.end(); domIt++) {
            result += domIt->get()->toString();
            if (std::next(domIt) != domains.end()) {
                result += ", ";
            }
        }
        result += "})";
        return result;
    }

}