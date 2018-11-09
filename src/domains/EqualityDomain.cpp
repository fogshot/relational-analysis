//
// Created by vanessa on 11/7/18.
//

#include <algorithm>
#include <utility>
#include "EqualityDomain.h"

using namespace bra;

//constructor
EqualityDomain::EqualityDomain() {}

//function definitions
void EqualityDomain::transform_unknown_assignment(Variable variable) {
    std::unordered_set<Variable> eqClass;
    Representative eqRepr;

    eqRepr = backwardMap.find(variable)->second;

    // Remove from backwardMap
    backwardMap.erase(variable);

    // Remove from forwardMap
    eqClass = forwardMap.find(eqRepr)->second;
    eqClass.erase(std::find(eqClass.begin(), eqClass.end(), variable));
    if (eqClass.empty()) {
        forwardMap.erase(eqRepr);
    } else if (eqRepr == variable){
        Representative var = *eqClass.begin();
        forwardMap.erase(eqRepr);
        forwardMap.insert(std::make_pair<Representative,std::unordered_set<Variable>>(&var, eqClass));
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

