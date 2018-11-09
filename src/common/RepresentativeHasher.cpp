//
// Created by Dominik Horn on 09.11.18.
//

#include <string>
#include "RepresentativeHasher.h"
#include "../util.h"

using namespace std;

size_t hash<bra::Representative>::operator()(const bra::Representative &) const {
    // should never be called!!
    DEBUG_ERR("Representative can not be hashed!");
    return 0;
}

size_t hash<bra::Variable>::operator()(const bra::Variable &var) const {
    return hash<string>()(var.getName());
}

size_t hash<bra::Constant>::operator()(const bra::Constant &constant) const {
    return hash<int>()(constant.getValue());
}