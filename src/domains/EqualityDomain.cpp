//
// Created by vanessa on 11/7/18.
//

#include <algorithm>
#include <utility>
#include "EqualityDomain.h"

using namespace bra;
namespace bra {

    //function definitions
    void EqualityDomain::transform_unknown_assignment(Variable variable) {
        std::unordered_set<Variable> eqClass;
        Representative eqRepr;

        // Remove from forwardMap
        eqClass = forwardMap.find(eqRepr)->second;
        eqClass.erase(std::find(eqClass.begin(), eqClass.end(), variable));
        if (eqClass.empty()) {
            forwardMap.erase(eqRepr);
        }
    };

    void EqualityDomain::transform_constant_assignment(Variable variable, Constant constant) {
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
}

