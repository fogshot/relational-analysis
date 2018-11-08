//
// Created by vanessa on 11/7/18.
//

#include "EqualityDomain.h"
#include <algorithm>

using namespace basic_relational_abstractions;

//constructor
EqualityDomain::EqualityDomain() {
    forwardMap.clear();
    backwardMap.clear();
}

//function definitions
void EqualityDomain::transform_unknown_assignment(Variable variable) {
    std::vector<Variable> eqClass;
    Representative eqRepr;

    eqRepr = backwardMap.find(variable)->second;

    // Remove from backwardMap
    backwardMap.erase(variable);

    // Remove from forwardMap
    eqClass = forwardMap.find(eqRepr)->second;
    eqClass.erase(std::find(eqClass.begin(), eqClass.end(), variable));
    if (eqClass.empty()) {
        forwardMap.erase(eqRepr);
    }
};

void EqualityDomain::transform_constant_assignment(Variable variable, Constant constant){
    //backwardMap: if key exists -> overwrite value, else add new pair
    //auto it = forwardMap.find(variable);
    //if(it != forwardMap.end()){
    //    if(it->second != constant){

    //    }
    //}
    //forwardMap: search for key, add variable to value set, if not existing add new pair

}

void EqualityDomain::transform_variable_assignment(Variable variable, Variable assigned_value){

}
