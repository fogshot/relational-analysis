//
// Created by vanessa on 11/7/18.
//

#include <algorithm>
#include <utility>
#include <string>
#include <memory>
#include <iostream>
#include <src/common/ClassType.h>
#include "EqualityDomain.h"
#include "../util.h"

namespace bra {
    //constructor and Destructor
    EqualityDomain::EqualityDomain() {}
    EqualityDomain::~EqualityDomain() {}

    //function definitions
    void EqualityDomain::transformUnkownAssignment(const std::shared_ptr<Variable> variable) {
        // Do nothing (Single static assignment)
    }

    void EqualityDomain::transformConstantAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Constant> constant) {
        this->addVariableToEquivalenceClass(constant, variable);
    }

    void EqualityDomain::transformVariableAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Variable> assignedValue) {
        // TODO:

    }

    void EqualityDomain::addVariableToEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                       const std::shared_ptr<Variable> var) {
        auto itForward = forwardMap.find(eqRepr); //iterator for forwardMap
        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass; //shared_ptr on set (=equality class)
        if (itForward != forwardMap.end()) { //go through forwardMap if not empty
            eqClass = itForward->second; //get eq class
            eqClass->insert(var); // add variable to eq class

            //if eqRepr is a Variable -> choose "smallest" (= first in the set) as new key
            if (eqRepr->getClassType() == ClassType::Variable){
                auto firstVarInSet = eqClass->begin();
                if (eqRepr<*firstVarInSet){
                    forwardMap.erase(itForward);//delete current pair
                    forwardMap.insert({*firstVarInSet, eqClass});//new pair with smallest variable as key
                }
            }

        } else { //eq class is empty
            eqClass = std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>>(
                    new std::set<std::shared_ptr<Variable>, Compare>()); //create new set
            eqClass->insert(var); //insert variable to set
            forwardMap.insert({eqRepr, eqClass}); //insert tuple to map
        }

        auto itBackward = backwardMap.find(var);
        if (itBackward != backwardMap.end()) { //variable is already in map -> overwrite value
            itBackward->second = eqRepr;
        } else { //otherwise add new pair
            backwardMap.insert({var, eqRepr});
        }
    }

    void EqualityDomain::removeVariableFromEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                            const std::shared_ptr<Variable> variable) {
        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass = forwardMap.find(eqRepr)->second;
        eqClass->erase(std::find(eqClass->begin(), eqClass->end(), variable));
        if (eqClass->empty()) {
            forwardMap.erase(eqRepr);
        } else if (eqRepr == variable) {
            const std::shared_ptr<Variable> &repr = eqClass->begin().operator*();
            forwardMap.erase(eqRepr);
            forwardMap.insert({repr, eqClass});
            for (const std::shared_ptr<Variable> &eqMember : *eqClass) {
                auto it = backwardMap.find(eqMember);
                if (it != backwardMap.end()) {
                    // TODO:
                    it->second = repr;
                } else {
                    backwardMap.insert({eqMember, repr});
                }
            }
        }
    }

    std::ostream &operator<<(std::ostream &stream, const EqualityDomain &dom) {
        stream << dom.toString();
        return stream;
    }

    std::string EqualityDomain::toString() const {
        std::string ret = "EqualityDomain (\n\tforwardMap {";
        for (auto tmp = this->forwardMap.begin(); tmp != this->forwardMap.end(); tmp++) {
            ret += "(" + (tmp->first->toString()) + ": {";

            for (auto var = tmp->second->begin(); var != tmp->second->end(); var++) {
                ret += (*var)->toString();

                if (std::next(var) != tmp->second->end()) {
                    ret += ", ";
                }
            }

            ret += "})";
            if (std::next(tmp) != this->forwardMap.end()) {
                ret += ", ";
            }
        }

        // New line for backward map
        ret += "}\n  -> backwardMap {";
        for (auto pairIt = this->backwardMap.begin(); pairIt != this->backwardMap.end(); pairIt++) {
            ret += "(" + pairIt->first->toString() + ", " + pairIt->second->toString() + ")";

            if (std::next(pairIt) != this->backwardMap.end()) {
                ret += ", ";
            }
        }

        return ret + "}";
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
        return std::make_shared<EqualityDomain>();
    }
}