//
// Created by Dominik Horn on 07.11.18.
//

#include "State.h"
#include <iostream>

std::vector<std::shared_ptr<bra::AbstractDomain>> bra::State::getDomains() const {
    return *domains;
}

int bra::State::getVisits() const {
    return visits;
}

void bra::State::addDomain(std::shared_ptr<AbstractDomain> dom) {
    domains->insert(domains->end(), dom);
}

std::ostream &bra::operator<<(std::ostream &outputStream, const bra::State &state) {
    outputStream << "State(visits: " << state.visits << ", domains: {";
    for (const auto &domain : *state.domains) {
        outputStream << domain << ", ";
    }
    outputStream << "})";
    return outputStream;
}

bra::State::State() : visits(0), domains(new std::vector<std::shared_ptr<AbstractDomain>>()) {};

bra::State::~State() {
    delete domains;
}
