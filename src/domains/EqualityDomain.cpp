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
        stream << "EqualityDomain (" << &dom << "):\n  -> forwardMap {";
        for (auto tmp = dom.forwardMap.begin(); tmp != dom.forwardMap.end(); tmp++) {
            stream << "(" << tmp->first << ": {";

            for (auto var = tmp->second->begin(); var != tmp->second->end(); var++) {
                stream << *var;

                if (std::next(var) != tmp->second->end()) {
                    stream << ", ";
                }
            }

            stream << "})";
            if (std::next(tmp) != dom.forwardMap.end()) {
                stream << ", ";
            }
        }

        // New line for forward map
        stream << "}" << "\n  -> backwardMap {";
        for (auto pairIt = dom.backwardMap.begin(); pairIt != dom.backwardMap.end(); pairIt++) {
            stream << "(" << pairIt->first << ", " << pairIt->second << ")";

            if (std::next(pairIt) != dom.backwardMap.end()) {
                stream << ", ";
            }
        }

        return stream << "}";
    }

    std::string EqualityDomain::toString() {
        std::string ret = "EQ: {";
        for (auto const &pair: this->forwardMap) {
            ret += "(" + pair.first->toString() + ": {";
            for (auto const &var: *(pair.second)) {
                ret += var->toString() + ", ";
            }
            ret += "}), ";
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