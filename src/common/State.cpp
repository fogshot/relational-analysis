//
// Created by Dominik Horn on 07.11.18.
//

#include "State.h"

std::vector<std::shared_ptr<bra::AbstractDomain>> bra::State::getDomains() const {
    return domains;
}

bra::State::State(int visits,
        std::vector<std::shared_ptr<bra::AbstractDomain>> domains) : visits(visits), domains(std::move(domains)) {}
