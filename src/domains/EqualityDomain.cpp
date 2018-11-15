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

namespace bra {
    //constructor and Destructor
    EqualityDomain::EqualityDomain() = default;

    EqualityDomain::~EqualityDomain() = default;

    /// Implementation of visitor interface
    void EqualityDomain::transform_add(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1,
                                       std::shared_ptr<Representative> arg2) {
        if (arg1->getClassType() == ClassType::Constant && arg2->getClassType() == ClassType::Constant) {
            int result = ((Constant *) arg1.get())->getValue() + ((Constant *) arg2.get())->getValue();
            transformConstantAssignment(destination, std::make_shared<Constant>(result));
        } else {
            // TODO: this is a case where simple equalities don't suffice
            // -> unkown assignment for now
            transformUnkownAssignment(destination);
        }
    }

    void EqualityDomain::transform_store(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) {
        if (arg1->getClassType() == ClassType::Constant) {
            std::shared_ptr<Constant> con = std::static_pointer_cast<Constant>(arg1);
            transformConstantAssignment(destination, con);
        } else if (arg1->getClassType() == ClassType::Variable) {
            std::shared_ptr<Variable> var = std::static_pointer_cast<Variable>(arg1);
            transformVariableAssignment(destination, var);
        }
    }

    void EqualityDomain::transform_load(std::shared_ptr<Variable> destination, std::shared_ptr<Representative> arg1) {
        // Equal handeling as far as we are concerned
        transform_store(destination, arg1);
    }


    //function definitions
    void EqualityDomain::transformUnkownAssignment(const std::shared_ptr<Variable> variable) {
        // Do nothing (Single static assignment)
    }

    void EqualityDomain::transformConstantAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Constant> constant) {
        this->addConstantAssignmentToEquivalenceClass(constant, variable);

    }

    void EqualityDomain::transformVariableAssignment(const std::shared_ptr<Variable> variable,
                                                     const std::shared_ptr<Variable> assignedValue) {
        this->addVariableAssignmentToEquivalenceClass(assignedValue, variable);
    }

    void EqualityDomain::addConstantAssignmentToEquivalenceClass(const std::shared_ptr<Representative> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        insertConstantIntoForwardMap(eqRepr, var);
        insertConstantIntoBackwardMap(eqRepr, var);
    }

    void EqualityDomain::addVariableAssignmentToEquivalenceClass(const std::shared_ptr<Variable> eqRepr,
                                                                 const std::shared_ptr<Variable> var) {
        insertVariableIntoMaps(eqRepr, var);
    }

    void EqualityDomain::insertConstantIntoForwardMap(const std::shared_ptr<Representative> eqRepr,
                                                      const std::shared_ptr<Variable> var) {
        auto itForward = forwardMap.find(eqRepr); //iterator for forwardMap
        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass; //shared_ptr on set (=equality class)

        if (itForward != forwardMap.end()) { //go through forwardMap if not empty
            eqClass = itForward->second; //get eq class
            eqClass->insert(var); // add variable to eq class
        } else { //eq class is empty
            std::set<std::shared_ptr<Variable>, Compare> newSet;
            newSet.insert(var);
            eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, Compare>>(newSet);
            forwardMap.insert({eqRepr, eqClass}); //insert tuple to map
        }
    }

    void EqualityDomain::insertConstantIntoBackwardMap(const std::shared_ptr<Representative> eqRepr,
                                                       const std::shared_ptr<Variable> var) {
        auto itBackward = backwardMap.find(var);
        if (itBackward != backwardMap.end()) { //if variable is already in map -> overwrite value
            itBackward->second = eqRepr;
        } else { //otherwise add new pair
            backwardMap.insert({var, eqRepr});
        }
    }

    void EqualityDomain::insertVariableIntoMaps(const std::shared_ptr<Variable> eqReprVar,
                                                const std::shared_ptr<Variable> var) {

        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass;
        //eqReprVar = std::dynamic_pointer_cast<std::shared_ptr<Variable>> (eqRepr);
        //look for existing assignment in backwardMap
        auto itBackward = backwardMap.find(eqReprVar);

        if (itBackward != backwardMap.end()) { //if there is an existing entry -> look for representative in forwardMap
            auto newReprVar = itBackward->second;
            auto itForward = forwardMap.find(newReprVar);
            if (newReprVar->getClassType() == ClassType::Constant) { //Constant case
                addConstantAssignmentToEquivalenceClass(newReprVar, var); //treat like a constant
            } else {
                //insert into eq class in forwardMap
                eqClass = itForward->second;
                eqClass->insert(var);
                std::shared_ptr<Representative> newRepr = *eqClass->begin();
                forwardMap.erase(newRepr);
                forwardMap.insert({newRepr, eqClass});
                for (auto it : *eqClass) {
                    backwardMap.erase(it);
                    backwardMap.insert({it, newRepr});
                }
            }
        } else {//no entry yet -> only insert the variables
            std::set<std::shared_ptr<Variable>, Compare> newSet;
            newSet.insert(var);
            newSet.insert(eqReprVar);
            std::shared_ptr<Representative> key = std::shared_ptr<Representative>(*newSet.begin());
            auto eqClass = std::make_shared<std::set<std::shared_ptr<Variable>, Compare>>(newSet);
            forwardMap.insert({key, eqClass}); //insert tuple to map
        }
    }

    void EqualityDomain::removeTemporaryVariablesfromEquivalenceClass() {
        Variable *varPtr;
        for (const auto &it : backwardMap) { //iterate through backwardMap
            if (it.first.get()->isTemporaryVariable) { //if key is a temporary variable -> remove
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
        std::shared_ptr<std::set<std::shared_ptr<Variable>, Compare>> eqClass = forwardMap.find(
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
        std::string ret = "forwardMap {";
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

        ret += "}  -> backwardMap {";
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