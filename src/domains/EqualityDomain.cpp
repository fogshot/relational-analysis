//
// Created by vanessa on 11/7/18.
//

#include <algorithm>
#include <utility>
#include <string>
#include <memory>
#include <iostream>
#include "../common/ClassType.h"
#include "EqualityDomain.h"
#include "../util.h"
#include "../common/RepresentativeCompare.h"

namespace bra {
    /// Implementation of visitor interface
    bool EqualityDomain::transform_add(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1,
                                       std::shared_ptr<Representative> arg2) {
        if (arg1->getClassType() == ClassType::Constant && arg2->getClassType() == ClassType::Constant) {
            int result = ((Constant *) arg1.get())->getValue() + ((Constant *) arg2.get())->getValue();
            return transformConstantAssignment(destination, std::make_shared<Constant>(result));
        } else {
            // TODO: this is a case where simple equalities don't suffice
            // -> unkown assignment for now
            return transformUnkownAssignment(destination);
        }
    }

    bool EqualityDomain::transform_store(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) {
        if (arg1->getClassType() == ClassType::Constant) {
            std::shared_ptr<Constant> con = std::static_pointer_cast<Constant>(arg1);
            return transformConstantAssignment(destination, con);
        } else if (arg1->getClassType() == ClassType::Variable) {
            std::shared_ptr<Variable> var = std::static_pointer_cast<Variable>(arg1);
            return transformVariableAssignment(destination, var);
        }

        return false;
    }

    bool EqualityDomain::transform_load(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) {
        // Equal handeling as far as we are concerned
        return transform_store(destination, arg1);
    }


    //function definitions
    bool EqualityDomain::transformUnkownAssignment(const std::shared_ptr<Variable> variable) {
        // Do nothing (Single static assignment)
        return false;
    }

    bool EqualityDomain::transformConstantAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Constant> constant) {
        return this->addConstantAssignmentToEquivalenceClass(constant, variable);
    }

    bool EqualityDomain::transformVariableAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Variable> assignedValue) {
        return this->addVariableAssignmentToEquivalenceClass(assignedValue, variable);
    }

    bool EqualityDomain::addConstantAssignmentToEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        bool modified;

        modified = insertConstantIntoForwardMap(eqRepr, var);
        modified = insertConstantIntoBackwardMap(eqRepr, var) || modified;

        return modified;
    }

    bool EqualityDomain::addVariableAssignmentToEquivalenceClass(const std::shared_ptr<Variable> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        return insertVariableIntoMaps(eqRepr, var);
    }

    bool EqualityDomain::insertConstantIntoForwardMap(const std::shared_ptr<Representative> eqRepr,
                                                      const std::shared_ptr<Variable> var) {
        bool modified = false;

        auto itForward = forwardMap.find(eqRepr); //iterator for forwardMap
        std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass; //shared_ptr on set (=equality class)

        if (itForward != forwardMap.end()) {
            // go through forwardMap if not empty
            eqClass = itForward->second; // get eq class
            auto varIt = eqClass->find(var);
            if (varIt == eqClass->end()) {
                modified = true;
                eqClass->insert(var); // add variable to eq class
            }
        } else {
            // eq class is empty
            modified = true;
            std::set<std::shared_ptr<Variable>, RepresentativeCompare> newSet;
            newSet.insert(var);
            eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>(newSet);
            forwardMap.insert({eqRepr, eqClass}); // insert tuple to map
        }

        return modified;
    }

    bool EqualityDomain::insertConstantIntoBackwardMap(const std::shared_ptr<Representative> eqRepr,
                                                       const std::shared_ptr<Variable> var) {
        bool modified = false;

        auto itBackward = backwardMap.find(var);
        if (itBackward != backwardMap.end()) {
            // if variable is already in map -> overwrite value
            const RepresentativeCompare c;
            if (!c.operator()(itBackward->second, eqRepr)) {
                modified = true;
                itBackward->second = eqRepr;
            }
        } else {
            // otherwise add new pair
            modified = true;
            backwardMap.insert({var, eqRepr});
        }

        return modified;
    }

    bool findCmp(std::shared_ptr<Variable> left, std::shared_ptr<Variable> right) {
        return left == right;
    }

    bool EqualityDomain::insertVariableIntoMaps(const std::shared_ptr<Variable> var1,
                                                const std::shared_ptr<Variable> var2) {
        bool modified = false;
        std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass;

        // Find existing repr var if any
        auto itBackward = backwardMap.find(var1);
        auto itBackward2 = backwardMap.find(var2);
        std::shared_ptr<Representative> reprVar = nullptr;
        std::shared_ptr<Variable> varToAdd = nullptr;
        if (itBackward != backwardMap.end()) {
            reprVar = itBackward->second;
            varToAdd = var2;
        }
        if (itBackward2 != backwardMap.end()) {
            reprVar = itBackward2->second;
            varToAdd = var1;
        }

        if (reprVar != nullptr) {
            // if there is an existing entry -> look for representative in forwardMap to obtain eqClass
            auto itForward = forwardMap.find(reprVar);
            if (reprVar->getClassType() == ClassType::Constant) { // Constant case
                modified = addConstantAssignmentToEquivalenceClass(reprVar, varToAdd); // treat like a constant
            } else {
                // Insert into eq class in forwardMap
                eqClass = itForward->second;
                auto varIt = eqClass->find(varToAdd);
                if (varIt != eqClass->end()) {
                    modified = true;
                    eqClass->insert(varToAdd);

                    // Update representative for equality class in both maps
                    std::shared_ptr<Representative> newRepr = *eqClass->begin();
                    forwardMap.erase(newRepr);
                    forwardMap.insert({newRepr, eqClass});
                    for (auto it : *eqClass) {
                        backwardMap.erase(it);
                        backwardMap.insert({it, newRepr});
                    }
                }
            }
        } else {
            // Insert new eqClass into forward map
            std::set<std::shared_ptr<Variable>, RepresentativeCompare> newSet;
            newSet.insert(var1);
            newSet.insert(var2);
            std::shared_ptr<Representative> newRepr = std::shared_ptr<Representative>(*newSet.begin());
            auto eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, RepresentativeCompare>>(newSet);
            forwardMap.insert({newRepr, eqClass}); //insert tuple to map

            // Insert into backward map
            for (auto it : *eqClass) {
                backwardMap.insert({it, newRepr});
            }
        }

        return modified;
    }

    /// This is the purge() implementation. For now it is not invoked (debug purposes)
    void EqualityDomain::removeTemporaryVariablesfromEquivalenceClass() {
        Variable *varPtr;
        for (const auto &it : backwardMap) { //iterate through backwardMap
            if (it.first.get()->isTemporaryVariable()) { //if key is a temporary variable -> remove
                varPtr = it.first.get();
                std::shared_ptr<Variable> varShPtr(varPtr);
                removeVariableFromEquivalenceClass(varShPtr);
            }
        }
    }

    void EqualityDomain::removeVariableFromEquivalenceClass(const std::shared_ptr<Variable> var) {
        //look for representative and remove from backwardMap
        std::shared_ptr<Representative> eqRepr = backwardMap.find(var)->second;
        backwardMap.erase(var);

        //erase from forwardMap
        std::shared_ptr<std::set<std::shared_ptr<Variable>, RepresentativeCompare>> eqClass = forwardMap.find(
                var)->second;//find respective eq class
        eqClass->erase(std::find(eqClass->begin(), eqClass->end(), var));
        if (eqClass->empty()) {//if this was last element in set -> remove from map
            forwardMap.erase(eqRepr);
        } else if (eqRepr ==
                   var) { //if current repr is not in the eqClass anymore -> replace with first element in eqClass
            const std::shared_ptr<Variable> &repr = eqClass->begin().operator*();
            forwardMap.erase(eqRepr);
            forwardMap.insert({repr, eqClass});
            for (const std::shared_ptr<Variable> &eqMember : *eqClass) {
                auto it = backwardMap.find(eqMember);
                if (it != backwardMap.end()) {
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
        std::string ret = "{";
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

        ret += "} <-> {";
        for (auto pairIt = this->backwardMap.begin(); pairIt != this->backwardMap.end(); pairIt++) {
            ret += "(" + pairIt->first->toString() + ", " + pairIt->second->toString() + ")";
            if (std::next(pairIt) != this->backwardMap.end()) {
                ret += ", ";
            }
        }
        return ret + "}";
    }

    std::shared_ptr<AbstractDomain> EqualityDomain::bottom() {
        return std::make_shared<EqualityDomain>();
    }

    std::shared_ptr<AbstractDomain>
    EqualityDomain::leastUpperBound(std::vector<std::shared_ptr<AbstractDomain>> domains) {
        // TODO implement for real
        return std::make_shared<EqualityDomain>();
    }
}