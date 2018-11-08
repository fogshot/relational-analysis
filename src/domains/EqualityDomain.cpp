//
// Created by vanessa on 11/7/18.
//

#include "EqualityDomain.h"

using namespace basic_relational_abstractions;

//constructor
EqualityDomain::EqualityDomain(){

    forwardMap.clear();
    backwardMap.clear();
}

//function definitions
void EqualityDomain::transform_unknown_assignment(Variable variable) {

    //Representative key_back = backwardMap.find(variable)->second;

    //remove from backwardMap
    //backwardMap.erase(variable);
    //remove from forwardMap
    //std::vector<Variable> set = forwardMap.find(key_back)->second;
    //set.erase(variable);
    //if (set.empty()) {
    //    forwardMap.erase(key_back);
    //}

};

void EqualityDomain::transform_constant_assignment();

void EqualityDomain::transform_variable_assignment();