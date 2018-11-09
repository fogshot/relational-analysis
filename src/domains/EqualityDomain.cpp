//
// Created by vanessa on 11/7/18.
//

#include "EqualityDomain.h"
#include <algorithm>

using namespace bra;
namespace bra {

    //constructor
    EqualityDomain::EqualityDomain() {
        forwardMap.clear();
        backwardMap.clear();
    }

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

    void EqualityDomain::transform_constant_assignment(Variable variable, Constant constant) {
        //backwardMap: if key exists -> overwrite value, else add new pair
        //auto it = forwardMap.find(variable);
        //if(it != forwardMap.end()){
        //    if(it->second != constant){

        //    }
        //}
        //forwardMap: search for key, add variable to value set, if not existing add new pair

    }

    void EqualityDomain::transform_variable_assignment(Variable variable, Variable assigned_value) {

    }

    void EqualityDomain::add() {

    }

    void EqualityDomain::move() {

    }

    std::shared_ptr<AbstractDomain> EqualityDomain::bottom() {
        return std::shared_ptr<EqualityDomain>();
    }

    std::shared_ptr<AbstractDomain>
    EqualityDomain::leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) {
        // TODO implement for real
        return std::shared_ptr<EqualityDomain>();
    }

    EqualityDomain::~EqualityDomain() = default;
}

