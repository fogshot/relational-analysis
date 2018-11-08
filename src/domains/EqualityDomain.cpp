//
// Created by vanessa on 11/7/18.
//

#include "EqualityDomain.h"

using namespace basic_relational_abstractions;

//constructor
EqualityDomain::EqualityDomain() {
    forwardMap.clear();
    backwardMap.clear();
}

//function definitions
void EqualityDomain::transform_unknown_assignment(Variable variable) {
//    std::vector<Variable> eqClass;
//    Representative eqRepr;
//
//    eqRepr = backwardMap.find(variable)->second;
//
//    // Remove from backwardMap
//    backwardMap.erase(variable);
//
//    // Remove from forwardMap
//    eqClass = forwardMap.find(eqRepr)->second;
////    eqClass.erase(find(eqClass.begin(), eqClass.end(), variable));
//    if (eqClass.empty()) {
//        forwardMap.erase(eqRepr);
//    }

};

/*
void EqualityDomain::transform_constant_assignment();

void EqualityDomain::transform_variable_assignment();
 */